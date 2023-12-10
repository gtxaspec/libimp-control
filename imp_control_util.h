#ifndef IMP_CONTROL_UTIL_H
#define IMP_CONTROL_UTIL_H

#include <stdint.h>

#define MAX_INFO_LEN        1024
#define TAG	                "LIBIMP_CONTROL"

#ifdef DEBUG
    #define RESULT(RES, P) ((RES) ? "error" : (P))
#else
    #define RESULT(RES, P) NULL
#endif

static char response[MAX_INFO_LEN]; // Buffer for response message

typedef union {
		char chr[MAX_INFO_LEN];
		uint8_t hex[MAX_INFO_LEN];
} SUDevID;

typedef struct {
		char chr[MAX_INFO_LEN];
} SUModelNum;

typedef struct {
		char chr[MAX_INFO_LEN];
} SUVersion;

extern int SU_Base_GetDevID(SUDevID *devID);
extern int SU_Base_GetModelNumber(SUModelNum *modelNum);
extern int SU_Base_GetVersion(SUVersion *version);

typedef struct {
		char aVersion[64];
} IMPVersion;

extern int IMP_System_GetVersion(IMPVersion *pstVersion);
extern const char* (*original_IMP_System_GetCPUInfo)(void);

#endif // IMP_CONTROL_UTIL_H
