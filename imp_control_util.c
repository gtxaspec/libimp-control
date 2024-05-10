#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include "imp_control_util.h"

char* GetDeviceID() {
	SUDevID devID;
	int ret = SU_Base_GetDevID(&devID);
	if (ret != 0) {
		snprintf(response, sizeof(response), "Error: Failed to get device ID.");
		return response;
	}
	snprintf(response, sizeof(response), "%s", devID.chr);
	return response;
};

char* GetModelFamily() {
	SUModelNum modelNum;
	int ret =  SU_Base_GetModelNumber(&modelNum);
	if (ret != 0) {
		snprintf(response, sizeof(response), "Error: Failed to get model family.");
		return response;
	}
	snprintf(response, sizeof(response), "%s", modelNum.chr);
	return response;
};

char* GetSysVersion() {
	SUVersion version;
	int ret =  SU_Base_GetVersion(&version);
	if (ret != 0) {
		snprintf(response, sizeof(response), "Error: Failed to get SDK SYSUTILS Version.");
		return response;
	}
	snprintf(response, sizeof(response), "Ingenic %s", version.chr);
	return response;
};

char *GetIMPVersion(char *tokenPtr) {
	IMPVersion version;
	int ret = IMP_System_GetVersion(&version);
	if (ret == 0) {
		snprintf(response, sizeof(response), "Ingenic %s", version.aVersion);
	} else {
		snprintf(response, sizeof(response), "Failed to get IMP version");
	}
	return response;
}
const char* (*original_IMP_System_GetCPUInfo)(void) = NULL;
void initialize_original_functions() {
	if (!original_IMP_System_GetCPUInfo) {
		original_IMP_System_GetCPUInfo = dlsym(RTLD_NEXT, "IMP_System_GetCPUInfo");
	}
}

char *GetCPUInfo(char *tokenPtr) {
 initialize_original_functions(); // Ensure the original function is loaded
	if (original_IMP_System_GetCPUInfo) {
		const char* cpuInfo = original_IMP_System_GetCPUInfo();    if (cpuInfo != NULL) {
		snprintf(response, sizeof(response), "%s", cpuInfo);
	} else {
		snprintf(response, sizeof(response), "Failed to get CPU info");
	}
	return response;
	}
}
