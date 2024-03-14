#include <arpa/inet.h>  // For socket functions and structures
#include <dlfcn.h>      // For dlsym, dlerror
#include <sys/epoll.h>	// For epoll
#include <errno.h>      // For errno
#include <fcntl.h>      // For fcntl
#include <netinet/in.h> // For sockaddr_in
#include <pthread.h>    // For pthread_create, pthread_detach
#include <sys/select.h> // For select
#include <stdio.h>      // For printf, fprintf, etc.
#include <stdlib.h>     // For NULL, exit
#include <string.h>     // For strlen, strtok_r, etc.
#include <sys/types.h>  // For socket types
#include <sys/socket.h> // For socket functions
#include <unistd.h>     // For close, read, write, unsetenv
#include "version.h"    // git VERSION
#include "command.h"
#include "include/imp_log.h"
#include "imp_control_util.h"
#include <libgen.h>

// Define the maximum number of events that epoll_wait can return at a time.
// This number represents the capacity of the event array used for handling
// file descriptor events in the epoll mechanism.
#define MAX_EVENTS 64

// Track library intialization to prevent multiple loads
int isLibraryInitialized = 0;

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
		IMP_LOG_ERR(TAG, "socket error: %s\n", strerror(errno));
		return NULL;
	}

	int sock_optval = 1;
	if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &sock_optval,
				sizeof(sock_optval)) == -1) {
		IMP_LOG_ERR(TAG, "setsockopt error: %s\n", strerror(errno));
		close(listenSocket);
		return NULL;
	}
	// Define the server address structure
	struct sockaddr_in saddr = {.sin_family = AF_INET,
								.sin_port = htons(CommandPort),
								.sin_addr.s_addr = htonl(INADDR_ANY)};

	// Bind the socket to the specified address and port
	if (bind(listenSocket, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		IMP_LOG_ERR(TAG, "bind error: %s\n", strerror(errno));
		close(listenSocket);
		return NULL;
	}

	// Start listening for incoming connections
	if (listen(listenSocket, MaxConnect) == -1) {
		IMP_LOG_ERR(TAG, "listen error: %s\n", strerror(errno));
		close(listenSocket);
		return NULL;
	}

	// Create an epoll instance
	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1) {
		IMP_LOG_ERR(TAG, "epoll_create error: %s\n", strerror(errno));
		close(listenSocket);
		return NULL;
	}

	struct epoll_event ev, events[MAX_EVENTS]; // Interested in input events
	ev.events = EPOLLIN;

	// Add the listening socket to the epoll instance for monitoring
	ev.data.fd = listenSocket;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listenSocket, &ev) == -1) {
		IMP_LOG_ERR(TAG, "epoll_ctl listenSocket error: %s\n", strerror(errno));
		close(epoll_fd);
		close(listenSocket);
		return NULL;
	}

	// Also monitor the self-pipe for internal communication
	ev.data.fd = SelfPipe[0];
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, SelfPipe[0], &ev) == -1) {
		IMP_LOG_ERR(TAG, "epoll_ctl SelfPipe error: %s\n", strerror(errno));
		close(epoll_fd);
		close(listenSocket);
		return NULL;
	}

	// Command processing loop using epoll to monitor file descriptors
	while (1) {
		int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			IMP_LOG_ERR(TAG, "epoll_wait error: %s\n", strerror(errno));
			continue;
		}

		for (int n = 0; n < nfds; ++n) {
			if (events[n].data.fd == listenSocket) {
				// Handle new incoming connections
				struct sockaddr_in dstAddr;
				socklen_t len = sizeof(dstAddr);
				int newSocket =
					accept(listenSocket, (struct sockaddr *)&dstAddr, &len);
				if (newSocket < 0) {
					IMP_LOG_ERR(TAG, "accept error\n");
					continue;
				}

				// Accept connections only from localhost
				if (strcmp(inet_ntoa(dstAddr.sin_addr), "127.0.0.1")) {
					fprintf(stderr, "Rejected request from %s\n",
							inet_ntoa(dstAddr.sin_addr));
					close(newSocket);
					continue;
				}

				// Set socket to non-blocking mode
				int flags = fcntl(newSocket, F_GETFL, 0);
				fcntl(newSocket, F_SETFL, O_NONBLOCK | flags);

				// Add new socket to epoll instance
				struct epoll_event ev = {0};
				ev.events = EPOLLIN;
				ev.data.fd = newSocket;
				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, newSocket, &ev) == -1) {
					IMP_LOG_ERR(TAG, "epoll_ctl newSocket error: %s\n",
								strerror(errno));
					close(newSocket);
					continue;
				}
			} else if (events[n].data.fd == SelfPipe[0]) {
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
				}
			} else {
				// Handle data from clients
				char buf[BufferSize];
				int size = recv(events[n].data.fd, buf, BufferSize - 1, 0);
				if (size <= 0) {
					close(events[n].data.fd);
					continue;
				}
				buf[size] = '\0';  // Null-terminate the received data

				// Parse and execute the received command
				char *tokenPtr;
				char *command = strtok_r(buf, " \t\r\n", &tokenPtr);
				if (command == NULL) {
					continue;
				}

				// Check and execute the command if found
				int executed = 0;
				for (int i = 0; CommandTable[i].cmd != NULL; i++) {
					if (strcasecmp(command, CommandTable[i].cmd) == 0) {
						char *response =
							CommandTable[i].func(events[n].data.fd, tokenPtr);
						if (response) {
							send(events[n].data.fd, response,
								strlen(response) + 1, 0);
							char cr = '\n';
							send(events[n].data.fd, &cr, 1, 0);
							close(events[n].data.fd);
						}
						executed = 1;
						break;
					}
				}

				// If the command is not recognized, send an error message
				if (!executed) {
					char *error_msg = "Unknown command\n";
					send(events[n].data.fd, error_msg, strlen(error_msg) + 1, 0);
					close(events[n].data.fd);
					IMP_LOG_ERR(TAG, "Unknown command received: %s\n", command);
				}
			}
		}
	}

	close(epoll_fd);
	close(listenSocket);
	return NULL;
}

void executeControl(const char* loadingMethod) {
	// Set the library as initialized
	isLibraryInitialized = 1;

	printf("LIBIMP_CONTROL Version: %s %s\n", VERSION, loadingMethod);
	IMP_LOG_INFO(TAG, "Version: %s %s\n", VERSION, loadingMethod);

	if (pipe(SelfPipe) != 0) {
		IMP_LOG_ERR(TAG, "pipe creation error\n");
		return;
	}

	// Set pipe to non-blocking mode
	for (int i = 0; i < 2; i++) {
		int flags = fcntl(SelfPipe[i], F_GETFL, 0);
		fcntl(SelfPipe[i], F_SETFL, O_NONBLOCK | flags);
	}

	pthread_t thread;
	if (pthread_create(&thread, NULL, CommandThread, NULL) != 0) {
		IMP_LOG_ERR(TAG, "thread creation error\n");
		return;
	}
	// Detach the thread to free resources when it's finished
	pthread_detach(thread);
}

// Hook function with the same signature as IMP_System_GetCPUInfo
const char* IMP_System_GetCPUInfo() {
	static const char* (*original_IMP_System_GetCPUInfo)(void) = NULL;
	if (!original_IMP_System_GetCPUInfo) {
		original_IMP_System_GetCPUInfo = dlsym(RTLD_NEXT, "IMP_System_GetCPUInfo");
		if (!original_IMP_System_GetCPUInfo) {
			IMP_LOG_ERR(TAG, "Error in `dlsym`: %s\n", dlerror());
			return NULL;
		}
		// Start our thread prior to the original function when using DLSYM
		executeControl("dlsym");
		return original_IMP_System_GetCPUInfo();
	} else {
		return NULL;
	}
	// The following line should never be reached, but it's here for completeness.
	return NULL;
}
