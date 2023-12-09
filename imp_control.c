#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "imp_control_audio.h"
#include "imp_control_video.h"
#include "imp_control_util.h"
#include "include/imp_osd.h"

char* fullDemo(char *tokenPtr);

static char *ShowHelp(char *tokenPtr) {
	static char response[] =
			"Usage: imp-control [command] [parameters]\n"
			"       Use without parameters to retrieve current values.\n"
			"Available commands:\n"
			"Command              Parameters\n"
			"-------              ----------\n"
			"aihpf                [0/1]\n"
			"aiagc                [0/gainLevel compGaindB]\n"
			"ains                 [-1/0-3]\n"
			"aiaec                [0/1]\n"
			"aivol                [-30-120]\n"
			"aigain               [0-31]\n"
			"aialc                [0-7]\n"
			"aovol                [-30-120]\n"
			"aogain               [0-31]\n"
			"flip                 [0/1/2/3]\n"
			"contrast             [0-255]\n"
			"brightness           [0-255]\n"
			"saturation           [0-255]\n"
			"sharpness            [0-255]\n"
			"sinter               [0-255]\n"
			"temper               [0-255]\n"
			"aecomp               [0-255]\n"
			"aeitmax              [value]\n"
			"dpc                  [0-255]\n"
			"drc                  [0-255]\n"
			"hilight              [0-10]\n"
			"again                [value]\n"
			"dgain                [value]\n"
			"hue                  [0-255]\n"
			"ispmode              [0/1]\n"
			"flicker              [0/1/2]\n"
			"whitebalance         [mode] [rgain] [bgain]\n"
			"sensorfps            [fps_num] [fps_den]\n"
			"backlightcomp        [strength]\n"
			"defogstrength        [0-255]\n"
			"framerate            [encChn] [<frmRateNum> <frmRateDen>]\n"
			"gopattr              [encChn] [<gopLength>]\n"
			"setbitrate           [encChn] <iTargetBitRate> <iMaxBitRate>\n"
			"setgoplength         [encChn] <iGopLength>\n"
			"setqp                [encChn] <iQP>\n"
			"setqpbounds          [encChn] <iMinQP> <iMaxQP>\n"
			"setqpipdelta         [encChn] <uIPDelta>\n"
			"rcmode               [encChn] <rcMode> [<mode specific parameters>]\n"
			"aemin                [min_it] [min_again] [min_it_short] [min_again_short]\n"
			"autozoom             [ch] [scaler enable] [scale w] [scale h] [crop enable] [crop left] [crop top] [crop w] [crop h]\n"
			"frontcrop            [enable] [top] [left] [width] [height]\n"
			"mask                 [ch] [enable] [top] [left] [width] [height] [green] [blue] [red]\n"
			"getosdattr           [handle]\n"
			"getosdgrpattr        [handle] [group number]\n"
			"getgamma\n"
			"getevattr\n"
			"getaeluma\n"
			"getawbct\n"
			"getafmetrics\n"
			"gettotalgain\n"
			"getaeattr\n"
			"getimpversion\n"
			"getsysversion\n"
			"getcpuinfo\n"
			"getdeviceid\n"
			"getmodelfamily\n"
			"help\n"
			"full_demo";
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
