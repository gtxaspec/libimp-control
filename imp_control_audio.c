#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imp_control_audio.h"

// AI

char *HighPassFilter(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  int ret = -1;
  if(p && !strcmp(p, "off")) {
    ret = IMP_AI_DisableHpf();
  }
  if(p && !strcmp(p, "on")) {
    IMPAudioIOAttr attr;
    ret = IMP_AI_GetPubAttr(AudioDeviceID, &attr);
    if(!ret) ret = IMP_AI_EnableHpf(&attr);
  }
  return ret ? "error" : "ok";
}

char *AutoGainControl(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) return "error";

  int ret = -1;
  if(!strcmp(p, "off")) {
    // ret = IMP_AI_DisableAgc(); // Exception
  } else {
    int targetLevelDbfs = atoi(p);
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    if(p) {
      int compressionGaindB = atoi(p);
      IMPAudioIOAttr attr;
      ret = IMP_AI_GetPubAttr(AudioDeviceID, &attr);
      if(!ret) ret = IMP_AI_EnableAgc(&attr, targetLevelDbfs, compressionGaindB);
    }
  }
  return ret ? "error" : "ok";
}

char *NoiseSuppression(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) return "error";

  int ret = -1;
  if(!strcmp(p, "off")) {
    ret = IMP_AI_DisableNs();
  } else {
    int level = atoi(p);
    IMPAudioIOAttr attr;
    ret = IMP_AI_GetPubAttr(AudioDeviceID, &attr);
    if(!ret) ret = IMP_AI_EnableNs(&attr, level);
  }
  return ret ? "error" : "ok";
}

char *EchoCancellation(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  int ret = -1;
  if(p && !strcmp(p, "off")) {
    ret = IMP_AI_DisableAec(AudioDeviceID, AudioChID);
  }
  if(p && !strcmp(p, "on")) {
    ret = IMP_AI_EnableAec(AudioDeviceID, AudioChID, AudioDeviceID, AudioChID);
  }
  return ret ? "error" : "ok";
}

char *Volume(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int vol;
    int ret = IMP_AI_GetVol(AudioDeviceID, AudioChID, &vol);
    if(ret) return "error";
    sprintf(response, "%d", vol);
    return response;
  }
  int ret = IMP_AI_SetVol(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
}

char *Gain(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int gain;
    int ret = IMP_AI_GetGain(AudioDeviceID, AudioChID, &gain);
    if(ret) return "error";
    sprintf(response, "%d", gain);
    return response;
  }
  int ret = IMP_AI_SetGain(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
}

char *AlcGain(char *tokenPtr) {
#ifndef CONFIG_T20
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int gain;
    int ret = IMP_AI_GetAlcGain(AudioDeviceID, AudioChID, &gain);
    if(ret) return "error";
    sprintf(response, "%d", gain);
    return response;
  }
  int ret = IMP_AI_SetAlcGain(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
#else
  return "not supported on >T20";
#endif
}

// AO
char *aoVolume(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int vol;
    int ret = IMP_AO_GetVol(AudioDeviceID, AudioChID, &vol);
    if(ret) return "error";
    sprintf(response, "%d", vol);
    return response;
  }
  int ret = IMP_AO_SetVol(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
}

char *aoGain(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int gain;
    int ret = IMP_AO_GetGain(AudioDeviceID, AudioChID, &gain);
    if(ret) return "error";
    sprintf(response, "%d", gain);
    return response;
  }
  int ret = IMP_AO_SetGain(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
}
