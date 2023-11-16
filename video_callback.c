#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>

// contrast of image effect.
extern int IMP_ISP_Tuning_SetContrast(unsigned char contrast);
extern int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast);

// brightness of image effect.
extern int IMP_ISP_Tuning_SetBrightness(unsigned char bright);
extern int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright);

// saturation of image effect.
extern int IMP_ISP_Tuning_SetSaturation(unsigned char sat);
extern int IMP_ISP_Tuning_GetSaturation(unsigned char *psat);

// sharpness of image effect.
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

// highlight intensity controls.
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

// new for majestic
extern int IMP_ISP_Tuning_SetBcshHue(unsigned char hue);
extern int IMP_ISP_Tuning_GetBcshHue(unsigned char *hue);

typedef enum {
        IMPISP_RUNNING_MODE_DAY = 0,
        IMPISP_RUNNING_MODE_NIGHT = 1,
} IMPISPRunningMode;

extern int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);
extern int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode);


typedef enum {
        IMPISP_ANTIFLICKER_DISABLE = 0,
        IMPISP_ANTIFLICKER_50HZ = 1,
        IMPISP_ANTIFLICKER_60HZ = 2,
} IMPISPAntiflickerAttr;

extern int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
extern int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);

typedef struct {
        uint16_t gamma[129];
} IMPISPGamma;

extern int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma);


///begin
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
    sprintf(videoResBuf, "%d\n", cont);
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
    sprintf(videoResBuf, "%d\n", bri);
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
    sprintf(videoResBuf, "%d\n", sat);
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
    sprintf(videoResBuf, "%d\n", sharpness);
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
    sprintf(videoResBuf, "%d\n", comp);
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
    sprintf(videoResBuf, "%d\n", itMax);
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
    sprintf(videoResBuf, "%d\n", dpc);
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
    sprintf(videoResBuf, "%d\n", drc);
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
    sprintf(videoResBuf, "%d\n", strength);
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
    sprintf(videoResBuf, "%d\n", gain);
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
    sprintf(videoResBuf, "%d\n", gain);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetMaxDgain(atoi(p));
  return res ? "error": "ok";
}

// new for majestic

static char *Hue(char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
    unsigned char hue;
    IMP_ISP_Tuning_GetBcshHue(&hue);
    sprintf(videoResBuf, "%d\n", hue);
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
    sprintf(videoResBuf, "%d\n", mode);
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
    sprintf(videoResBuf, "%d\n", flicker);
    return videoResBuf;
  }
  int res = IMP_ISP_Tuning_SetAntiFlickerAttr(atoi(p));
  return res ? "error": "ok";
}

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


// begin commands
struct CommandTableSt {
  const char *cmd;
  char * (*func)(char *);
};

static struct CommandTableSt VideoCommandTable[] = {
  { "flip",      &Flip }, // flip [normal/flip/mirror/flip_mirror]
  { "cont",      &Contrast }, // cont 0 - 255(center:128)
  { "bri",       &Brightness }, // bri 0 - 255(center:128)
  { "sat",       &Saturation }, // sat 0 - 255(center:128)
  { "sharp",     &Sharpness }, // sharp 0 - 255(center:128)
  { "sinter",    &Sinter }, // sinter 0 - 255(center:128)
  { "temper",    &Temper }, // temper 0 - 255(center:128)
  { "aecomp",    &AEComp }, // aecomp 0 - 255
  { "aeitmax",   &AEItMax }, // aeitmax 0-
  { "dpc",       &DPC }, // dpc 0 - 255
  { "drc",       &DRC }, // drc 0 - 255
  { "hilight",   &HiLight }, // hilight 0 - 10
  { "again",     &AGain }, // again 0 -
  { "dgain",     &DGain }, // dgain 0 -
  { "hue",     &Hue }, // hue
  { "mode",     &Mode }, // hue
  { "flicker",     &Flicker }, // hue
  { "gamma",     &Gamma }, // hue
};


/*

support:
IMP_ISP_Tuning_SetAutoZoom(IMPISPAutoZoom *ispautozoom);
IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable);
IMP_ISP_Tuning_SetISPRunningMode(mode);
IMP_ISP_Tuning_SetISPRunningMode error !\n");
IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);
IMP_ISP_Tuning_SetISPCustomMode(IMPISPTuningOpsMode mode);
IMP_ISP_Tuning_SetAeFreeze(IMPISPTuningOpsMode mode);
IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);
IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
IMP_ISP_Tuning_SetAwbClust(IMPISPAWBCluster *awb_cluster);
IMP_ISP_Tuning_SetAwbCtTrend(IMPISPAWBCtTrend *ct_trend);
IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void));
IMP_ISP_Tuning_SetBacklightComp(uint32_t strength);
IMP_ISP_Tuning_SetAeWeight(IMPISPWeight *ae_weight);
IMP_ISP_Tuning_SetAwbWeight(IMPISPWeight *awb_weight);
IMP_ISP_Tuning_SetWB_ALGO(IMPISPAWBAlgo wb_algo);
IMP_ISP_Tuning_SetAeHist(IMPISPAEHist *ae_hist);
IMP_ISP_Tuning_SetAwbHist(IMPISPAWBHist *awb_hist);
IMP_ISP_Tuning_SetAfHist(IMPISPAFHist *af_hist);
IMP_ISP_Tuning_SetAfWeight(IMPISPWeight *af_weight);
IMP_ISP_Tuning_SetAeMin(IMPISPAEMin *ae_min);
IMP_ISP_Tuning_SetAe_IT_MAX(unsigned int it_max);
IMP_ISP_Tuning_SetAeTargetList(IMPISPAETargetList *at_list);
IMP_ISP_Tuning_SetModuleControl(IMPISPModuleCtl *ispmodule);
IMP_ISP_Tuning_SetFrontCrop(IMPISPFrontCrop *ispfrontcrop);
IMP_ISP_Tuning_SetMask(IMPISPMASKAttr *mask);
IMP_ISP_Tuning_SetAwbCt(unsigned int *ct);
IMP_ISP_Tuning_SetCCMAttr(IMPISPCCMAttr *ccm);
IMP_ISP_Tuning_SetAeAttr(IMPISPAEAttr *ae);
IMP_ISP_Tuning_SetScalerLv(IMPISPScalerLv *scaler_level);

IMP_ISP_Tuning_EnableDefog(IMPISPTuningOpsMode mode)
IMP_ISP_Tuning_SetDefog_Strength(uint8_t *ratio);

IMP_ISP_Tuning_SetCsc_Attr(IMPISPCscAttr *attr);
IMP_ISP_Tuning_SetWdr_OutputMode(IMPISPWdrOutputMode *mode);

*/

char *VideoTune(int fd, char *tokenPtr) {

  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(p) {
    for(int i = 0; i < sizeof(VideoCommandTable) / sizeof(struct CommandTableSt); i++) {
      if(!strcmp(p, VideoCommandTable[i].cmd)) return (*VideoCommandTable[i].func)(tokenPtr);
    }
  }

  int ch = 0;
  if(p && (!strcmp(p, "0") || !strcmp(p, "1"))) {
    ch = atoi(p);
    p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  }
  return "error";
}
