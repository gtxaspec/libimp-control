#ifndef IMP_CONTROL__H
#define IMP_CONTROL__H

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

char *Flip(char *tokenPtr);
char *Contrast(char *tokenPtr);
char *Brightness(char *tokenPtr);
char *Saturation(char *tokenPtr);
char *Sharpness(char *tokenPtr);
char *AEComp(char *tokenPtr);
char *AEItMax(char *tokenPtr);
char *Sinter(char *tokenPtr);
char *Temper(char *tokenPtr);
char *DPC(char *tokenPtr);
char *DRC(char *tokenPtr);
char *HiLight(char *tokenPtr);
char *AGain(char *tokenPtr);
char *DGain(char *tokenPtr);
char *Hue(char *tokenPtr);
char *Mode(char *tokenPtr);
char *Flicker(char *tokenPtr);
char *Gamma(char *tokenPtr);
char *SetAutoZoom(char *tokenPtr);
char *FrontCrop(char *tokenPtr);
char *Mask(char *tokenPtr);
char *WhiteBalance(char *tokenPtr);
char *SensorFPS(char *tokenPtr);
char *BacklightComp(char *tokenPtr);
char *GetEVAttributes(char *tokenPtr);
char *GetAeLuma(char *tokenPtr);
char *AwbCt(char *tokenPtr);
char *GetAFMetrics(char *tokenPtr);
char *GetTotalGain(char *tokenPtr);
char *DefogStrength(char *tokenPtr);
char *AeMin(char *tokenPtr);
char *GetAeAttr(char *tokenPtr);
char *SetAndGetFrameRate(char *tokenPtr);
char *SetAndGetRcMode(char *tokenPtr);
char *SetAndGetGopAttr(char *tokenPtr);
char *SetBitRate(char *tokenPtr);
char *SetGopLength(char *tokenPtr);
char *SetChnQp(char *tokenPtr);
char *SetChnQpBounds(char *tokenPtr);
char *SetChnQpIPDelta(char *tokenPtr);
char *showOSD(char *tokenPtr);
char *setOSDpos(char *tokenPtr);
char *setOSDcover(char *tokenPtr);
char *setOSDalpha(char *tokenPtr);
char *ControlFisheyeStatus(char *tokenPtr);

char *GetOSDRegionAttributes(char *tokenPtr);
char *GetOSDGroupRegionAttributes(char *tokenPtr);
char *GetChannelEncodingType(char *tokenPtr);
char *GetDeviceID();
char *GetModelFamily();
char *GetSysVersion();
char *GetIMPVersion(char *tokenPtr);
char *GetCPUInfo(char *tokenPtr);

char *Test(char *tokenPtr);
char* fullDemo(char *tokenPtr);


static char *ShowHelp(char *tokenPtr) {
    static char response[] =
        "Usage: imp-control [command] <parameters> <-h>\n"
        "       Use without parameters to retrieve current values.\n"
        "       Add '-h' to the end of a command to get full usage and syntax.\n\n"
        "Available commands:\n"
        "-------------------   -------------------   -------------------   -------------------\n"
        "aihpf                 aeitmax               setbitrate            setbitrate         \n"
        "aiagc                 dpc                   rcmode                setgoplength       \n"
        "ains                  drc                   gopattr               setqp              \n"
        "aiaec                 hilight               getgamma              setqpbounds        \n"
        "aivol                 again                 getevattr             setqpipdelta       \n"
        "aigain                dgain                 getaeluma             setosdalpha        \n"
        "aialc                 hue                   getawbct              setosdpos          \n"
        "aovol                 ispmode               getafmetrics                             \n"
        "aogain                flicker               gettotalgain          help               \n"
        "aohpf                 autozoom              getaeattr             getchnencoder      \n"
        "flip                  frontcrop             getimpversion         setosdcover        \n"
        "contrast              mask                  getcpuinfo                               \n"
        "brightness            whitebalance          getosdattr                               \n"
        "saturation            sensorfps             getosdgrpattr                            \n"
        "sharpness             backlightcomp         getdeviceid                              \n"
        "sinter                aemin                 getmodelfamily                           \n"
        "temper                defogstrrength        getsysversion                            \n"
        "aecomp                framerate             full_demo";
    return response;
}
// split into channel group, future.

struct CommandTableSub {
	const char *cmd;
	char * (*func)(char *);
};

static struct CommandTableSub imp_ControlTable[] = {
	{ "full_demo", &fullDemo }, // Full demo
	{ "help", &ShowHelp }, // No parameters
	{ "aihpf",      &HighPassFilter }, // on/off
	{ "aiagc",      &AutoGainControl }, // gainLevel:0-31(dB) maxGain:0-90(dB)
	{ "ains",       &NoiseSuppression }, // off/0 - 3
	{ "aiaec",      &EchoCancellation }, // on/off
	{ "aivol",      &Volume }, // -30 - 120
	{ "aigain",     &Gain }, // 0 - 31
	{ "aialc",      &AlcGain }, // 0 - 7
	{ "aohpf",      &aoHighPassFilter }, // on/off
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
	{ "setfisheye", &ControlFisheyeStatus },
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
	{ "getdeviceid", &GetDeviceID },
	{ "getmodelfamily", &GetModelFamily },
	{ "getsysversion", &GetSysVersion },
	{ "getchnencoder", &GetChannelEncodingType },
	// Set Only:
	{ "setbitrate", &SetBitRate },
	{ "setgoplength", &SetGopLength },
	{ "setqp", &SetChnQp },
	{ "setqpbounds", &SetChnQpBounds },
	{ "setqpipdelta", &SetChnQpIPDelta },
	{ "setosdalpha", &setOSDalpha},
	{ "setosdshow", &showOSD},
	{ "setosdpos", &setOSDpos},
	{ "setosdcover", &setOSDcover},
	// Test
	{ "test", &Test},
};

#endif // IMP_CONTROL_H

