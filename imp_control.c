#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "imp_control.h"

char *IMPTune(int fd, char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if(p) {
		for(int i = 0; i < sizeof(imp_ControlTable) / sizeof(struct CommandTableSub); i++) {
			if(!strcmp(p, imp_ControlTable[i].cmd)) return (*imp_ControlTable[i].func)(tokenPtr);
		}
	}

	int ch = 0;
	if(p && (!strcmp(p, "0") || !strcmp(p, "1"))) {
		ch = atoi(p);
		p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	}
	return "Usage: [command] [parameters] (Use without parameters to retrieve current values.)\nUse 'help' to get a list of commands";
}
