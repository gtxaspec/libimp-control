#define _GNU_SOURCE
#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

///////////
// Audio //
///////////

static const int AudioDeviceID = 0;
static const int AudioChID = 0;

typedef struct {
  int samplerate; // Audio sampling rate.
  int bitwidth; // Audio sampling precision. 16 bit
  int soundmode; // Audio channel mode. 1(mono)
  int frmNum;  // Number of cached frames, range: [2, MAX_AUDIO_FRAME_NUM].
  int numPerFrm; // Number of sample points per frame.
  int chnCnt;  // Number of channels supported.
} IMPAudioIOAttr;

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

// ALC gain value. 0 - 7
extern int IMP_AI_SetAlcGain(int audioDevId, int aiChn, int aiPgaGain);
extern int IMP_AI_GetAlcGain(int audioDevId, int aiChn, int *aiPgaGain);

// Audio output volume. -30 - 120, default: 60
extern int IMP_AO_SetVol(int audioDevId, int aoChn, int aoVol);
extern int IMP_AO_GetVol(int audioDevId, int aoChn, int *vol);

// Audio output gain. 0 - 31
extern int IMP_AO_SetGain(int audioDevId, int aoChn, int aoGain);
extern int IMP_AO_GetGain(int audioDevId, int aoChn, int *aoGain);

/////////////////
// Video begin //
/////////////////

// Contrast
extern int IMP_ISP_Tuning_SetContrast(unsigned char contrast);
extern int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast);

// Brightness
extern int IMP_ISP_Tuning_SetBrightness(unsigned char bright);
extern int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright);

// Saturation
extern int IMP_ISP_Tuning_SetSaturation(unsigned char sat);
extern int IMP_ISP_Tuning_GetSaturation(unsigned char *psat);

// Sharpness
extern int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness);
extern int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness);

// AE compensation.
// AE compensation parameters can adjust the target of the image AE.
extern int IMP_ISP_Tuning_SetAeComp(int comp);
extern int IMP_ISP_Tuning_GetAeComp(int *comp);

// AE Max parameters.
extern int IMP_ISP_Tuning_SetAe_IT_MAX(unsigned int it_max);
extern int IMP_ISP_Tuning_GetAE_IT_MAX(unsigned int *it_max);

// DPC Strength.
extern int IMP_ISP_Tuning_SetDPC_Strength(unsigned int ratio);
extern int IMP_ISP_Tuning_GetDPC_Strength(unsigned int *ratio);

// DRC Strength.
extern int IMP_ISP_Tuning_SetDRC_Strength(unsigned int ratio);
extern int IMP_ISP_Tuning_GetDRC_Strength(unsigned int *ratio);

// Highlight intensity controls.
extern int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength);
extern int IMP_ISP_Tuning_GetHiLightDepress(uint32_t *strength);

// Set 3D noise reduction intensity.
extern int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio);

// Set 2D noise reduction intensity.
extern int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio);

// Max value of sensor analog gain.
extern int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
extern int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);

// Max value of sensor Digital gain.
extern int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain);
extern int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);

// ISP image mirror(horizontal) effect function (enable/disable)
extern int IMP_ISP_Tuning_SetISPHflip(int mode);
extern int IMP_ISP_Tuning_GetISPHflip(int *pmode);

// ISP image mirror(vertical) effect function (enable/disable)
extern int IMP_ISP_Tuning_SetISPVflip(int mode);
extern int IMP_ISP_Tuning_GetISPVflip(int *pmode);

// Hue
extern int IMP_ISP_Tuning_SetBcshHue(unsigned char hue);
extern int IMP_ISP_Tuning_GetBcshHue(unsigned char *hue);

// ISP Day / Night mode
typedef enum {
        IMPISP_RUNNING_MODE_DAY = 0,
        IMPISP_RUNNING_MODE_NIGHT = 1,
} IMPISPRunningMode;

extern int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);
extern int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode);

// ISP Anti-Flicker effect
typedef enum {
        IMPISP_ANTIFLICKER_DISABLE = 0,
        IMPISP_ANTIFLICKER_50HZ = 1,
        IMPISP_ANTIFLICKER_60HZ = 2,
} IMPISPAntiflickerAttr;

extern int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
extern int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);

// ISP Gamma
typedef struct {
        uint16_t gamma[129];
} IMPISPGamma;

extern int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma);

// ISP AutoZoom
typedef struct {
    int chan;
    int scaler_enable;
    int scaler_outwidth;
    int scaler_outheight;
    int crop_enable;
    int crop_left;
    int crop_top;
    int crop_width;
    int crop_height;
} IMPISPAutoZoom;

// ISP Front Crop
extern int IMP_ISP_Tuning_SetAutoZoom(IMPISPAutoZoom *ispautozoom);

typedef struct {
        bool fcrop_enable;
        unsigned int fcrop_top;
        unsigned int fcrop_left;
        unsigned int fcrop_width;
        unsigned int fcrop_height;
} IMPISPFrontCrop;

extern int IMP_ISP_Tuning_SetFrontCrop(IMPISPFrontCrop *ispfrontcrop);
extern int IMP_ISP_Tuning_GetFrontCrop(IMPISPFrontCrop *ispfrontcrop);

// ISP Masking Zone
typedef enum {
        IMPISP_MASK_TYPE_RGB = 0,
        IMPISP_MASK_TYPE_YUV = 1,
} IMPISP_MASK_TYPE;

typedef union mask_value {
        struct {
                unsigned char Red;
                unsigned char Green;
                unsigned char Blue;
        } mask_rgb;
        struct {
                unsigned char y_value;
                unsigned char u_value;
                unsigned char v_value;
        } mask_ayuv;
} IMP_ISP_MASK_VALUE;

typedef struct isp_mask_block_par {
        unsigned char mask_en;
        unsigned short mask_pos_top;
        unsigned short mask_pos_left;
        unsigned short mask_width;
        unsigned short mask_height;
        IMP_ISP_MASK_VALUE mask_value;
} IMPISP_MASK_BLOCK_PAR;

typedef struct {
        IMPISP_MASK_BLOCK_PAR chn0[4];
        IMPISP_MASK_BLOCK_PAR chn1[4];
        IMPISP_MASK_BLOCK_PAR chn2[4];
        IMPISP_MASK_TYPE mask_type;
} IMPISPMASKAttr;

extern int IMP_ISP_Tuning_SetMask(IMPISPMASKAttr *mask);
extern int IMP_ISP_Tuning_GetMask(IMPISPMASKAttr *mask);

// ISP White Balance
typedef enum isp_core_wb_mode {
        ISP_CORE_WB_MODE_AUTO = 0,
        ISP_CORE_WB_MODE_MANUAL = 1,
        ISP_CORE_WB_MODE_DAY_LIGHT = 2,
        ISP_CORE_WB_MODE_CLOUDY = 3,
        ISP_CORE_WB_MODE_INCANDESCENT = 4,
        ISP_CORE_WB_MODE_FLOURESCENT = 5,
        ISP_CORE_WB_MODE_TWILIGHT = 6,
        ISP_CORE_WB_MODE_SHADE = 7,
        ISP_CORE_WB_MODE_WARM_FLOURESCENT = 8,
        ISP_CORE_WB_MODE_CUSTOM = 9,
} isp_core_wb_mode;

typedef struct isp_core_wb_attr{
        enum isp_core_wb_mode mode;
        uint16_t rgain;
        uint16_t bgain;
}IMPISPWB;

extern int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
extern int IMP_ISP_Tuning_GetWB(IMPISPWB *wb);

// ISP Sensor FPS
extern int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
extern int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);

// ISP Backlight Compensation
extern int IMP_ISP_Tuning_SetBacklightComp(uint32_t strength);
extern int IMP_ISP_Tuning_GetBacklightComp(uint32_t *strength);

//////////////
// Begin AI //
//////////////

static char audioResBuf[256];

static char *HighPassFilter(char *tokenPtr) {

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

static char *AutoGainControl(char *tokenPtr) {

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

static char *NoiseSuppression(char *tokenPtr) {

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

static char *EchoCancellation(char *tokenPtr) {

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

static char *Volume(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int vol;
    int ret = IMP_AI_GetVol(AudioDeviceID, AudioChID, &vol);
    if(ret) return "error";
    sprintf(audioResBuf, "%d", vol);
    return audioResBuf;
  }
  int ret = IMP_AI_SetVol(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
}

static char *Gain(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int gain;
    int ret = IMP_AI_GetGain(AudioDeviceID, AudioChID, &gain);
    if(ret) return "error";
    sprintf(audioResBuf, "%d", gain);
    return audioResBuf;
  }
  int ret = IMP_AI_SetGain(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
}

static char *AlcGain(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int gain;
    int ret = IMP_AI_GetAlcGain(AudioDeviceID, AudioChID, &gain);
    if(ret) return "error";
    sprintf(audioResBuf, "%d", gain);
    return audioResBuf;
  }
  int ret = IMP_AI_SetAlcGain(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
}

// AO
static char *aoVolume(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int vol;
    int ret = IMP_AO_GetVol(AudioDeviceID, AudioChID, &vol);
    if(ret) return "error";
    sprintf(audioResBuf, "%d", vol);
    return audioResBuf;
  }
  int ret = IMP_AO_SetVol(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
}

static char *aoGain(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int gain;
    int ret = IMP_AO_GetGain(AudioDeviceID, AudioChID, &gain);
    if(ret) return "error";
    sprintf(audioResBuf, "%d", gain);
    return audioResBuf;
  }
  int ret = IMP_AO_SetGain(AudioDeviceID, AudioChID, atoi(p));
  return ret ? "error" : "ok";
}

/////////////////
// Begin video //
/////////////////

static char videoResBuf[1024];

static char *Flip(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int vflip, hflip;
    IMP_ISP_Tuning_GetISPHflip(&hflip);
    IMP_ISP_Tuning_GetISPVflip(&vflip);
    if(!hflip && !vflip) return "normal";
    if(hflip && !vflip) return "flip";
    if(!hflip && vflip) return "mirror";
    return "flip_mirror";
  }

  if(!strcmp(p, "normal")) {
    IMP_ISP_Tuning_SetISPVflip(0);
    IMP_ISP_Tuning_SetISPHflip(0);
  } else if(!strcmp(p, "flip")) {
    IMP_ISP_Tuning_SetISPVflip(1);
    IMP_ISP_Tuning_SetISPHflip(0);
  } else if(!strcmp(p, "mirror")) {
    IMP_ISP_Tuning_SetISPVflip(0);
    IMP_ISP_Tuning_SetISPHflip(1);
  } else if(!strcmp(p, "flip_mirror")) {
    IMP_ISP_Tuning_SetISPVflip(1);
    IMP_ISP_Tuning_SetISPHflip(1);
  } else {
    return "error";
  }
  return "ok";
}

static char *Contrast(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned char cont;
    IMP_ISP_Tuning_GetContrast(&cont);
    sprintf(videoResBuf, "%d", cont);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetContrast(atoi(p));
  return res ? "error": "ok";
}

static char *Brightness(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned char bri;
    IMP_ISP_Tuning_GetBrightness(&bri);
    sprintf(videoResBuf, "%d", bri);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetBrightness(atoi(p));
  return res ? "error": "ok";
}

static char *Saturation(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned char sat;
    IMP_ISP_Tuning_GetSaturation(&sat);
    sprintf(videoResBuf, "%d", sat);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetSaturation(atoi(p));
  return res ? "error": "ok";
}

static char *Sharpness(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned char sharpness;
    IMP_ISP_Tuning_GetSharpness(&sharpness);
    sprintf(videoResBuf, "%d", sharpness);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetSharpness(atoi(p));
  return res ? "error": "ok";
}

static char *AEComp(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    int comp;
    IMP_ISP_Tuning_GetAeComp(&comp);
    sprintf(videoResBuf, "%d", comp);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetAeComp(atoi(p));
  return res ? "error": "ok";
}

static char *AEItMax(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned int itMax;
    IMP_ISP_Tuning_GetAE_IT_MAX(&itMax);
    sprintf(videoResBuf, "%d", itMax);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetAe_IT_MAX(atoi(p));
  return res ? "error": "ok";
}

static char *Sinter(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) return "error";
  int res = IMP_ISP_Tuning_SetSinterStrength(atoi(p));
  return res ? "error": "ok";
}

static char *Temper(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) return "error";
  int res = IMP_ISP_Tuning_SetTemperStrength(atoi(p));
  return res ? "error": "ok";
}

static char *DPC(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned int dpc;
    IMP_ISP_Tuning_GetDPC_Strength(&dpc);
    sprintf(videoResBuf, "%d", dpc);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetDPC_Strength(atoi(p));
  return res ? "error": "ok";
}

static char *DRC(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned int drc;
    IMP_ISP_Tuning_GetDRC_Strength(&drc);
    sprintf(videoResBuf, "%d", drc);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetDRC_Strength(atoi(p));
  return res ? "error": "ok";
}

static char *HiLight(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned int strength;
    IMP_ISP_Tuning_GetHiLightDepress(&strength);
    sprintf(videoResBuf, "%d", strength);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetHiLightDepress(atoi(p));
  return res ? "error": "ok";
}

static char *AGain(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned int gain;
    IMP_ISP_Tuning_GetMaxAgain(&gain);
    sprintf(videoResBuf, "%d", gain);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetMaxAgain(atoi(p));
  return res ? "error": "ok";
}

static char *DGain(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned int gain;
    IMP_ISP_Tuning_GetMaxDgain(&gain);
    sprintf(videoResBuf, "%d", gain);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetMaxDgain(atoi(p));
  return res ? "error": "ok";
}

// New

static char *Hue(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned char hue;
    IMP_ISP_Tuning_GetBcshHue(&hue);
    sprintf(videoResBuf, "%d", hue);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetBcshHue(atoi(p));
  return res ? "error": "ok";
}

static char *Mode(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    IMPISPRunningMode mode;
    IMP_ISP_Tuning_GetISPRunningMode(&mode);
    sprintf(videoResBuf, "%d", mode);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetISPRunningMode(atoi(p));
  return res ? "error": "ok";
}

static char *Flicker(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    IMPISPAntiflickerAttr flicker;
    IMP_ISP_Tuning_GetAntiFlickerAttr(&flicker);
    sprintf(videoResBuf, "%d", flicker);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetAntiFlickerAttr(atoi(p));
  return res ? "error": "ok";
}

// This one needs work...
static char *Gamma(char *tokenPtr) {
    char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    if (!p) {
        IMPISPGamma gamma;
        if (IMP_ISP_Tuning_GetGamma(&gamma) != 0) {
            // Handle the error if needed
            return "error";
        }

        char *bufPtr = videoResBuf;
        for (int i = 0; i < 129; i++) {
            bufPtr += sprintf(bufPtr, "%hu ", gamma.gamma[i]);
        }
        *(bufPtr - 1) = '\n';
        return videoResBuf;
    }
}

// Doesn't work, or, I don't know how it works... lol
static char *SetAutoZoom(char *tokenPtr) {
    IMPISPAutoZoom zoomParams;
    char *response = "error"; // Default response is error
    char *p;
    int parsedFields = 0;

    // Parse each parameter from the input string
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    while(p != NULL && parsedFields < 8) {
        switch (parsedFields) {
            case 0: zoomParams.chan = atoi(p); break;
            case 1: zoomParams.scaler_enable = atoi(p); break;
            case 2: zoomParams.scaler_outwidth = atoi(p); break;
            case 3: zoomParams.scaler_outheight = atoi(p); break;
            case 4: zoomParams.crop_enable = atoi(p); break;
            case 5: zoomParams.crop_left = atoi(p); break;
            case 6: zoomParams.crop_top = atoi(p); break;
            case 7: zoomParams.crop_width = atoi(p); break;
            case 8: zoomParams.crop_height = atoi(p); break;
        }
        p = strtok_r(NULL, " \t\r\n", &tokenPtr);
        parsedFields++;
    }

    // Check if all parameters were provided
    if (parsedFields == 8) {
        int res = IMP_ISP_Tuning_SetAutoZoom(&zoomParams);
        if (res == 0) {
            response = "ok";
        }
    }

    return response;
}

// Example : fcrop 1 180 320 1280 720
// fcrop <enable> <top> <left> <width> <height>
static char *FrontCrop(char *tokenPtr) {
    IMPISPFrontCrop frontCropParams;
    char *response = "error"; // Default response is error
    char *p;
    int parsedFields = 0;

    // Parse each parameter from the input string
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    while (p != NULL) {
        switch (parsedFields) {
            case 0: frontCropParams.fcrop_enable = atoi(p) != 0; break;
            case 1: frontCropParams.fcrop_top = (unsigned int)atoi(p); break;
            case 2: frontCropParams.fcrop_left = (unsigned int)atoi(p); break;
            case 3: frontCropParams.fcrop_width = (unsigned int)atoi(p); break;
            case 4: frontCropParams.fcrop_height = (unsigned int)atoi(p); break;
            default: break;
        }
        p = strtok_r(NULL, " \t\r\n", &tokenPtr);
        parsedFields++;
    }

    // Get current front crop settings if no arguments are provided
    if (parsedFields == 0) {
        int res = IMP_ISP_Tuning_GetFrontCrop(&frontCropParams);
        if (res == 0) {
            static char buffer[128];
            sprintf(buffer, "Enable: %d, Top: %u, Left: %u, Width: %u, Height: %u",
                    frontCropParams.fcrop_enable,
                    frontCropParams.fcrop_top,
                    frontCropParams.fcrop_left,
                    frontCropParams.fcrop_width,
                    frontCropParams.fcrop_height);
            return buffer;
        }
    }
    // Set new front crop settings if arguments are provided
    else if (parsedFields == 5) {
        int res = IMP_ISP_Tuning_SetFrontCrop(&frontCropParams);
        if (res == 0) {
            response = "ok";
        }
    }

    return response;
}


// Example: video mask 0 1 100 100 400 400 100 100 100
// mask <channel> <mask_en> <mask_pos_top> <mask_pos_left> <mask_width> <mask_height> <Red> <Green> <Blue>
static char *Mask(char *tokenPtr) {
    IMPISPMASKAttr maskAttr;
    char *response = "error";
    char *p;
    int parsedFields = 0;
    unsigned int channel = 0; // default channel

    // Parse the channel first
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    if (p != NULL) {
        channel = atoi(p);
        if (channel >= 4) { // Assuming only 4 channels (0-3)
            return "Invalid channel";
        }
    } else {
        return "Channel not specified";
    }

    // Parse mask parameters
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    while (p != NULL) {
        switch (parsedFields) {
            case 0: maskAttr.chn0[channel].mask_en = atoi(p); break;
            case 1: maskAttr.chn0[channel].mask_pos_top = (unsigned short)atoi(p); break;
            case 2: maskAttr.chn0[channel].mask_pos_left = (unsigned short)atoi(p); break;
            case 3: maskAttr.chn0[channel].mask_width = (unsigned short)atoi(p); break;
            case 4: maskAttr.chn0[channel].mask_height = (unsigned short)atoi(p); break;
            case 5: maskAttr.chn0[channel].mask_value.mask_rgb.Red = (unsigned char)atoi(p); break;
            case 6: maskAttr.chn0[channel].mask_value.mask_rgb.Green = (unsigned char)atoi(p); break;
            case 7: maskAttr.chn0[channel].mask_value.mask_rgb.Blue = (unsigned char)atoi(p); break;
            // Add more cases if you want to handle YUV type as well
            default: break;
        }
        p = strtok_r(NULL, " \t\r\n", &tokenPtr);
        parsedFields++;
    }

    // If no parameters after channel, get mask settings
    if (parsedFields == 0) {
        int res = IMP_ISP_Tuning_GetMask(&maskAttr);
        if (res == 0) {
            static char buffer[256];
            // Assuming we are formatting for channel 0 RGB type for simplicity
            sprintf(buffer, "Enable: %d, Top: %u, Left: %u, Width: %u, Height: %u, R: %u, G: %u, B: %u",
                    maskAttr.chn0[channel].mask_en,
                    maskAttr.chn0[channel].mask_pos_top,
                    maskAttr.chn0[channel].mask_pos_left,
                    maskAttr.chn0[channel].mask_width,
                    maskAttr.chn0[channel].mask_height,
                    maskAttr.chn0[channel].mask_value.mask_rgb.Red,
                    maskAttr.chn0[channel].mask_value.mask_rgb.Green,
                    maskAttr.chn0[channel].mask_value.mask_rgb.Blue);
            return buffer;
        }
    }
    // Set new mask settings if parameters are provided
    else if (parsedFields >= 5) { // Assuming at least 5 parameters for setting the mask
        int res = IMP_ISP_Tuning_SetMask(&maskAttr);
        if (res == 0) {
            response = "ok";
        }
    }

    return response;
}

// rgain and bgain should work on manual mode?
static char *WhiteBalance(char *tokenPtr) {
    IMPISPWB wb;
    char *response = "error";
    char *p;
    int parsedFields = 0;

    // Parse parameters from the input string
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    while (p != NULL) {
        switch (parsedFields) {
            case 0: wb.mode = (isp_core_wb_mode)atoi(p); break;
            case 1: wb.rgain = (uint16_t)atoi(p); break;
            case 2: wb.bgain = (uint16_t)atoi(p); break;
            default: break;
        }
        p = strtok_r(NULL, " \t\r\n", &tokenPtr);
        parsedFields++;
    }

    // Get current WB settings if no parameters are provided
    if (parsedFields == 0) {
        int res = IMP_ISP_Tuning_GetWB(&wb);
        if (res == 0) {
            static char buffer[128];
            sprintf(buffer, "Mode: %d, Rgain: %u, Bgain: %u", wb.mode, wb.rgain, wb.bgain);
            return buffer;
        }
    }
    // Set new WB settings if parameters are provided
    else if (parsedFields >= 1) { // At least mode is required
        int res = IMP_ISP_Tuning_SetWB(&wb);
        if (res == 0) {
            response = "ok";
        }
    }

    return response;
}

static char *SensorFPS(char *tokenPtr) {
    char *response = "error";
    char *p;
    uint32_t fps_num = 0, fps_den = 0;
    int parsedFields = 0;

    // Parse parameters from the input string
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    while (p != NULL) {
        if (parsedFields == 0) {
            fps_num = (uint32_t)atoi(p);
        } else if (parsedFields == 1) {
            fps_den = (uint32_t)atoi(p);
        } else {
            break; // No more than two parameters expected
        }
        p = strtok_r(NULL, " \t\r\n", &tokenPtr);
        parsedFields++;
    }

    // Get current sensor FPS if no parameters are provided
    if (parsedFields == 0) {
        int res = IMP_ISP_Tuning_GetSensorFPS(&fps_num, &fps_den);
        if (res == 0) {
            static char buffer[64];
            sprintf(buffer, "Current FPS: %u/%u", fps_num, fps_den);
            return buffer;
        }
    }
    // Set new sensor FPS if parameters are provided
    else if (parsedFields == 2) {
        int res = IMP_ISP_Tuning_SetSensorFPS(fps_num, fps_den);
        if (res == 0) {
            response = "ok";
        }
    } else {
        return "Invalid parameters";
    }

    return response;
}

static char *BacklightComp(char *tokenPtr) {
    char *response = "error";
    char *p;
    uint32_t strength = 0;
    int parsedFields = 0;

    // Parse parameter from the input string
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    if (p != NULL) {
        strength = (uint32_t)atoi(p);
        parsedFields++;
    }

    // Get current backlight compensation strength if no parameter is provided
    if (parsedFields == 0) {
        int res = IMP_ISP_Tuning_GetBacklightComp(&strength);
        if (res == 0) {
            static char buffer[32];
            sprintf(buffer, "Current Backlight Strength: %u", strength);
            return buffer;
        }
    }
    // Set new backlight compensation strength if a parameter is provided
    else if (parsedFields == 1) {
        int res = IMP_ISP_Tuning_SetBacklightComp(strength);
        if (res == 0) {
            response = "ok";
        }
    } else {
        return "Invalid parameters";
    }

    return response;
}


///////////////////
// Command Table //
///////////////////
struct CommandTableSt {
  const char *cmd;
  char * (*func)(char *);
};

static struct CommandTableSt imp_ControlTable[] = {
  { "aihpf",      &HighPassFilter }, // on/off
  { "aiagc",      &AutoGainControl }, // gainLevel:0-31(dB) maxGain:0-90(dB)
  { "ains",       &NoiseSuppression }, // off/0 - 3
  { "aiaec",      &EchoCancellation }, // on/off
  { "aivol",      &Volume }, // -30 - 120
  { "aigain",     &Gain }, // 0 - 31
  { "aialc",      &AlcGain }, // 0 - 7
  { "aovol",      &aoVolume }, // -30 - 120
  { "aogain",     &aoGain }, // 0 - 31
  { "flip",      &Flip }, // normal/flip/mirror/flip_mirror
  { "contrast",      &Contrast }, // cont 0 - 255 (center:128)
  { "brightness",       &Brightness }, // 0 - 255 (center:128)
  { "saturation",       &Saturation }, // 0 - 255 (center:128)
  { "sharpness",     &Sharpness }, // sharp 0 - 255 (center:128)
  { "sinter",    &Sinter }, // sinter 0 - 255 (center:128)
  { "temper",    &Temper }, // temper 0 - 255 (center:128)
  { "aecomp",    &AEComp }, // aecomp 0 - 255
  { "aeitmax",   &AEItMax }, // aeitmax 0 -
  { "dpc",       &DPC }, // 0 - 255
  { "drc",       &DRC }, // 0 - 255
  { "hilight",   &HiLight }, // 0 - 10
  { "again",     &AGain }, //  0 = 1x, 32 = 2x gain, etc
  { "dgain",     &DGain }, // 0 = 1x, 32 = 2x gain, etc
  { "hue",     &Hue }, // hue 0 - 255 (center:128)
  { "ispmode",     &Mode }, // 0, 1 
  { "flicker",     &Flicker }, // 0, 1, 2
  { "gamma",     &Gamma }, // GET only
  { "autozoom",  &SetAutoZoom }, // GET only
  { "frontcrop",  &FrontCrop }, // See example in function
  { "mask",  &Mask }, // See example in function
  { "whitebalance",  &WhiteBalance }, // <mode 0-9> [rgain] [bgain]
  { "fps",  &SensorFPS }, // <fps_num> <fps_den>
  { "backlightcomp",  &BacklightComp }, // strength 0-10 
};

/*

todo:
DPS // t20 only
IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable);

IMP_ISP_Tuning_SetISPCustomMode(IMPISPTuningOpsMode mode);

IMP_ISP_Tuning_SetWB_ALGO(IMPISPAWBAlgo wb_algo);
IMP_ISP_Tuning_SetAeFreeze(IMPISPTuningOpsMode mode);
IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);
IMP_ISP_Tuning_SetAwbClust(IMPISPAWBCluster *awb_cluster);
IMP_ISP_Tuning_SetAwbCtTrend(IMPISPAWBCtTrend *ct_trend);
IMP_ISP_Tuning_SetBacklightComp(uint32_t strength);
IMP_ISP_Tuning_SetAeWeight(IMPISPWeight *ae_weight);
IMP_ISP_Tuning_SetAwbWeight(IMPISPWeight *awb_weight);
IMP_ISP_Tuning_SetAeHist(IMPISPAEHist *ae_hist);
IMP_ISP_Tuning_SetAwbHist(IMPISPAWBHist *awb_hist);
IMP_ISP_Tuning_SetAfHist(IMPISPAFHist *af_hist);
IMP_ISP_Tuning_SetAfWeight(IMPISPWeight *af_weight);
IMP_ISP_Tuning_SetAeMin(IMPISPAEMin *ae_min);
IMP_ISP_Tuning_SetAe_IT_MAX(unsigned int it_max);
IMP_ISP_Tuning_SetAeTargetList(IMPISPAETargetList *at_list);
IMP_ISP_Tuning_SetModuleControl(IMPISPModuleCtl *ispmodule);
IMP_ISP_Tuning_SetAwbCt(unsigned int *ct);
IMP_ISP_Tuning_SetCCMAttr(IMPISPCCMAttr *ccm);
IMP_ISP_Tuning_SetAeAttr(IMPISPAEAttr *ae);
IMP_ISP_Tuning_SetScalerLv(IMPISPScalerLv *scaler_level);

IMP_ISP_Tuning_EnableDefog(IMPISPTuningOpsMode mode)
IMP_ISP_Tuning_SetDefog_Strength(uint8_t *ratio);

IMP_ISP_Tuning_SetCsc_Attr(IMPISPCscAttr *attr);
IMP_ISP_Tuning_SetWdr_OutputMode(IMPISPWdrOutputMode *mode);

*/

char *IMPTune(int fd, char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(p) {
    for(int i = 0; i < sizeof(imp_ControlTable) / sizeof(struct CommandTableSt); i++) {
      if(!strcmp(p, imp_ControlTable[i].cmd)) return (*imp_ControlTable[i].func)(tokenPtr);
    }
  }

  int ch = 0;
  if(p && (!strcmp(p, "0") || !strcmp(p, "1"))) {
    ch = atoi(p);
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  }
  return "error";
}
