#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imp_control_help.h"
#include "imp_control_video.h"
#include "imp_control_util.h"
#include "include/imp_encoder.h"
#include "include/imp_log.h" //include in util

char *Flip(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

	if (p != NULL && strcmp(p, "-h") == 0) {
		return HELP_MESSAGE_FLIP;
	}

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
	return DEBUG_TEXT("Missing parameter");
}

char *Contrast(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

	if (p != NULL && strcmp(p, "-h") == 0) {
		return HELP_MESSAGE_CONTRAST;
	}

  if(!p) {
	unsigned char cont;
	IMP_ISP_Tuning_GetContrast(&cont);
	sprintf(response, "%d", cont);
	return response;
    } else {
        int cont = atoi(p);
        if (cont > 255 || cont < 0) {
            return "Value out of range";
        }
  }
  int res = IMP_ISP_Tuning_SetContrast(atoi(p));
  return RESULT(res, p);
}

char *Brightness(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

      if (p != NULL && strcmp(p, "-h") == 0) {
		return HELP_MESSAGE_BRIGHTNESS;
    }

  if(!p) {
	unsigned char bri;
	IMP_ISP_Tuning_GetBrightness(&bri);
	sprintf(response, "%d", bri);
	return response;
	    } else {
        int bri = atoi(p);
        if (bri > 255 || bri < 0) {
            return "Value out of range";
        }
  	}
  int res = IMP_ISP_Tuning_SetBrightness(atoi(p));
  return RESULT(res, p);
}

char *Saturation(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
      if (p != NULL && strcmp(p, "-h") == 0) {
     return HELP_MESSAGE_SATURATION;
    }
  if(!p) {
	unsigned char sat;
	IMP_ISP_Tuning_GetSaturation(&sat);
	sprintf(response, "%d", sat);
	return response;
	    } else {
        int sat = atoi(p);
        if (sat > 255 || sat < 0) {
            return "Value out of range";
        }
  	}
  int res = IMP_ISP_Tuning_SetSaturation(atoi(p));
  return RESULT(res, p);
}

char *Sharpness(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

      if (p != NULL && strcmp(p, "-h") == 0) {
       return HELP_MESSAGE_SHARPNESS;
    }

  if(!p) {
	unsigned char sharpness;
	IMP_ISP_Tuning_GetSharpness(&sharpness);
	sprintf(response, "%d", sharpness);
	return response;
		    } else {
        int sharpness = atoi(p);
        if (sharpness > 255 || sharpness < 0) {
            return "Value out of range";
        }
  	}
  int res = IMP_ISP_Tuning_SetSharpness(atoi(p));
  return RESULT(res, p);
}

char *AEComp(char *tokenPtr) {
#ifndef CONFIG_T21
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

    if (p != NULL && strcmp(p, "-h") == 0) {
		return HELP_MESSAGE_AECOMP;
    }
  if(!p) {
	int comp;
	IMP_ISP_Tuning_GetAeComp(&comp);
	sprintf(response, "%d", comp);
	return response;
		    } else {
        int comp = atoi(p);
        if (comp > 255 || comp < 0) {
            return "Value out of range";
        }
  	}
  int res = IMP_ISP_Tuning_SetAeComp(atoi(p));
  return RESULT(res, p);
#else
  return HELP_MESSAGE_PLATFORM;
#endif
}

char *AEItMax(char *tokenPtr) {
#ifndef CONFIG_T20
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

      if (p != NULL && strcmp(p, "-h") == 0) {
	return HELP_MESSAGE_AEITMAX;
    }
  if(!p) {
	unsigned int itMax;
	IMP_ISP_Tuning_GetAE_IT_MAX(&itMax);
	sprintf(response, "%d", itMax);
	return response;
  }
  int res = IMP_ISP_Tuning_SetAe_IT_MAX(atoi(p));
  return RESULT(res, p);
#else
  return HELP_MESSAGE_PLATFORM;
#endif
}

char *Sinter(char *tokenPtr) {
    char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

    if (p != NULL && strcmp(p, "-h") == 0) {
        return HELP_MESSAGE_SINTER;
    }

    if (!p) {
        return DEBUG_TEXT("Error: Missing parameter for Sinter");
    } else {
        int sint = atoi(p);
        if (sint > 255 || sint < 0) {
            return "Value out of range";
        }
        int res = IMP_ISP_Tuning_SetSinterStrength(sint);
        return RESULT(res, p);
    }
}

char *Temper(char *tokenPtr) {
    char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

    if (p != NULL && strcmp(p, "-h") == 0) {
        return HELP_MESSAGE_TEMPER;
    }

    if (p == NULL) {
        return DEBUG_TEXT("Error: Missing parameter for Temper");
    } else {
    int temperStrength = atoi(p);
    if (temperStrength < 0 || temperStrength > 255) {
        return "Value out of range";
    }

    int res = IMP_ISP_Tuning_SetTemperStrength(temperStrength);
    return RESULT(res, p);
	}
}

char *DPC(char *tokenPtr) {
#ifndef CONFIG_T20
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

  if (p != NULL && strcmp(p, "-h") == 0) {
    return HELP_MESSAGE_DPC;
}

  if(!p) {
	unsigned int dpc;
	IMP_ISP_Tuning_GetDPC_Strength(&dpc);
	sprintf(response, "%d", dpc);
	return response;
	    } else {
        int dpc = atoi(p);
        if (dpc > 255 || dpc < 0) {
            return "Value out of range";
        }
  }
  int res = IMP_ISP_Tuning_SetDPC_Strength(atoi(p));
  return RESULT(res, p);
#else
  return HELP_MESSAGE_PLATFORM;
#endif
}

char *DRC(char *tokenPtr) {
#ifndef CONFIG_T20
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if (p != NULL && strcmp(p, "-h") == 0) {
    return HELP_MESSAGE_DRC;
}

  if(!p) {
	unsigned int drc;
	IMP_ISP_Tuning_GetDRC_Strength(&drc);
	sprintf(response, "%d", drc);
	return response;
	    } else {
        int drc = atoi(p);
        if (drc > 255 || drc < 0) {
            return "Value out of range";
        }
  }
  int res = IMP_ISP_Tuning_SetDRC_Strength(atoi(p));
  return RESULT(res, p);
#else
  return HELP_MESSAGE_PLATFORM;
#endif
}

char *HiLight(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

  if (p != NULL && strcmp(p, "-h") == 0) {
    return HELP_MESSAGE_HILIGHT;
}

  if(!p) {
	unsigned int strength;
	IMP_ISP_Tuning_GetHiLightDepress(&strength);
	sprintf(response, "%d", strength);
	return response;
	    } else {
        int strength = atoi(p);
        if (strength > 10 || strength < 0) {
            return "Value out of range";
        }
  }
  int res = IMP_ISP_Tuning_SetHiLightDepress(atoi(p));
  return RESULT(res, p);
}

char *AGain(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
  if (p != NULL && strcmp(p, "-h") == 0) {
    return HELP_MESSAGE_AGAIN;
}

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
  if (p != NULL && strcmp(p, "-h") == 0) {
    return HELP_MESSAGE_DGAIN;
}

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
  if (p != NULL && strcmp(p, "-h") == 0) {
    return HELP_MESSAGE_HUE;
}

  if(!p) {
	unsigned char hue;
	IMP_ISP_Tuning_GetBcshHue(&hue);
	sprintf(response, "%d", hue);
	return response;
	    } else {
        int hue = atoi(p);
        if (hue > 255 || hue < 0) {
            return "Value out of range";
        }
  }
  int res = IMP_ISP_Tuning_SetBcshHue(atoi(p));
  return RESULT(res, p);
#else
  return HELP_MESSAGE_PLATFORM;
#endif
}

char *Mode(char *tokenPtr) {
    char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

    if (p != NULL && strcmp(p, "-h") == 0) {
        return HELP_MESSAGE_MODE;
    }

    if (!p) {
        IMPISPRunningMode mode;
        int res = IMP_ISP_Tuning_GetISPRunningMode(&mode);
        if (res != 0) {
            return "Error getting mode";
        }

        sprintf(response, "%d", mode);
        return response;
    }

    int modeValue = atoi(p);
    if (modeValue != 0 && modeValue != 1) {
        return "Invalid mode";
    }

    int res = IMP_ISP_Tuning_SetISPRunningMode(modeValue);
    return RESULT(res, p);
}

char *Flicker(char *tokenPtr) {
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

  if (p != NULL && strcmp(p, "-h") == 0) {
    return HELP_MESSAGE_FLICKER;
}

  if(!p) {
	IMPISPAntiflickerAttr flicker;
	IMP_ISP_Tuning_GetAntiFlickerAttr(&flicker);
	sprintf(response, "%d", flicker);
	return response;
  }

    int flickerValue = atoi(p);
    if (flickerValue != 0 && flickerValue != 1 && flickerValue != 2) {
        return "Invalid mode";
    }

  int res = IMP_ISP_Tuning_SetAntiFlickerAttr(flickerValue);
  return RESULT(res, p);
}

char *BacklightComp(char *tokenPtr) {
#ifndef CONFIG_T20
  uint32_t strength = 0;
  char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

  if (p != NULL && strcmp(p, "-h") == 0) {
    return HELP_MESSAGE_BACKLIGHTCOMP;
}
  if(!p) {
	uint32_t strength;
	IMP_ISP_Tuning_GetBacklightComp(&strength);
	sprintf(response, "%d", strength);
	return response;
		} else {
        int strength = atoi(p);
        if (strength > 10 || strength < 0) {
            return "Value out of range";
        }
  }
  int res = IMP_ISP_Tuning_SetBacklightComp(atoi(p));
  return RESULT(res, p);
#else
  return HELP_MESSAGE_PLATFORM;
#endif
}

char *DefogStrength(char *tokenPtr) {
	#ifndef CONFIG_T20
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

	if (p != NULL && strcmp(p, "-h") == 0) {
    return HELP_MESSAGE_DEFOGSTRENGTH;
}
	uint8_t ratio;
	if (!p) {
		int32_t getRet = IMP_ISP_Tuning_GetDefog_Strength(&ratio);
		if (getRet) return "error";
		sprintf(response, "%u", ratio);
		return response;
			    } else {
        int ratio = atoi(p);
        if (ratio > 255 || ratio < 0) {
            return "Value out of range";
        }
	}
	ratio = (uint8_t)atoi(p);
	int32_t setRet = IMP_ISP_Tuning_SetDefog_Strength(&ratio);
	return RESULT(setRet, p);
	#else
	return HELP_MESSAGE_PLATFORM;
	#endif
}

char *SetAndGetGopAttr(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn;
	IMPEncoderGopAttr gopAttr;

	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return DEBUG_TEXT("Error: Encoder channel missing.");

if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_GOPATTR;
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
	  return HELP_MESSAGE_PLATFORM;
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
			//sprintf(buffer, "Mode: %d, Rgain: %u, Bgain: %u", wb.mode, wb.rgain, wb.bgain);
			sprintf(buffer, "%d %u %u", wb.mode, wb.rgain, wb.bgain);
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
	return HELP_MESSAGE_SENSORFPS;
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
	if (!p) return DEBUG_TEXT("Error: encoder channel missing.");

if (p != NULL && strcmp(p, "-h") == 0)
{
	return HELP_MESSAGE_FRAMERATE;
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
	if (!p) return DEBUG_TEXT("Usage: <encChn> <iTargetBitRate> <iMaxBitRate>");

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
		return HELP_MESSAGE_PLATFORM;
	#endif
}

char *SetGopLength(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn, iGopLength;
	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return DEBUG_TEXT("Usage: <encChn> <iGopLength>");

	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing iGopLength";
	iGopLength = atoi(p);

	if (IMP_Encoder_SetChnGopLength(encChn, iGopLength) != 0) {
		return "Error: Set GOP Length Failed";
	}
	return "GOP length set successfully";
	#else
		return HELP_MESSAGE_PLATFORM;
	#endif
}

char *SetChnQp(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn, iQP;
	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return DEBUG_TEXT("Usage: <encChn> <iQP>");

	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing iQP";
	iQP = atoi(p);

	if (IMP_Encoder_SetChnQp(encChn, iQP) != 0) {
		return "Error: Set QP Failed";
	}
	return "QP set successfully";
	#else
		return HELP_MESSAGE_PLATFORM;
	#endif
}

char *SetChnQpBounds(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn, iMinQP, iMaxQP;
	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return DEBUG_TEXT("Usage: <encChn> <iMinQP> <iMaxQP>");

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
		return HELP_MESSAGE_PLATFORM;
	#endif
}

char *SetChnQpIPDelta(char *tokenPtr) {
	#ifndef CONFIG_T20
	int encChn, uIPDelta;
	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);
	if (!p) return DEBUG_TEXT("Usage: <encChn> <uIPDelta>");

	encChn = atoi(p);
	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (!p) return "Error: Missing uIPDelta";
	uIPDelta = atoi(p);

	if (IMP_Encoder_SetChnQpIPDelta(encChn, uIPDelta) != 0) {
		return "Error: Set QP IP Delta Failed";
	}
	return "QP IP Delta set successfully";
	#else
		return HELP_MESSAGE_PLATFORM;
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
			return HELP_MESSAGE_AUTOZOOM;
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

	return DEBUG_TEXT(response);
#else
  return HELP_MESSAGE_PLATFORM;
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
			return HELP_MESSAGE_FRONTCROP;
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
  return HELP_MESSAGE_PLATFORM;
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
		return HELP_MESSAGE_MASK;
	}

	// Parse the channel
	if (p != NULL) {
		channel = atoi(p);
		parsedFields++;
	} else {
		return DEBUG_TEXT("Channel not specified");
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
	return HELP_MESSAGE_PLATFORM;
	#endif

}

char *SetAndGetRcMode(char *tokenPtr) {
	int encChn;
	IMPEncoderAttrRcMode rcMode;

	char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);

	if (p != NULL && strcmp(p, "-h") == 0) {
		return HELP_MESSAGE_RCMODE;
	}

    if (p == NULL) {
        return DEBUG_TEXT("No parameteres provided");
    }

	encChn = atoi(p);

    p = strtok_r(NULL, " \t\r\n", &tokenPtr);

    if (p == NULL) {
        if (IMP_Encoder_GetChnAttrRcMode(encChn, &rcMode) != 0) {
            return "Error: Failed to get rate control mode";
        }

        switch (rcMode.rcMode) {
            case IMP_ENC_RC_MODE_FIXQP:
                snprintf(response, sizeof(response), "Current RC Mode: FIXQP, InitialQP: %d",
                         rcMode.attrFixQp.iInitialQP);
                break;
            case IMP_ENC_RC_MODE_CBR:
                snprintf(response, sizeof(response), "Current RC Mode: CBR, InitialQP: %d, MinQP: %d, MaxQP: %d, Bitrate: %u",
                         rcMode.attrCbr.iInitialQP, rcMode.attrCbr.iMinQP, rcMode.attrCbr.iMaxQP, rcMode.attrCbr.uTargetBitRate);
                break;
            case IMP_ENC_RC_MODE_VBR:
                snprintf(response, sizeof(response), "Current RC Mode: VBR, InitialQP: %d, MinQP: %d, MaxQP: %d, Bitrate: %u, MaxBitRate: %u",
                         rcMode.attrVbr.iInitialQP, rcMode.attrVbr.iMinQP, rcMode.attrVbr.iMaxQP, rcMode.attrVbr.uTargetBitRate, rcMode.attrVbr.uMaxBitRate);
                break;
            case IMP_ENC_RC_MODE_CAPPED_VBR:
                snprintf(response, sizeof(response), "Current RC Mode: CAPPED_VBR, InitialQP: %d, MinQP: %d, MaxQP: %d, Bitrate: %u, MaxBitRate: %u, MaxPSNR: %u",
                         rcMode.attrCappedVbr.iInitialQP, rcMode.attrCappedVbr.iMinQP, rcMode.attrCappedVbr.iMaxQP, rcMode.attrCappedVbr.uTargetBitRate, rcMode.attrCappedVbr.uMaxBitRate, rcMode.attrCappedVbr.uMaxPSNR);
                break;
            case IMP_ENC_RC_MODE_CAPPED_QUALITY:
                snprintf(response, sizeof(response), "Current RC Mode: CAPPED_QUALITY, InitialQP: %d, MinQP: %d, MaxQP: %d, Bitrate: %u, MaxBitRate: %u, MaxPSNR: %u",
                         rcMode.attrCappedQuality.iInitialQP, rcMode.attrCappedQuality.iMinQP, rcMode.attrCappedQuality.iMaxQP, rcMode.attrCappedQuality.uTargetBitRate, rcMode.attrCappedQuality.uMaxBitRate, rcMode.attrCappedQuality.uMaxPSNR);
                break;
            default:
                snprintf(response, sizeof(response), "Unsupported RC mode");
                break;
        }
        return response;
    }

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

char *ControlFisheyeStatus(char *tokenPtr) {
    int encChn, enable, ret;

    char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);

    // Check for help message request
    if (p != NULL && strcmp(p, "-h") == 0) {
        return HELP_MESSAGE_FISHEYE;
    }

    if (p == NULL) {
        return DEBUG_TEXT("No channel number provided");
    }


    encChn = atoi(p);

    p = strtok_r(NULL, " \t\r\n", &tokenPtr);

    // Set fisheye status
    if (p != NULL) {
        enable = atoi(p);
        ret = IMP_Encoder_SetFisheyeEnableStatus(encChn, enable);
        if (ret != 0) {
            sprintf(response, "Error: Unable to set fisheye status for channel %d", encChn);
        } else {
            sprintf(response, "Fisheye status set to %d for channel %d", enable, encChn);
        }
    }
    // Get fisheye status
    else {
        ret = IMP_Encoder_GetFisheyeEnableStatus(encChn, &enable);
        if (ret != 0) {
            sprintf(response, "Error: Unable to get fisheye status for channel %d", encChn);
        } else {
            sprintf(response, "Fisheye status for channel %d is %d", encChn, enable);
        }
    }

    return response;
}

// GET ONLY

char *GetChannelEncodingType(char *tokenPtr) {
	#ifndef CONFIG_T20
    int encChn;
    IMPEncoderEncType encType;

    char *p = strtok_r(tokenPtr, " \t\r\n", &tokenPtr);

    // Check for help message request
    if (p != NULL && strcmp(p, "-h") == 0) {
        return HELP_MESSAGE_GETENCTYPE;
    }

    if (p == NULL) {
        return DEBUG_TEXT("No channel number provided");
    }

    encChn = atoi(p);

    int ret = IMP_Encoder_GetChnEncType(encChn, &encType);
    if (ret != 0) {
        return "Error: Failed to get encoding type";
    }

    sprintf(response, "Channel %d Encoding Type: %d", encChn, encType);

    return response;
	#else
		return HELP_MESSAGE_PLATFORM;
	#endif
}

char *GetEVAttributes(char *tokenPtr) {
	IMPISPEVAttr attr;
	int ret = IMP_ISP_Tuning_GetEVAttr(&attr);
	if (ret) return "error";
	//sprintf(response, "EV: %u, Expr_us: %u, EV_Log2: %u, AGain: %u, DGain: %u, Gain_Log2: %u",
	//		attr.ev, attr.expr_us, attr.ev_log2, attr.again, attr.dgain, attr.gain_log2);
	sprintf(response, "%u %u %u %u %u %u",
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
		return HELP_MESSAGE_PLATFORM;
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
		return HELP_MESSAGE_PLATFORM;
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

	//sprintf(response, "Min IT: %u, Min AGain: %u, Min IT Short: %u, Min AGain Short: %u",
	//		ae_min.min_it, ae_min.min_again, ae_min.min_it_short, ae_min.min_again_short);
	sprintf(response, "%u %u %u %u",
			ae_min.min_it, ae_min.min_again, ae_min.min_it_short, ae_min.min_again_short);
	return response; // Return the current AE Min parameters
	#else
		return HELP_MESSAGE_PLATFORM;
	#endif
}

char *GetAeAttr(char *tokenPtr) {
	#ifndef CONFIG_T20
	IMPISPAEAttr aeAttr;
	memset(&aeAttr, 0, sizeof(IMPISPAEAttr)); // Zero-initialize the structure

	int ret = IMP_ISP_Tuning_GetAeAttr(&aeAttr);
	if (ret) return "error";

	// Format and return the AE attributes
	/*sprintf(response, "AE FreezenEn: %d, AE ItManualEn: %d, AE It: %u, AE AGainManualEn: %d, AE AGain: %u, "
			"AE DGainManualEn: %d, AE DGain: %u, AE IspDGainManualEn: %d, AE IspDGain: %u, "
			"AE WdrShortFreezenEn: %d, AE WdrShortItManualEn: %d, AE WdrShortIt: %u, "
			"AE WdrShortAGainManualEn: %d, AE WdrShortAGain: %u, AE WdrShortDGainManualEn: %d, "
			"AE WdrShortDGain: %u, AE WdrShortIspDGainManualEn: %d, AE WdrShortIspDGain: %u",
			aeAttr.AeFreezenEn, aeAttr.AeItManualEn, aeAttr.AeIt, aeAttr.AeAGainManualEn, aeAttr.AeAGain,
			aeAttr.AeDGainManualEn, aeAttr.AeDGain, aeAttr.AeIspDGainManualEn, aeAttr.AeIspDGain,
			aeAttr.AeWdrShortFreezenEn, aeAttr.AeWdrShortItManualEn, aeAttr.AeWdrShortIt,
			aeAttr.AeWdrShortAGainManualEn, aeAttr.AeWdrShortAGain, aeAttr.AeWdrShortDGainManualEn,
			aeAttr.AeWdrShortDGain, aeAttr.AeWdrShortIspDGainManualEn, aeAttr.AeWdrShortIspDGain);*/
	sprintf(response, "%d %d %u %d %u %d %u %d %u %d %d %u %d %u %d %u %d %u",
			aeAttr.AeFreezenEn, aeAttr.AeItManualEn, aeAttr.AeIt, aeAttr.AeAGainManualEn, aeAttr.AeAGain,
			aeAttr.AeDGainManualEn, aeAttr.AeDGain, aeAttr.AeIspDGainManualEn, aeAttr.AeIspDGain,
			aeAttr.AeWdrShortFreezenEn, aeAttr.AeWdrShortItManualEn, aeAttr.AeWdrShortIt,
			aeAttr.AeWdrShortAGainManualEn, aeAttr.AeWdrShortAGain, aeAttr.AeWdrShortDGainManualEn,
			aeAttr.AeWdrShortDGain, aeAttr.AeWdrShortIspDGainManualEn, aeAttr.AeWdrShortIspDGain);
	return response;
	#else
		return HELP_MESSAGE_PLATFORM;
	#endif
}

char *GetOSDRegionAttributes(char *tokenPtr) {
	// Extract the region handle from the token
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

	IMPRgnHandle handle;

	if (p != NULL && strcmp(p, "-h") == 0) {
		return HELP_MESSAGE_GETOSDRGNATTR;
	}

	// If no handle specifed, use 0 as default, otherwise use specified handle
	if (p == NULL) {
		handle = 0;
	} else {
		handle = atoi(p);
	}

	// Get the region attributes
	IMPOSDRgnAttr rgnAttr;
	int ret = IMP_OSD_GetRgnAttr(handle, &rgnAttr);
	if (ret != 0) {
		snprintf(response, sizeof(response), "Error: Failed to get attributes for region handle %d.", handle);
		return response;
	}

	// Prepare the response with the region attributes
	/*snprintf(response, sizeof(response), "Region Handle: %d, Type: %d, Rect: (x: %d, y: %d, w: %d, h: %d), Format: %d",
			 handle,
			 rgnAttr.type,
			 rgnAttr.rect.p0.x, rgnAttr.rect.p0.y, rgnAttr.rect.p1.x - rgnAttr.rect.p0.x, rgnAttr.rect.p1.y - rgnAttr.rect.p0.y,
			 rgnAttr.fmt);*/
	snprintf(response, sizeof(response), "%d %d %d %d %d %d %d",
			 handle,
			 rgnAttr.type,
			 rgnAttr.rect.p0.x, rgnAttr.rect.p0.y, rgnAttr.rect.p1.x - rgnAttr.rect.p0.x, rgnAttr.rect.p1.y - rgnAttr.rect.p0.y,
			 rgnAttr.fmt);

	return response;
}

char *GetOSDGroupRegionAttributes(char *tokenPtr) {
	// Extract the region handle from the token
	char *pHandle = strtok_r(NULL, " \t\r\n", &tokenPtr);

	IMPRgnHandle handle;

	if (pHandle != NULL && strcmp(pHandle, "-h") == 0) {
	return HELP_MESSAGE_GETOSDGRPRGNATTR;
	}

	// If no handle specifed, use 0 as default, otherwise use specified handle
	if (pHandle == NULL) {
		handle = 0;
	} else {
		handle = atoi(pHandle);
	}

	// Extract the group number from the token
	char *pGrpNum = strtok_r(NULL, " \t\r\n", &tokenPtr);
		int grpNum;

	// If no group specifed, use 0 as default, otherwise use specified group
	if (pGrpNum == NULL) {
		grpNum = 0;
	} else {
		grpNum = atoi(pGrpNum);
	}

	// Get the OSD group region attributes
	IMPOSDGrpRgnAttr grpRgnAttr;
	int ret = IMP_OSD_GetGrpRgnAttr(handle, grpNum, &grpRgnAttr);
	if (ret != 0) {
		snprintf(response, sizeof(response), "Error: Failed to get group region attributes for handle %d, group %d.", handle, grpNum);
		return response;
	}

	// Prepare the response with the group region attributes
	/*snprintf(response, sizeof(response), "Region Handle: %d, Group Number: %d, Show: %d, OffPos: (x: %d, y: %d), Scale: (x: %f, y: %f), GAlphaEn: %d, FgAlpha: %d, BgAlpha: %d, Layer: %d",
			 handle,
			 grpNum,
			 grpRgnAttr.show,
			 grpRgnAttr.offPos.x, grpRgnAttr.offPos.y,
			 grpRgnAttr.scalex, grpRgnAttr.scaley,
			 grpRgnAttr.gAlphaEn,
			 grpRgnAttr.fgAlhpa,
			 grpRgnAttr.bgAlhpa,
			 grpRgnAttr.layer);*/
	snprintf(response, sizeof(response), "%d %d %d %d %d%f %f %d %d %d %d",
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

char *setOSDalpha(char *tokenPtr) {
	int grpNum = 0;
	int handle = 0;
	// Parse input arguments for alpha_en
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

	// Parse input arguments for fg_alpha
	if (p == NULL) return DEBUG_TEXT("Error: Foreground alpha not specified");

	if (p != NULL && strcmp(p, "-h") == 0) {
		return HELP_MESSAGE_SETOSDALPHA;
	}

	int fg_alpha = atoi(p); // Parse as decimal value

	// Initialize OSD group region attributes
	IMPOSDGrpRgnAttr grpRgnAttr;
	grpRgnAttr.show = 1; // Set to show the region
	grpRgnAttr.gAlphaEn = 1; // Alpha enable
	grpRgnAttr.fgAlhpa = fg_alpha;  // Foreground Alpha (0-255)
	grpRgnAttr.bgAlhpa = 0;  // Background Alpha (0-255)
	grpRgnAttr.offPos = (IMPPoint){0, 0}; // Set offset position
	grpRgnAttr.scalex = 0; // No scaling in x
	grpRgnAttr.scaley = 0; // No scaling in y
	grpRgnAttr.layer = 0; // Set display layer

	// Assuming handle and grpNum are defined elsewhere and accessible here
	 int ret = IMP_OSD_SetGrpRgnAttr(handle, grpNum, &grpRgnAttr);
	if (ret != 0) {
		return "Failed to set OSD group region attributes";
	}

	return "OSD group region attributes set successfully";
}

char *showOSD(char *tokenPtr) {
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p == NULL) return DEBUG_TEXT("Error: Show/Hide flag not specified");

	if (p != NULL && strcmp(p, "-h") == 0) {
		return HELP_MESSAGE_SHOWOSD;
		}

	int showFlag = 0;
	if (strcmp(p, "1") == 0 || strcmp(p, "show") == 0) {
		showFlag = 1; // Show OSD
	} else if (strcmp(p, "0") == 0 || strcmp(p, "hide") == 0) {
		showFlag = 0; // Hide OSD
	} else {
		return "Error: Invalid Show/Hide flag";
	}

	int grpNum = 0;
	int handle = 0;

	// Set the OSD group region attributes
	int ret = IMP_OSD_ShowRgn(handle, grpNum, showFlag);
	if (ret != 0) {
		return "Failed to set OSD group region attributes";
	}

	return "OSD group region attributes set successfully";
}

// Global variables for new coordinates, width, height and a flag to check if they are set
int newTopLeftX = -1;
int newTopLeftY = -1;
int newWidth = -1;
int newHeight = -1;
int coordinatesSet = 0; // Flag to indicate new coordinates are set

// External handle
extern IMPRgnHandle handle;

// Define a pointer for the original function
int (*original_IMP_OSD_SetRgnAttr)(IMPRgnHandle, IMPOSDRgnAttr*);

// Function to set new top-left coordinates (x, y) and size (width, height)
void setNewCoordinatesAndSize(int topLeftX, int topLeftY) {
	newTopLeftX = topLeftX;
	newTopLeftY = topLeftY;

	coordinatesSet = 1; // Indicate that new coordinates and size are set
	IMP_LOG_INFO(TAG, "New Coordinates and Size Set: Top-Left (x: %d, y: %d)\n",
		   newTopLeftX, newTopLeftY);
}

// Hook function
int IMP_OSD_SetRgnAttr(IMPRgnHandle handle, IMPOSDRgnAttr *prAttr) {
	// Dynamically find the original function if not already found
	if (!original_IMP_OSD_SetRgnAttr) {
		original_IMP_OSD_SetRgnAttr = dlsym(RTLD_NEXT, "IMP_OSD_SetRgnAttr");
		if (!original_IMP_OSD_SetRgnAttr) {
			IMP_LOG_ERR(TAG, "Error in `dlsym`: %s\n", dlerror());
			return -1;
		}
	}

	if (coordinatesSet && prAttr != NULL) {
		// Temporarily save original coordinates and size
		int origX = prAttr->rect.p0.x;
		int origY = prAttr->rect.p0.y;
		int origWidth = prAttr->rect.p1.x - origX + 1;
		int origHeight = prAttr->rect.p1.y - origY + 1;

		// Set new coordinates and size
		prAttr->rect.p0.x = newTopLeftX;
		prAttr->rect.p0.y = newTopLeftY;

		prAttr->rect.p1.x = newTopLeftX + origWidth - 1;
		prAttr->rect.p1.y = newTopLeftY + origHeight - 1;

		// Call the original function with modified coordinates and size
		int result = original_IMP_OSD_SetRgnAttr(handle, prAttr);

		return result;
	}

	// Call the original function without modification
	return original_IMP_OSD_SetRgnAttr(handle, prAttr);
}

char *setOSDpos(char *tokenPtr) {

	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);

	// Check for help request
	if (p != NULL && strcmp(p, "-h") == 0) {
		return HELP_MESSAGE_SETOSD_POS;
	}

	if (p == NULL) return DEBUG_TEXT("Error: x coordinate not specified");
	int x = atoi(p);

	p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	if (p == NULL) return DEBUG_TEXT("Error: y coordinate not specified");
	int y = atoi(p);

	// Set the new top-left coordinates and size
	setNewCoordinatesAndSize(x, y);

	return "OSD region position and size update scheduled";
}

char *Test(char *tokenPtr)
{
	char *p = strtok_r(NULL, " \t\r\n", &tokenPtr);
	int grpNum = 0;
	int handle = 0;
	int showFlag = 0;
	int showFlag1 = 1;

	if (p != NULL && strcmp(p, "-1") == 0)
	{
		IMP_OSD_Stop(grpNum);
		return "ok stop osd";
	}

	if (p != NULL && strcmp(p, "-2") == 0)
	{
		IMP_OSD_Start(grpNum);
		return "ok start osd";
	}

	if (p != NULL && strcmp(p, "-3") == 0)
	{
		IMP_OSD_ShowRgn(handle, grpNum, showFlag);
		return "ok showflag disable osd";
	}

	if (p != NULL && strcmp(p, "-4") == 0)
	{
		IMP_OSD_ShowRgn(handle, grpNum, showFlag1);
		return "ok showflag enable osd";
	}

	if (p != NULL && strcmp(p, "-5") == 0)
	{
		return "ok";
	}
		if (p != NULL && strcmp(p, "-0") == 0)
	{
		return "ok";
	}
}
