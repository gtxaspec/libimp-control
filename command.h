#ifndef COMMAND_H
#define COMMAND_H

// Constants
static const unsigned short CommandPort = 4000;
static const int MaxConnect = 255;
static const int BufferSize = 256;

// Global variables for pipe communication
static int SelfPipe[2];

// Function declarations for external modules
extern char *IMPTune(int fd, char *tokenPtr);

// Structure for command handling
struct CommandTableStMain {
	const char *cmd;
	char * (*func)(int, char *);
};

// Command handling table
struct CommandTableStMain CommandTable[] = {
	{ "imp_control", &IMPTune },
	{ NULL, NULL } // End of table marker
};

#endif // COMMAND_H
