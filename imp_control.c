#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "imp_control_audio.h"
#include "imp_control_video.h"
#include "include/imp_osd.h"

char* fullDemo(char *tokenPtr);

static char *ShowHelp(char *tokenPtr) {
    static char response[] =
        "Usage: imp-control [command] [parameters]\n"
        "       Use without parameters to retrieve current values.\n"
        "Available commands:\n"
        "Command              Parameters                                  Description\n"
        "-------              ----------                                   -----------\n"
        "aihpf                [on/off]                                     High Pass Filter\n"
        "aiagc                [off/gainLevel compGaindB]                   Auto Gain Control\n"
        "ains                 [off/0-3]                                    Noise Suppression\n"
        "aiaec                [on/off]                                     Echo Cancellation\n"
        "aivol                [-30-120]                                    Audio Input Volume\n"
        "aigain               [0-31]                                       Audio Input Gain\n"
        "aialc                [0-7]                                        Audio Input ALC Gain\n"
        "aovol                [-30-120]                                    Audio Output Volume\n"
        "aogain               [0-31]                                       Audio Output Gain\n"
        "flip                 [normal/flip/mirror/flip_mirror]             Image Flip\n"
        "contrast             [0-255]                                      Contrast\n"
        "brightness           [0-255]                                      Brightness\n"
        "saturation           [0-255]                                      Saturation\n"
        "sharpness            [0-255]                                      Sharpness\n"
        "sinter               [0-255]                                      Sinter Strength\n"
        "temper               [0-255]                                      Temper Strength\n"
        "aecomp               [0-255]                                      AE Compensation\n"
        "aeitmax              [value]                                      AE Max Parameters\n"
        "dpc                  [0-255]                                      DPC Strength\n"
        "drc                  [0-255]                                      DRC Strength\n"
        "hilight              [0-10]                                       Highlight Intensity\n"
        "again                [value]                                      Analog Gain\n"
        "dgain                [value]                                      Digital Gain\n"
        "hue                  [0-255]                                      Hue\n"
        "ispmode              [0/1]                                        ISP Mode (Day/Night)\n"
        "flicker              [0/1/2]                                      Anti-Flicker\n"
        "whitebalance         [mode] [rgain] [bgain]                       White Balance\n"
        "sensorfps            [fps_num] [fps_den]                          Sensor FPS\n"
        "backlightcomp        [strength]                                   Backlight Compensation Strength\n"
        "defogstrength        [0-255]                                      Defog Strength\n"
        "framerate            [encChn] [<frmRateNum> <frmRateDen>]         Sensor Frame Rate\n"
        "gopattr              [encChn] [<gopLength>]                       GOP Attributes\n"
        "setbitrate           [encChn] <iTargetBitRate> <iMaxBitRate>      Set Bit Rate\n"
        "setgoplength         [encChn] <iGopLength>                        Set GOP Length\n"
        "setqp                [encChn] <iQP>                               Set QP\n"
        "setqpbounds          [encChn] <iMinQP> <iMaxQP>                   Set QP Bounds\n"
        "setqpipdelta         [encChn] <uIPDelta>                          Set QP IP Delta\n"
        "rcmode               [encChn] <rcMode> [<mode specific parameters>]\n"
        "                                                                  Set/Get Rate Control Mode\n"
        "aemin                [min_it] [min_again] [min_it_short] [min_again_short]\n"
        "                                                                  Set AE Min Parameters\n"
        "autozoom             [ch] [scaler enable] [scale w] [scale h] [crop enable] [crop left] [crop top] [crop w] [crop h]\n"
        "                                                                  Set Auto Zoom\n"
        "frontcrop            [enable] [top] [left] [width] [height]       Set Front Crop\n"
        "mask                 [ch] [enable] [top] [left] [width] [height] [green] [blue] [red]\n"
        "                                                                  Set Mask\n"
        "getosdattr           [handle]                                     Get OSD Region Attributes\n"
        "getosdgrpattr        [handle] [group number]                      Get OSD Group Region Attributes\n"
        "getgamma                                                          Get Gamma Values\n"
        "getevattr                                                         Get EV Attributes\n"
        "getaeluma                                                         Get AE Luma\n"
        "getawbct                                                          Get AWB CT\n"
        "getafmetrics                                                      Get AF Metrics\n"
        "gettotalgain                                                      Get Total Gain\n"
        "getaeattr                                                         Get AE Attributes\n"
        "getimpversion                                                     Get IMP Version\n"
        "getcpuinfo                                                        Get CPU Info\n"
        "help                                                              Show this help message\n"
        "full_demo                                                         Run a full demo";
    return response;
}

struct CommandTableSt {
  const char *cmd;
  char * (*func)(char *);
};

static struct CommandTableSt imp_ControlTable[] = {
  { "full_demo", &fullDemo }, // Full demo
  { "help", &ShowHelp }, // No parameters
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
  { "autozoom",  &SetAutoZoom }, // See example in function
  { "frontcrop",  &FrontCrop }, // See example in function
  { "mask",  &Mask }, // See example in function
  { "whitebalance",  &WhiteBalance }, // <mode 0-9> [rgain] [bgain]
  { "sensorfps",  &SensorFPS }, // <fps_num> <fps_den>
  { "backlightcomp",  &BacklightComp }, // strength 0-10
  { "aemin", &AeMin }, // <min_it> <min_again> <min_it_short> <min_again_short>
  { "defogstrength", &DefogStrength }, // 0 - 255
  { "framerate", &SetAndGetFrameRate },
  { "rcmode", &SetAndGetRcMode },
  { "gopattr", &SetAndGetGopAttr },
  // Read only:
  { "getgamma",     &Gamma },
  { "getevattr", &GetEVAttributes },
  { "getaeluma", &GetAeLuma },
  { "getawbct", &AwbCt },
  { "getafmetrics", &GetAFMetrics },
  { "gettotalgain", &GetTotalGain },
  { "getaeattr", &GetAeAttr },
  { "getimpversion", &GetIMPVersion },
  { "getcpuinfo", &GetCPUInfo },
  { "getosdattr", &GetOSDRegionAttributes }, // Usage: getosdattr <handle>
  { "getosdgrpattr", &GetOSDGroupRegionAttributes }, // Usage: getosdgrpattr <handle> <group number>
  // Set Only:
  { "setbitrate", &SetBitRate },
  { "setgoplength", &SetGopLength },
  { "setqp", &SetChnQp },
  { "setqpbounds", &SetChnQpBounds },
  { "setqpipdelta", &SetChnQpIPDelta },
};

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
  return "Usage: [command] [parameters] (Use without parameters to retrieve current values.)\nUse 'help' to get a list of commands";
}
