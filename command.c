#include <arpa/inet.h>  // For socket functions and structures
#include <dlfcn.h>      // For dlsym, dlerror
#include <errno.h>      // For errno
#include <fcntl.h>      // For fcntl
#include <netinet/in.h> // For sockaddr_in
#include <pthread.h>    // For pthread_create, pthread_detach
#include <stdio.h>      // For printf, fprintf, etc.
#include <stdlib.h>     // For NULL, exit
#include <string.h>     // For strlen, strtok_r, etc.
#include <sys/types.h>  // For socket types
#include <sys/socket.h> // For socket functions
#include <unistd.h>     // For close, read, write, unsetenv
#include "version.h"    // git VERSION

// Constants
static const unsigned short CommandPort = 4000;
static const int MaxConnect = 255;
static const int BufferSize = 256;

// Global variables for pipe communication
static int SelfPipe[2];

// Function declarations for external modules
extern char *IMPTune(int fd, char *tokenPtr);

// Structure for command handling
struct CommandTableSt {
	const char *cmd;
	char * (*func)(int, char *);
};

// Command handling table
struct CommandTableSt CommandTable[] = {
	{ "imp_control", &IMPTune },
	{ NULL, NULL } // End of table marker
};

// Function to send command response
void CommandResponse(int fd, const char *res) {
	if (res == NULL) {
		return;
	}

	unsigned char buf[BufferSize];
	unsigned int len = strlen(res);
	buf[0] = len > 252 ? 253 : len + 1;
	buf[1] = fd;
	strncpy((char *)buf + 2, res, buf[0] - 1);
	buf[buf[0] + 1] = '\0'; // Ensure null termination
	write(SelfPipe[1], buf, buf[0] + 2);
}

// Command processing thread
static void *CommandThread(void *arg) {
	// Socket setup
	int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		return NULL;
	}

	int sock_optval = 1;
	if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &sock_optval, sizeof(sock_optval)) == -1) {
		fprintf(stderr, "setsockopt error: %s\n", strerror(errno));
		close(listenSocket);
		return NULL;
	}

	struct sockaddr_in saddr = {
		.sin_family = AF_INET,
		.sin_port = htons(CommandPort),
		.sin_addr.s_addr = htonl(INADDR_ANY)
	};

	if (bind(listenSocket, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		fprintf(stderr, "bind error: %s\n", strerror(errno));
		close(listenSocket);
		return NULL;
	}

	if (listen(listenSocket, MaxConnect) == -1) {
		fprintf(stderr, "listen error: %s\n", strerror(errno));
		close(listenSocket);
		return NULL;
	}

	fd_set targetFd;
	FD_ZERO(&targetFd);
	FD_SET(listenSocket, &targetFd);
	int maxFd = listenSocket;
	FD_SET(SelfPipe[0], &targetFd);
	if (SelfPipe[0] > maxFd) {
		maxFd = SelfPipe[0];
	}

	// Command processing loop
	while (1) {
		fd_set checkFDs = targetFd;
		int selectResult = select(maxFd + 1, &checkFDs, NULL, NULL, NULL);
		if (selectResult == -1) {
			fprintf(stderr, "select error: %s\n", strerror(errno));
			continue;
		}

		// Check each file descriptor
		for (int fd = 0; fd <= maxFd; fd++) {
			if (!FD_ISSET(fd, &checkFDs)) {
				continue;
			}

			if (fd == SelfPipe[0]) {
				// Handle self-pipe for internal communication
				unsigned char buf[BufferSize];
				while (1) {
					int length = read(SelfPipe[0], buf, 2);
					if (length <= 1) {
						break;
					}
					int resSize = buf[0];
					int resFd = buf[1];
					length = read(SelfPipe[0], buf, resSize);
					if (length < resSize) {
						break;
					}
					char *res = (char *)buf;
					strcat(res, "\n");
					send(resFd, res, strlen(res) + 1, 0);
					close(resFd);
					FD_CLR(resFd, &targetFd);
				}
			} else if (fd == listenSocket) {
				// Handle new incoming connections
				struct sockaddr_in dstAddr;
				socklen_t len = sizeof(dstAddr);
				int newSocket = accept(fd, (struct sockaddr *)&dstAddr, &len);
				if (newSocket < 0) {
					fprintf(stderr, "accept error\n");
					continue;
				}

				// Set socket to non-blocking mode
				int flags = fcntl(newSocket, F_GETFL, 0);
				fcntl(newSocket, F_SETFL, O_NONBLOCK | flags);

				FD_SET(newSocket, &targetFd);
				if (newSocket > maxFd) {
					maxFd = newSocket;
				}
				if (maxFd >= MaxConnect) {
					maxFd = MaxConnect - 1;
				}
			} else {
				// Handle data from clients
				char buf[BufferSize];
				int size = recv(fd, buf, BufferSize - 1, 0);
				if (size <= 0) {
					close(fd);
					FD_CLR(fd, &targetFd);
					continue;
				}
				buf[size] = '\0'; // Null-terminate the received data

				char *tokenPtr;
				char *command = strtok_r(buf, " \t\r\n", &tokenPtr);
				if (command == NULL) {
					continue;
				}

				int executed = 0;
				for (int i = 0; CommandTable[i].cmd != NULL; i++) {
					if (strcasecmp(command, CommandTable[i].cmd) == 0) {
						char *response = CommandTable[i].func(fd, tokenPtr);
						if (response) {
							send(fd, response, strlen(response) + 1, 0);
							char cr = '\n';
							send(fd, &cr, 1, 0);
							close(fd);
							FD_CLR(fd, &targetFd);
						}
						executed = 1;
						break;
					}
				}

				if (!executed) {
					char *error_msg = "Unknown command\n";
					send(fd, error_msg, strlen(error_msg) + 1, 0);
					close(fd);
					FD_CLR(fd, &targetFd);
					printf("LIBIMP_CONTROL: Unknown command received: %s\n", command);
				}
			}
		}
	}

	close(listenSocket);
	return NULL;
}

// Hook function with the same signature as IMP_System_GetCPUInfo
// Avoiding the use of a constructor because launching our own
// thread interferes with the host program's complex threading mechanisms.
const char* IMP_System_GetCPUInfo() {
	static const char* (*original_IMP_System_GetCPUInfo)(void) = NULL;

	if (!original_IMP_System_GetCPUInfo) {
		// Dynamically look up the original IMP_System_GetCPUInfo function
		original_IMP_System_GetCPUInfo = dlsym(RTLD_NEXT, "IMP_System_GetCPUInfo");
		if (!original_IMP_System_GetCPUInfo) {
			fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
			return NULL; // return NULL as the function expects a string return type
		}
	}

	// Start our thread prior to the original function
	printf("LIBIMP_CONTROL Version: %s\n", VERSION);

	if (pipe(SelfPipe) != 0) {
		fprintf(stderr, "pipe creation error\n");
		return NULL;
	}

	// Set pipe to non-blocking mode
	for (int i = 0; i < 2; i++) {
		int flags = fcntl(SelfPipe[i], F_GETFL, 0);
		fcntl(SelfPipe[i], F_SETFL, O_NONBLOCK | flags);
	}

	pthread_t thread;
	if (pthread_create(&thread, NULL, CommandThread, NULL) != 0) {
		fprintf(stderr, "thread creation error\n");
		return NULL;
	}

	// Detach the thread to free resources when it's finished
	pthread_detach(thread);

	// Unset LD_PRELOAD to prevent it from being inherited by child processes
	// This also prevents the host program's built-in webserver from breaking
	unsetenv("LD_PRELOAD");

	// Call the original IMP_System_GetCPUInfo function
	const char* result = original_IMP_System_GetCPUInfo();

	// Optionally, we can place code here to run after the original function

	return result;
}
