#ifndef IMP_CONTROL_AUDIO_H
#define IMP_CONTROL_AUDIO_H

char *HighPassFilter(char *tokenPtr);
char *AutoGainControl(char *tokenPtr);
char *NoiseSuppression(char *tokenPtr);
char *EchoCancellation(char *tokenPtr);
char *Volume(char *tokenPtr);
char *Gain(char *tokenPtr);
char *AlcGain(char *tokenPtr);
char *aoHighPassFilter(char *tokenPtr);
char *aoVolume(char *tokenPtr);
char *aoGain(char *tokenPtr);

static const int AudioDeviceID = 0;
static const int AudioChID = 0;

static char response[1024]; // Buffer for response message

typedef struct {
	int samplerate; // Audio sampling rate.
	int bitwidth; // Audio sampling precision. 16 bit
	int soundmode; // Audio channel mode. 1(mono)
	int frmNum;  // Number of cached frames, range: [2, MAX_AUDIO_FRAME_NUM].
	int numPerFrm; // Number of sample points per frame.
	int chnCnt;  // Number of channels supported.
} IMPAudioIOAttr;

// ALC gain value. 0 - 7
extern int IMP_AI_SetAlcGain(int audioDevId, int aiChn, int aiPgaGain);
extern int IMP_AI_GetAlcGain(int audioDevId, int aiChn, int *aiPgaGain);

// Attribute of the audio input device.
extern int IMP_AI_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr);
extern int IMP_AI_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

// AI high pass filtering function.
extern int IMP_AI_DisableHpf();
extern int IMP_AI_EnableHpf(IMPAudioIOAttr *attr);

// AI automatic gain feature.
extern int IMP_AI_DisableAgc();
extern int IMP_AI_EnableAgc(IMPAudioIOAttr *attr, short TargetLevelDbfs, short CompressionGaindB);

// Noise suppression.
extern int IMP_AI_DisableNs();
extern int IMP_AI_EnableNs(IMPAudioIOAttr *attr, int mode);

// Enable audio echo cancellation feature of the specified audio input and audio output.
extern int IMP_AI_DisableAec(int aiDevId, int aiCh);
extern int IMP_AI_EnableAec(int aiDevId, int aiChn, int aoDevId, int aoChn);

// Audio input volume. -30 - 120, default: 60
extern int IMP_AI_SetVol(int audioDevId, int aiChn, int aiVol);
extern int IMP_AI_GetVol(int audioDevId, int aiChn, int *vol);

// Audio input gain. 0 - 31
extern int IMP_AI_SetGain(int audioDevId, int aiChn, int aiGain);
extern int IMP_AI_GetGain(int audioDevId, int aiChn, int *aiGain);

// Attribute of the audio input device.
extern int IMP_AO_SetPubAttr(int audioDevId, IMPAudioIOAttr *attr);
extern int IMP_AO_GetPubAttr(int audioDevId, IMPAudioIOAttr *attr);

// Audio output volume. -30 - 120, default: 60
extern int IMP_AO_SetVol(int audioDevId, int aoChn, int aoVol);
extern int IMP_AO_GetVol(int audioDevId, int aoChn, int *vol);

// Audio output gain. 0 - 31
extern int IMP_AO_SetGain(int audioDevId, int aoChn, int aoGain);
extern int IMP_AO_GetGain(int audioDevId, int aoChn, int *aoGain);

// AO high pass filtering function.
extern int IMP_AO_DisableHpf();
extern int IMP_AO_EnableHpf(IMPAudioIOAttr *attr);

#endif // IMP_CONTROL_AUDIO_H
