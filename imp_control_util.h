#ifndef IMP_CONTROL_UTIL_H
#define IMP_CONTROL_UTIL_H

#include <stdint.h>

#define MAX_INFO_LEN        64

char *GetDeviceID();
char *GetModelFamily();
char *GetSysVersion();
char *GetIMPVersion(char *tokenPtr);
char *GetCPUInfo(char *tokenPtr);

typedef union {
		char chr[MAX_INFO_LEN];         /**< Device ID in string */
		uint8_t hex[MAX_INFO_LEN];      /**< Device ID in binary */
} SUDevID;

typedef struct {
		char chr[MAX_INFO_LEN];         /**< Device Model strings */
} SUModelNum;

typedef struct {
		char chr[MAX_INFO_LEN];         /**< Device software version strings*/
} SUVersion;


extern int SU_Base_GetDevID(SUDevID *devID);
extern int SU_Base_GetModelNumber(SUModelNum *modelNum);
extern int SU_Base_GetVersion(SUVersion *version);

typedef struct {
		char aVersion[64];      /**< IMP Version */
} IMPVersion;

extern int IMP_System_GetVersion(IMPVersion *pstVersion);
extern const char* (*original_IMP_System_GetCPUInfo)(void);

#endif // IMP_CONTROL_UTIL_H
