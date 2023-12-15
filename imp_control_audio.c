#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imp_control_audio.h"
#include "imp_control_help.h"
#include "imp_control_util.h"

// AI

char *HighPassFilter(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_HPF;
}
	int res = -1;
	if (p == NULL) {
		return DEBUG_TEXT("Missing parameter");
	}
	int value = atoi(p);
	if (value == 0) {
			res = IMP_AI_DisableHpf();
	} else if (value == 1) {
			IMPAudioIOAttr attr;
			res = IMP_AI_GetPubAttr(AudioDeviceID, &attr);
			if (!res) res = IMP_AI_EnableHpf(&attr);
	} else {
			return "Invalid parameter";
	}
	return RESULT(res, p);
}

char *AutoGainControl(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_AOAGC;
}
	if (p == NULL) {
			return DEBUG_TEXT("Missing parameter");
	}
	int res = -1;
	int targetLevelDbfs = atoi(p);
	if (targetLevelDbfs == 0) {
			// ret = IMP_AI_DisableAgc();
			return RESULT(res, p);
	}
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p) {
			int compressionGaindB = atoi(p);
			IMPAudioIOAttr attr;
			res = IMP_AI_GetPubAttr(AudioDeviceID, &attr);
			if (!res) res = IMP_AI_EnableAgc(&attr, targetLevelDbfs, compressionGaindB);
	} else {
			return "Missing compression gain parameter";
	}
	return RESULT(res, p);
}

char *NoiseSuppression(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_AINS;
}
	if (p == NULL) {
			return DEBUG_TEXT("Missing parameter");
	}
	int level = atoi(p);
	int res = -1;
	if (level != -1 && (level < 0 || level > 3)) {
			return "Invalid level";
	}
	if (level == -1) {
			res = IMP_AI_DisableNs();
	} else {
			IMPAudioIOAttr attr;
			res = IMP_AI_GetPubAttr(AudioDeviceID, &attr);
			if (!res) res = IMP_AI_EnableNs(&attr, level);
	}
	return RESULT(res, p);
}

char *EchoCancellation(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_AIEC;
}
	if (p == NULL) {
			return DEBUG_TEXT("Missing parameter");
	}
	int state = atoi(p);
	int res = -1;
	if (state != 0 && state != 1) {
			return "Invalid state";
	}
	if (state == 0) {
			res = IMP_AI_DisableAec(AudioDeviceID, AudioChID);
	} else {
			res = IMP_AI_EnableAec(AudioDeviceID, AudioChID, AudioDeviceID, AudioChID);
	}
	return RESULT(res, p);
}

char *Volume(char *tokenPtr) {
    char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    if (p != NULL && strcmp(p, "-h") == 0) {
        return HELP_MESSAGE_AIVOL;
    }

    if (!p) {
        int vol;
        int res = IMP_AI_GetVol(AudioDeviceID, AudioChID, &vol);
        if (res) return "error";

        sprintf(response, "%d", vol);
        return response;
    } else {
        int vol = atoi(p);
        if (vol > 120 || vol < -30) {
            return "Invalid value";
        }
        int res = IMP_AI_SetVol(AudioDeviceID, AudioChID, vol);
        return RESULT(res, p);
    }
}

char *Gain(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_AIGAIN;
}
	if(!p) {
		int gain;
		int res = IMP_AI_GetGain(AudioDeviceID, AudioChID, &gain);
		if(res) return "error";
		sprintf(response, "%d", gain);
		return response;
		} else {
		int gain = atoi(p);
        if (gain > 31 || gain < 0) {
            return "Invalid value";
        }
	}
	int res = IMP_AI_SetGain(AudioDeviceID, AudioChID, atoi(p));
	return RESULT(res, p);
}

char *AlcGain(char *tokenPtr) {
#ifndef CONFIG_T20
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_AIALC;
}
	if(!p) {
		int gain;
		int res = IMP_AI_GetAlcGain(AudioDeviceID, AudioChID, &gain);
		if(res) return "error";
		sprintf(response, "%d", gain);
		return response;
			} else {
		int gain = atoi(p);
        if (gain > 7 || gain < 0) {
            return "Invalid value";
        }
	}
	int res = IMP_AI_SetAlcGain(AudioDeviceID, AudioChID, atoi(p));
	return RESULT(res, p);
#else
	return HELP_MESSAGE_PLATFORM;
#endif
}

// AO
char *aoVolume(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_AOVOL;
}
	if(!p) {
		int vol;
		int res = IMP_AO_GetVol(AudioDeviceID, AudioChID, &vol);
		if(res) return "error";
		sprintf(response, "%d", vol);
		return response;
		    } else {
        int vol = atoi(p);
        if (vol > 120 || vol < -30) {
            return "Invalid value";
        }
	}
	int res = IMP_AO_SetVol(AudioDeviceID, AudioChID, atoi(p));
	return RESULT(res, p);
}

char *aoGain(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_AOGAIN;
}
	if(!p) {
		int gain;
		int res = IMP_AO_GetGain(AudioDeviceID, AudioChID, &gain);
		if(res) return "error";
		sprintf(response, "%d", gain);
		return response;
				} else {
		int gain = atoi(p);
        if (gain > 31 || gain < 0) {
            return "Invalid value";
        }
	}
	int res = IMP_AO_SetGain(AudioDeviceID, AudioChID, atoi(p));
	return RESULT(res, p);
}

char *aoHighPassFilter(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_AOHPF;
}
	int res = -1;
	if (p == NULL) {
			return DEBUG_TEXT("Missing parameter");
	}
	int value = atoi(p);
	if (value == 0) {
			res = IMP_AO_DisableHpf();
	} else if (value == 1) {
			IMPAudioIOAttr attr;
			res = IMP_AO_GetPubAttr(AudioDeviceID, &attr);
			if (!res) res = IMP_AO_EnableHpf(&attr);
	} else {
			return "Invalid parameter";
	}
	return RESULT(res, p);
}