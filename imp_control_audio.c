#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imp_control_audio.h"
#include "imp_control_util.h"

// AI

char *HighPassFilter(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
if (p != NULL && strcmp(p, "-h") == 0)
{
	return 
		"Usage: aihpf [0/1]\n"
		"Option:\n"
		"  0 - Turn off High Pass Filter\n"
		"  1 - Turn on High Pass Filter";
}
	int res = -1;
	if (p == NULL) {
			return "Missing parameter";
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
	return 
		"Usage: aiagc [mode] [compGaindB]\n"
		"Options:\n"
		"  mode - Operating mode of AGC (Automatic Gain Control)\n"
		"         0: Off\n"
		"         Any other number: Gain Level\n"
		"  compGaindB - Compensation gain in decibels (dB), used when mode is not 0";
}
	if (p == NULL) {
			return "Missing parameter";
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
	return 
		"Usage: ains [-1/0-3]\n"
		"Parameter:\n"
		"  -1: Disable Noise Suppression\n"
		"  0-3: Set Noise Suppression Level (0 being the lowest and 3 the highest)";
}
	if (p == NULL) {
			return "Missing parameter";
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
	return 
		"Usage: aiaec [0/1]\n"
		"Parameter:\n"
		"  0: Disable Automatic Echo Cancellation (AEC)\n"
		"  1: Enable Automatic Echo Cancellation (AEC)";
}
	if (p == NULL) {
			return "Missing parameter";
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
if (p != NULL && strcmp(p, "-h") == 0)
{
	return 
		"Usage: aivol [-30-120]\n"
		"Parameter:\n"
		"  -30 to 120: Set the Audio Input Volume Level.\n"
		"              -30 represents the lowest volume level,\n"
		"              120 represents the highest volume level.";
}
	if(!p) {
		int vol;
		int res = IMP_AI_GetVol(AudioDeviceID, AudioChID, &vol);
		if(res) return "error";
		sprintf(response, "%d", vol);
		return response;
	}
	int res = IMP_AI_SetVol(AudioDeviceID, AudioChID, atoi(p));
	return RESULT(res, p);
}

char *Gain(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
	return 
		"Usage: aigain [0-31]\n"
		"Parameter:\n"
		"  0-31: Set the Audio Input Gain level.\n"
		"        0 represents the minimum gain level,\n"
		"        31 represents the maximum gain level.";
}
	if(!p) {
		int gain;
		int res = IMP_AI_GetGain(AudioDeviceID, AudioChID, &gain);
		if(res) return "error";
		sprintf(response, "%d", gain);
		return response;
	}
	int res = IMP_AI_SetGain(AudioDeviceID, AudioChID, atoi(p));
	return RESULT(res, p);
}

char *AlcGain(char *tokenPtr) {
#ifndef CONFIG_T20
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
	return 
		"Usage: aialc [0-7]\n"
		"Parameter:\n"
		"  0-7: Set the Automatic Input Level Control (AILC) level.\n"
		"       0 is the lowest level and 7 is the highest level.";
}
	if(!p) {
		int gain;
		int res = IMP_AI_GetAlcGain(AudioDeviceID, AudioChID, &gain);
		if(res) return "error";
		sprintf(response, "%d", gain);
		return response;
	}
	int res = IMP_AI_SetAlcGain(AudioDeviceID, AudioChID, atoi(p));
	return RESULT(res, p);
#else
	return "not supported on >T20";
#endif
}

// AO
char *aoVolume(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
if (p != NULL && strcmp(p, "-h") == 0)
{
	return 
		"Usage: aovol [-30-120]\n"
		"Parameter:\n"
		"  -30 to 120: Set the Audio Output Volume Level.\n"
		"              -30 represents the lowest volume level,\n"
		"              120 represents the highest volume level.";
}
	if(!p) {
		int vol;
		int res = IMP_AO_GetVol(AudioDeviceID, AudioChID, &vol);
		if(res) return "error";
		sprintf(response, "%d", vol);
		return response;
	}
	int res = IMP_AO_SetVol(AudioDeviceID, AudioChID, atoi(p));
	return RESULT(res, p);
}

char *aoGain(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
	return 
		"Usage: aogain [0-31]\n"
		"Parameter:\n"
		"  0-31: Set the Audio Output Gain level.\n"
		"        0 is the minimum gain level and 31 is the maximum gain level.";
}
	if(!p) {
		int gain;
		int res = IMP_AO_GetGain(AudioDeviceID, AudioChID, &gain);
		if(res) return "error";
		sprintf(response, "%d", gain);
		return response;
	}
	int res = IMP_AO_SetGain(AudioDeviceID, AudioChID, atoi(p));
	return RESULT(res, p);
}

char *aoHighPassFilter(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
if (p != NULL && strcmp(p, "-h") == 0)
{
	return 
		"Usage: aohpf [0/1]\n"
		"Parameter:\n"
		"  0: Disable High Pass Filter for Audio Output\n"
		"  1: Enable High Pass Filter for Audio Output";
}
	int res = -1;
	if (p == NULL) {
			return "Missing parameter";
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