#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imp_control_video.h"
#include "imp_control_util.h"
#include "include/imp_encoder.h"

char *Flip(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) {
		int vflip, hflip;
		IMP_ISP_Tuning_GetISPHflip(&hflip);
		IMP_ISP_Tuning_GetISPVflip(&vflip);

		if (!hflip && !vflip) {
			return "0"; // No flip, no mirror
		} else if (hflip && !vflip) {
			return "1"; // Mirror only
		} else if (!hflip && vflip) {
			return "2"; // Flip only
		} else if (hflip && vflip) {
			return "3"; // Flip and mirror
		}
	}

	int flipValue = atoi(p);
	switch (flipValue) {
		case 0: // No flip, no mirror
			IMP_ISP_Tuning_SetISPVflip(0);
			IMP_ISP_Tuning_SetISPHflip(0);
			break;
		case 1: // Mirror only
			IMP_ISP_Tuning_SetISPVflip(0);
			IMP_ISP_Tuning_SetISPHflip(1);
			break;
		case 2: // Flip only
			IMP_ISP_Tuning_SetISPVflip(1);
			IMP_ISP_Tuning_SetISPHflip(0);
			break;
		case 3: // Flip and mirror
			IMP_ISP_Tuning_SetISPVflip(1);
			IMP_ISP_Tuning_SetISPHflip(1);
			break;
		default:
			return "Error: Invalid value specified";
	}
	return RESULT(res, p);	
}

char *Contrast(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned char cont;
	IMP_ISP_Tuning_GetContrast(&cont);
	sprintf(response, "%d", cont);
	return response;
  }
  int res = IMP_ISP_Tuning_SetContrast(atoi(p));
  return RESULT(res, p);
}

char *Brightness(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned char bri;
	IMP_ISP_Tuning_GetBrightness(&bri);
	sprintf(response, "%d", bri);
	return response;
  }
  int res = IMP_ISP_Tuning_SetBrightness(atoi(p));
  return RESULT(res, p);
}

char *Saturation(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned char sat;
	IMP_ISP_Tuning_GetSaturation(&sat);
	sprintf(response, "%d", sat);
	return response;
  }
  int res = IMP_ISP_Tuning_SetSaturation(atoi(p));
  return RESULT(res, p);
}

char *Sharpness(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned char sharpness;
	IMP_ISP_Tuning_GetSharpness(&sharpness);
	sprintf(response, "%d", sharpness);
	return response;
  }
  int res = IMP_ISP_Tuning_SetSharpness(atoi(p));
  return RESULT(res, p);
}

char *AEComp(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	int comp;
	IMP_ISP_Tuning_GetAeComp(&comp);
	sprintf(response, "%d", comp);
	return response;
  }
  int res = IMP_ISP_Tuning_SetAeComp(atoi(p));
  return RESULT(res, p);
}

char *AEItMax(char *tokenPtr) {
#ifndef CONFIG_T20
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned int itMax;
	IMP_ISP_Tuning_GetAE_IT_MAX(&itMax);
	sprintf(response, "%d", itMax);
	return response;
  }
  int res = IMP_ISP_Tuning_SetAe_IT_MAX(atoi(p));
  return RESULT(res, p);
#else
  return "not supported on >T20";
#endif
}

char *Sinter(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) return "error";
  int res = IMP_ISP_Tuning_SetSinterStrength(atoi(p));
  return RESULT(res, p);
}

char *Temper(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) return "error";
  int res = IMP_ISP_Tuning_SetTemperStrength(atoi(p));
  return RESULT(res, p);
}

char *DPC(char *tokenPtr) {
#ifndef CONFIG_T20
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned int dpc;
	IMP_ISP_Tuning_GetDPC_Strength(&dpc);
	sprintf(response, "%d", dpc);
	return response;
  }
  int res = IMP_ISP_Tuning_SetDPC_Strength(atoi(p));
  return RESULT(res, p);
#else
  return "not supported on >T20";
#endif
}

char *DRC(char *tokenPtr) {
#ifndef CONFIG_T20
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned int drc;
	IMP_ISP_Tuning_GetDRC_Strength(&drc);
	sprintf(response, "%d", drc);
	return response;
  }
  int res = IMP_ISP_Tuning_SetDRC_Strength(atoi(p));
  return RESULT(res, p);
#else
  return "not supported on >T20";
#endif
}

char *HiLight(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned int strength;
	IMP_ISP_Tuning_GetHiLightDepress(&strength);
	sprintf(response, "%d", strength);
	return response;
  }
  int res = IMP_ISP_Tuning_SetHiLightDepress(atoi(p));
  return RESULT(res, p);
}

char *AGain(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned int gain;
	IMP_ISP_Tuning_GetMaxAgain(&gain);
	sprintf(response, "%d", gain);
	return response;
  }
  int res = IMP_ISP_Tuning_SetMaxAgain(atoi(p));
  return RESULT(res, p);
}

char *DGain(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned int gain;
	IMP_ISP_Tuning_GetMaxDgain(&gain);
	sprintf(response, "%d", gain);
	return response;
  }
  int res = IMP_ISP_Tuning_SetMaxDgain(atoi(p));
  return RESULT(res, p);
}

char *Hue(char *tokenPtr) {
#ifndef CONFIG_T20
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	unsigned char hue;
	IMP_ISP_Tuning_GetBcshHue(&hue);
	sprintf(response, "%d", hue);
	return response;
  }
  int res = IMP_ISP_Tuning_SetBcshHue(atoi(p));
  return RESULT(res, p);
#else
  return "not supported on >T20";
#endif
}

char *Mode(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	IMPISPRunningMode mode;
	IMP_ISP_Tuning_GetISPRunningMode(&mode);
	sprintf(response, "%d", mode);
	return response;
  }
  int res = IMP_ISP_Tuning_SetISPRunningMode(atoi(p));
  return RESULT(res, p);
}

char *Flicker(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	IMPISPAntiflickerAttr flicker;
	IMP_ISP_Tuning_GetAntiFlickerAttr(&flicker);
	sprintf(response, "%d", flicker);
	return response;
  }
  int res = IMP_ISP_Tuning_SetAntiFlickerAttr(atoi(p));
  return RESULT(res, p);
}

char *BacklightComp(char *tokenPtr) {
#ifndef CONFIG_T20
  uint32_t strength = 0;
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if(!p) {
	uint32_t strength;
	IMP_ISP_Tuning_GetBacklightComp(&strength);
	sprintf(response, "%d", strength);
	return response;
  }
  int res = IMP_ISP_Tuning_SetBacklightComp(atoi(p));
  return RESULT(res, p);
#else
  return "not supported on >T20";
#endif
}

char *DefogStrength(char *tokenPtr) {
    #ifndef CONFIG_T20
    char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
    uint8_t ratio;
    if (!p) {
        int32_t getRet = IMP_ISP_Tuning_GetDefog_Strength(&ratio);
        if (getRet) return "error";
        sprintf(response, "%u", ratio);
        return response;
    }
    ratio = (uint8_t)atoi(p);
    int32_t setRet = IMP_ISP_Tuning_SetDefog_Strength(&ratio);
    return RESULT(setRet, p);
    #else
    return "not supported on >T20";
    #endif
}

char *SetAndGetGopAttr(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn;
	IMPEncoderGopAttr gopAttr;

	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Encoder channel missing.";

if (p != NULL && strcmp(p, "-h") == 0)
{
    return 
        "Usage: gopattr [encChn] [gopLength]\n"
        "Parameters:\n"
        "  encChn: Encoder Channel number to set the GOP attribute for.\n"
        "  gopLength: Length of the Group of Pictures (GOP).";
}

	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);

	if (p) {
		gopAttr.uGopLength = (uint16_t)atoi(p);
		if (IMP_Encoder_SetChnGopAttr(encChn, &gopAttr) != 0) {
			return "Error: Set GOP Attribute Failed";
		}
		return "GOP attribute set successfully";
	} else {
		if (IMP_Encoder_GetChnGopAttr(encChn, &gopAttr) != 0) {
			return "Error: Get GOP Attribute Failed";
		}
		//snprintf(response, sizeof(response), "GOP length: %u", gopAttr.uGopLength);
		snprintf(response, sizeof(response), "%u", gopAttr.uGopLength);
		return response;
	}
	#else
	  return "not supported on >T20";
	#endif
}

// rgain and bgain should work on manual mode?
char *WhiteBalance(char *tokenPtr) {
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
			  return RESULT(res, p);
		}
	}

	return response;
}

char *SensorFPS(char *tokenPtr) {
	char *response = "error";
	char *p;
	uint32_t fps_num = 0, fps_den = 1; // Initialize fps_den to 1 by default
	int parsedFields = 0;

	// Parse parameters from the input string
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
{
    return 
        "Usage: sensorfps [fps_num]\n"
        "Parameter:\n"
        "  fps_num: The frame rate number to set for the sensor.\n"
        "           It specifies the number of frames per second.";
}

	while (p != NULL) {
		if (parsedFields == 0) {
			fps_num = (uint32_t)atoi(p);
		} else if (parsedFields == 1) {
			fps_den = (uint32_t)atoi(p); // Update fps_den only if the second parameter is provided
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
			sprintf(buffer, "%u", fps_num);
			return buffer;
		}
	}
	// Set new sensor FPS if parameters are provided
	else if (parsedFields == 1) {
		int res = IMP_ISP_Tuning_SetSensorFPS(fps_num, fps_den);
		if (res == 0) {
			  return RESULT(res, p);
		}
	} else {
		return "Invalid parameters";
	}

	return response;
}

char *SetAndGetFrameRate(char *tokenPtr) {
	int encChn;
	IMPEncoderFrmRate frmRate;

	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return "Error: encoder channel missing.";

if (p != NULL && strcmp(p, "-h") == 0)
{
    return 
        "Usage: framerate [encChn] [frmRateNum] <frmRateDen>\n"
        "Parameters:\n"
        "  encChn: Encoder Channel number to set the framerate for.\n"
        "  frmRateNum: Desired frame rate number.\n"
		"  frmRateDen: Frame rate number denominator.  This value may be omited and the default value of 1 will be used.";
}
	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);

	if (p) {
		// Set frame rate
		frmRate.frmRateNum = atoi(p);
		frmRate.frmRateDen = 1; // Default denominator to 1

		p = strtok_r(NULL, " \t\r\n", &tokenPtr);
		if (p) {
			frmRate.frmRateDen = atoi(p); // Update denominator if provided
		}

		if (IMP_Encoder_SetChnFrmRate(encChn, &frmRate) != 0) {
			return "Error: Set Frame Rate Failed";
		}
		snprintf(response, sizeof(response), "%u", frmRate.frmRateNum);
		return response;
	} else {
		// Get frame rate
		if (IMP_Encoder_GetChnFrmRate(encChn, &frmRate) != 0) {
			return "Error: Get Frame Rate Failed";
		}
		snprintf(response, sizeof(response), "%u", frmRate.frmRateNum);
		return response;
	}
}

char *SetBitRate(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn, iTargetBitRate, iMaxBitRate;
	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return "Usage: <encChn> <iTargetBitRate> <iMaxBitRate>";

	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing iTargetBitRate";
	iTargetBitRate = atoi(p);

	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing iMaxBitRate";
	iMaxBitRate = atoi(p);

	if (IMP_Encoder_SetChnBitRate(encChn, iTargetBitRate, iMaxBitRate) != 0) {
		return "Error: Set Bit Rate Failed";
	}
	return "Bit rate set successfully";
	#else
		return "not supported on >T20";
	#endif
}

char *SetGopLength(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn, iGopLength;
	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return "Usage: <encChn> <iGopLength>";

	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing iGopLength";
	iGopLength = atoi(p);

	if (IMP_Encoder_SetChnGopLength(encChn, iGopLength) != 0) {
		return "Error: Set GOP Length Failed";
	}
	return "GOP length set successfully";
	#else
		return "not supported on >T20";
	#endif
}

char *SetChnQp(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn, iQP;
	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return "Usage: <encChn> <iQP>";

	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing iQP";
	iQP = atoi(p);

	if (IMP_Encoder_SetChnQp(encChn, iQP) != 0) {
		return "Error: Set QP Failed";
	}
	return "QP set successfully";
	#else
		return "not supported on >T20";
	#endif
}

char *SetChnQpBounds(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn, iMinQP, iMaxQP;
	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return "Usage: <encChn> <iMinQP> <iMaxQP>";

	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing iMinQP";
	iMinQP = atoi(p);

	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing iMaxQP";
	iMaxQP = atoi(p);

	if (IMP_Encoder_SetChnQpBounds(encChn, iMinQP, iMaxQP) != 0) {
		return "Error: Set QP Bounds Failed";
	}
	return "QP bounds set successfully";
	#else
		return "not supported on >T20";
	#endif
}

char *SetChnQpIPDelta(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn, uIPDelta;
	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return "Usage: <encChn> <uIPDelta>";

	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing uIPDelta";
	uIPDelta = atoi(p);

	if (IMP_Encoder_SetChnQpIPDelta(encChn, uIPDelta) != 0) {
		return "Error: Set QP IP Delta Failed";
	}
	return "QP IP Delta set successfully";
	#else
		return "not supported on >T20";
	#endif
}

// Example: autozoom 0 1 1920 1080 1 800 200 640 480
char *SetAutoZoom(char *tokenPtr) {
	#ifndef CONFIG_T20
	IMPISPAutoZoom zoomParams;
	char *response = "error"; // Default response is error
	char *p;
	int parsedFields = 0;

	// Check for help argument
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0)
	{
			return "Usage: SetAutoZoom [chan] [scaler_enable] [scaler_outwidth] [scaler_outheight] [crop_enable] [crop_left] [crop_top] [crop_width] [crop_height]\n"
						"chan: Channel number\n"
						"scaler_enable: 0 (disable) or 1 (enable) scaler\n"
						"scaler_outwidth, scaler_outheight: Scaler output dimensions\n"
						"crop_enable: 0 (disable) or 1 (enable) crop\n"
						"crop_left, crop_top: Crop region start coordinates\n"
						"crop_width, crop_height: Crop region dimensions\n"
						"WARNING: AutoZoom requires increased performance, recommended 240Mhz ISP Clock";
	}

	// Parse each parameter from the input string
	while(p != NULL && parsedFields < 9) {
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
	if (parsedFields == 9) {
		int res = IMP_ISP_Tuning_SetAutoZoom(&zoomParams);
		if (res == 0) {
			return RESULT(res, p);
		}
	}

	return response;
#else
  return "not supported on >T20";
#endif
}

// Example : fcrop 1 180 320 1280 720
// fcrop <enable> <top> <left> <width> <height>
char *FrontCrop(char *tokenPtr) {
	#ifndef CONFIG_T20
	IMPISPFrontCrop frontCropParams;
	char *response = "error"; // Default response is error
	char *p;
	int parsedFields = 0;

	p = strtok_r(NULL, " \t\r\n", &tokenPtr);

	// Check for help argument
	if (p != NULL && strcmp(p, "-h") == 0)
	{
			return "Usage: FrontCrop [enable] [top] [left] [width] [height]\n"
						"Enable: 0 (disable) or 1 (enable)\n"
						"Top, Left, Width, Height: Integer values specifying crop region";
	}

	// Parse each parameter from the input string
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
			//sprintf(buffer, "Enable: %d, Top: %u, Left: %u, Width: %u, Height: %u",
			sprintf(buffer, "%d %u %u %u %u",
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
			return RESULT(res, p);
		}
	}

	return response;
#else
  return "not supported on >T20";
#endif
}

// Example: video mask 0 1 100 100 400 400 100 100 100
// mask <channel> <mask_en> <mask_pos_top> <mask_pos_left> <mask_width> <mask_height> <Red> <Green> <Blue>
char *Mask(char *tokenPtr) {
	#ifndef CONFIG_T20
	IMPISPMASKAttr maskAttr;
	char *response = "error";
	char *p;
	int parsedFields = 0;
	unsigned int channel = 0; // default channel

	// Check for help argument
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p != NULL && strcmp(p, "-h") == 0) {
		return "Usage: Mask [channel] [mask_en] [mask_pos_top] [mask_pos_left] [mask_width] [mask_height] [Red] [Green] [Blue]\n"
			   "channel: Channel number\n"
			   "mask_en: 0 (disable) or 1 (enable) mask\n"
			   "mask_pos_top, mask_pos_left: Mask position coordinates\n"
			   "mask_width, mask_height: Mask dimensions\n"
			   "Red, Green, Blue: Mask color values (0-255)";
	}

	// Parse the channel
	if (p != NULL) {
		channel = atoi(p);
		parsedFields++;
	} else {
		return "Channel not specified";
	}

	// Continue parsing if there are more parameters
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	while (p != NULL) {
		switch (parsedFields) {
			case 1: maskAttr.chn0[channel].mask_en = atoi(p); break;
			case 2: maskAttr.chn0[channel].mask_pos_top = (unsigned short)atoi(p); break;
			case 3: maskAttr.chn0[channel].mask_pos_left = (unsigned short)atoi(p); break;
			case 4: maskAttr.chn0[channel].mask_width = (unsigned short)atoi(p); break;
			case 5: maskAttr.chn0[channel].mask_height = (unsigned short)atoi(p); break;
			case 6: maskAttr.chn0[channel].mask_value.mask_rgb.Red = (unsigned char)atoi(p); break;
			case 7: maskAttr.chn0[channel].mask_value.mask_rgb.Green = (unsigned char)atoi(p); break;
			case 8: maskAttr.chn0[channel].mask_value.mask_rgb.Blue = (unsigned char)atoi(p); break;
			default: break;
		}
		p = strtok_r(NULL, " \t\r\n", &tokenPtr);
		parsedFields++;
	}

	// Get mask settings if only channel is provided
	if (parsedFields == 1) {
		int res = IMP_ISP_Tuning_GetMask(&maskAttr);
		if (res == 0) {
			static char buffer[256];
			sprintf(buffer, "%d %u %u %u %u %u %u %u",
					maskAttr.chn0[channel].mask_en,
					maskAttr.chn0[channel].mask_pos_top,
					maskAttr.chn0[channel].mask_pos_left,
					maskAttr.chn0[channel].mask_width,
					maskAttr.chn0[channel].mask_height,
					maskAttr.chn0[channel].mask_value.mask_rgb.Red,
					maskAttr.chn0[channel].mask_value.mask_rgb.Green,
					maskAttr.chn0[channel].mask_value.mask_rgb.Blue);
			return buffer;
		} else {
			return "Failed to get mask status";
		}
	}

	// Set new mask settings if full parameters are provided
	if (parsedFields >= 5) {
		int res = IMP_ISP_Tuning_SetMask(&maskAttr);
		if (res == 0) {
			return RESULT(res, p);
		}
	}

	return response;
	#else
	return "not supported on >T20";
	#endif

}char *SetAndGetRcMode(char *tokenPtr) {
	int encChn;
	IMPEncoderAttrRcMode rcMode;

	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return "Usage: <encChn> <rcMode> [<mode specific parameters>]\n"
				   "rcModes:\n"
				   "0: FIXQP: <iInitialQP>\n"
				   "2: CBR: <iInitialQP> <iMinQP> <iMaxQP> <bitrate>\n"
				   "3: VBR: <iInitialQP> <iMinQP> <iMaxQP> <bitrate> <maxBitRate>\n"
				   "4: CAPPED_VBR: <iInitialQP> <iMinQP> <iMaxQP> <bitrate> <maxBitRate> <maxPSNR>\n"
				   "8: CAPPED_QUALITY: <iInitialQP> <iMinQP> <iMaxQP> <bitrate> <maxBitRate> <maxPSNR>";
	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing rcMode";

	rcMode.rcMode = (IMPEncoderRcMode)atoi(p);

	switch (rcMode.rcMode) {
		case IMP_ENC_RC_MODE_FIXQP:
			// Expecting <iInitialQP>
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			if (!p) return "Error: Missing parameters for FixQP";
			rcMode.attrFixQp.iInitialQP = atoi(p);
			break;

		case IMP_ENC_RC_MODE_CBR:
			// Expecting <iInitialQP> <iMinQP> <iMaxQP> <bitrate>
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			if (!p) return "Error: Missing iInitialQP for CBR";
			rcMode.attrCbr.iInitialQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			if (!p) return "Error: Missing iMinQP for CBR";
			rcMode.attrCbr.iMinQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			if (!p) return "Error: Missing iMaxQP for CBR";
			rcMode.attrCbr.iMaxQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			if (!p) return "Error: Missing bitrate for CBR";
			rcMode.attrCbr.uTargetBitRate = atoi(p);
			break;

		case IMP_ENC_RC_MODE_VBR:
			// Parse VBR specific parameters
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			if (!p) return "Error: Missing parameters for VBR";
			rcMode.attrVbr.iInitialQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrVbr.iMinQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrVbr.iMaxQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrVbr.uTargetBitRate = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrVbr.uMaxBitRate = atoi(p);
			break;

		case IMP_ENC_RC_MODE_CAPPED_VBR:
			// Parse Capped VBR specific parameters
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			if (!p) return "Error: Missing parameters for Capped VBR";
			rcMode.attrCappedVbr.iInitialQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedVbr.iMinQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedVbr.iMaxQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedVbr.uTargetBitRate = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedVbr.uMaxBitRate = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedVbr.uMaxPSNR = atoi(p);
			break;

		case IMP_ENC_RC_MODE_CAPPED_QUALITY:
			// Parse Capped Quality specific parameters
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			if (!p) return "Error: Missing parameters for Capped Quality";
			rcMode.attrCappedQuality.iInitialQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedQuality.iMinQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedQuality.iMaxQP = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedQuality.uTargetBitRate = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedQuality.uMaxBitRate = atoi(p);
			p = strtok_r(NULL, " \t\r\n", &tokenPtr);
			rcMode.attrCappedQuality.uMaxPSNR = atoi(p);
			break;

		default:
			return "Error: Unsupported RC mode";
	}

	if (IMP_Encoder_SetChnAttrRcMode(encChn, &rcMode) != 0) {
		return "Error: Set Rate Control Mode Failed";
	}
	return "Rate control mode set successfully";
}

// GET ONLY
char *GetEVAttributes(char *tokenPtr) {
	IMPISPEVAttr attr;
	int ret = IMP_ISP_Tuning_GetEVAttr(&attr);
	if (ret) return "error";
	sprintf(response, "EV: %u, Expr_us: %u, EV_Log2: %u, AGain: %u, DGain: %u, Gain_Log2: %u", 
			attr.ev, attr.expr_us, attr.ev_log2, attr.again, attr.dgain, attr.gain_log2);
	return response;
}

char *GetAeLuma(char *tokenPtr) {
	#ifndef CONFIG_T20
	int luma;
	int ret = IMP_ISP_Tuning_GetAeLuma(&luma);
	if (ret) return "error";
	sprintf(response, "%d", luma);
	return response;
	#else
		return "not supported on >T20";
	#endif
}

char *AwbCt(char *tokenPtr) {
	#ifndef CONFIG_T20
	unsigned int ct;
	int getRet = IMP_ISP_Tuning_GetAWBCt(&ct);
	if (getRet) return "error";

	sprintf(response, "%u", ct);
	return response;
	#else
		return "not supported on >T20";
	#endif
}

char *GetAFMetrics(char *tokenPtr) {
	unsigned int metric;
	int ret = IMP_ISP_Tuning_GetAFMetrices(&metric);
	if (ret) return "error";
	sprintf(response, "%u", metric);
	return response;
}
char *GetTotalGain(char *tokenPtr) {
	uint32_t gain;
	int ret = IMP_ISP_Tuning_GetTotalGain(&gain);
	if (ret) return "error";
	sprintf(response, "%u", gain);
	return response;
}

char *AeMin(char *tokenPtr) {
	#ifndef CONFIG_T20
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	IMPISPAEMin ae_min;

	// If parameters are provided, set the AE Min parameters
	if (p) {
		ae_min.min_it = (unsigned int)atoi(p);
		p = strtok_r(NULL, " \t\r\n", &tokenPtr);
		if (!p) return "error";

		ae_min.min_again = (unsigned int)atoi(p);
		p = strtok_r(NULL, " \t\r\n", &tokenPtr);
		if (!p) return "error";

		ae_min.min_it_short = (unsigned int)atoi(p);
		p = strtok_r(NULL, " \t\r\n", &tokenPtr);
		if (!p) return "error";

		ae_min.min_again_short = (unsigned int)atoi(p);

		int ret = IMP_ISP_Tuning_SetAeMin(&ae_min);
		if (ret) return "error";
		return RESULT(ret, p);
	}

	// If no parameters were provided, get and return the current AE Min parameters
	int ret = IMP_ISP_Tuning_GetAeMin(&ae_min);
	if (ret) return "error";

	sprintf(response, "Min IT: %u, Min AGain: %u, Min IT Short: %u, Min AGain Short: %u", 
			ae_min.min_it, ae_min.min_again, ae_min.min_it_short, ae_min.min_again_short);
	return response; // Return the current AE Min parameters
	#else
		return "not supported on >T20";
	#endif
}

char *GetAeAttr(char *tokenPtr) {
	#ifndef CONFIG_T20
	IMPISPAEAttr aeAttr;
	memset(&aeAttr, 0, sizeof(IMPISPAEAttr)); // Zero-initialize the structure

	int ret = IMP_ISP_Tuning_GetAeAttr(&aeAttr);
	if (ret) return "error";

	// Format and return the AE attributes
	sprintf(response, "AE FreezenEn: %d, AE ItManualEn: %d, AE It: %u, AE AGainManualEn: %d, AE AGain: %u, "
			"AE DGainManualEn: %d, AE DGain: %u, AE IspDGainManualEn: %d, AE IspDGain: %u, "
			"AE WdrShortFreezenEn: %d, AE WdrShortItManualEn: %d, AE WdrShortIt: %u, "
			"AE WdrShortAGainManualEn: %d, AE WdrShortAGain: %u, AE WdrShortDGainManualEn: %d, "
			"AE WdrShortDGain: %u, AE WdrShortIspDGainManualEn: %d, AE WdrShortIspDGain: %u",
			aeAttr.AeFreezenEn, aeAttr.AeItManualEn, aeAttr.AeIt, aeAttr.AeAGainManualEn, aeAttr.AeAGain, 
			aeAttr.AeDGainManualEn, aeAttr.AeDGain, aeAttr.AeIspDGainManualEn, aeAttr.AeIspDGain,
			aeAttr.AeWdrShortFreezenEn, aeAttr.AeWdrShortItManualEn, aeAttr.AeWdrShortIt, 
			aeAttr.AeWdrShortAGainManualEn, aeAttr.AeWdrShortAGain, aeAttr.AeWdrShortDGainManualEn, 
			aeAttr.AeWdrShortDGain, aeAttr.AeWdrShortIspDGainManualEn, aeAttr.AeWdrShortIspDGain);
	return response;
	#else
		return "not supported on >T20";
	#endif
}

char *GetOSDRegionAttributes(char *tokenPtr) {
	// Extract the region handle from the token
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p == NULL) {
		return "Error: Region handle not provided.";
	}

	IMPRgnHandle handle = atoi(p);

	// Get the region attributes
	IMPOSDRgnAttr rgnAttr;
	int ret = IMP_OSD_GetRgnAttr(handle, &rgnAttr);
	if (ret != 0) {
		snprintf(response, sizeof(response), "Error: Failed to get attributes for region handle %d.", handle);
		return response;
	}

	// Prepare the response with the region attributes
	snprintf(response, sizeof(response), "Region Handle: %d, Type: %d, Rect: (x: %d, y: %d, w: %d, h: %d), Format: %d",
			 handle,
			 rgnAttr.type,
			 rgnAttr.rect.p0.x, rgnAttr.rect.p0.y, rgnAttr.rect.p1.x - rgnAttr.rect.p0.x, rgnAttr.rect.p1.y - rgnAttr.rect.p0.y,
			 rgnAttr.fmt);

	return response;
}

char *GetOSDGroupRegionAttributes(char *tokenPtr) {
	// Extract the region handle from the token
	char *pHandle = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (pHandle == NULL) {
		return "Error: Region handle not provided.";
	}
	IMPRgnHandle handle = atoi(pHandle);

	// Extract the group number from the token
	char *pGrpNum = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (pGrpNum == NULL) {
		return "Error: Group number not provided.";
	}
	int grpNum = atoi(pGrpNum);

	// Get the OSD group region attributes
	IMPOSDGrpRgnAttr grpRgnAttr;
	int ret = IMP_OSD_GetGrpRgnAttr(handle, grpNum, &grpRgnAttr);
	if (ret != 0) {
		snprintf(response, sizeof(response), "Error: Failed to get group region attributes for handle %d, group %d.", handle, grpNum);
		return response;
	}

	// Prepare the response with the group region attributes
	snprintf(response, sizeof(response), "Region Handle: %d, Group Number: %d, Show: %d, OffPos: (x: %d, y: %d), Scale: (x: %f, y: %f), GAlphaEn: %d, FgAlpha: %d, BgAlpha: %d, Layer: %d",
			 handle,
			 grpNum,
			 grpRgnAttr.show,
			 grpRgnAttr.offPos.x, grpRgnAttr.offPos.y,
			 grpRgnAttr.scalex, grpRgnAttr.scaley,
			 grpRgnAttr.gAlphaEn,
			 grpRgnAttr.fgAlhpa,
			 grpRgnAttr.bgAlhpa,
			 grpRgnAttr.layer);

	return response;
}

// This one needs work to set...
char *Gamma(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) {
		IMPISPGamma gamma;
		if (IMP_ISP_Tuning_GetGamma(&gamma) != 0) {
			// Handle the error if needed
			return "error";
		}

		char *bufPtr = response;
		for (int i = 0; i < 129; i++) {
			bufPtr += sprintf(bufPtr, "%hu ", gamma.gamma[i]);
		}
		*(bufPtr - 1) = '\n';
		return response;
	}
}

// END GET ONLY