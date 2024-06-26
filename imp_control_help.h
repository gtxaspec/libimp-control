#ifndef HELP_MESSAGES_H
#define HELP_MESSAGES_H

#define HELP_MESSAGE_AEITMAX "Usage: AEITMax [value]\n" \
                             "value: Maximum AE integration time to set (in milliseconds).\n" \
                             "If no value is provided, the current maximum AE integration time setting is returned."
#define HELP_MESSAGE_FLIP "Usage: Flip [value]\n" \
               "value: 0 - No flip, no mirror\n" \
               "       1 - Mirror only\n" \
               "       2 - Flip only\n" \
               "       3 - Flip and mirror\n" \
               "If no value is provided, the current flip/mirror status is returned."

#define HELP_MESSAGE_CONTRAST "Usage: Contrast [value]\n" \
               "value: Contrast value to set (0-255).\n" \
               "If no value is provided, the current contrast setting is returned."

#define HELP_MESSAGE_BRIGHTNESS "Usage: Brightness [value]\n" \
               "value: Brightness value to set (0-255).\n" \
               "If no value is provided, the current brightness setting is returned."

#define HELP_MESSAGE_SATURATION "Usage: Saturation [value]\n" \
               "value: Saturation value to set (range: 0-255).\n" \
               "If no value is provided, the current saturation setting is returned."

#define HELP_MESSAGE_SHARPNESS "Usage: Sharpness [value]\n" \
               "value: Sharpness value to set (range: 0-255).\n" \
               "If no value is provided, the current sharpness setting is returned."

#define HELP_MESSAGE_AECOMP "Usage: AEComp [value]\n" \
               "value: AE compensation value to set (range: specific to your camera).\n" \
               "If no value is provided, the current AE compensation setting is returned."

#define HELP_MESSAGE_AEITMAX "Usage: AEITMax [value]\n" \
               "value: Maximum AE integration time to set (in milliseconds).\n" \
               "If no value is provided, the current maximum AE integration time setting is returned."

#define HELP_MESSAGE_SINTER "Usage: Sinter [value]\n" \
           "value: Set the spatial noise reduction intensity (0-255).\n" \
           "If no value is provided, the current spatial noise reduction setting is returned."

#define HELP_MESSAGE_TEMPER "Usage: Temper [value]\n" \
           "value: Set the temporal noise reduction intensity (0-255).\n" \
           "If no value is provided, the current temporal noise reduction setting is returned."

#define HELP_MESSAGE_DPC "Usage: DPC [value]\n" \
           "value: Enable or disable Defective Pixel Correction (DPC).\n" \
           "0: Disable DPC, 1: Enable DPC.\n" \
           "If no value is provided, the current DPC setting is returned."

#define HELP_MESSAGE_DRC "Usage: DRC [value]\n" \
           "value: Set the dynamic range compression level (0-255).\n" \
           "If no value is provided, the current dynamic range compression setting is returned."

#define HELP_MESSAGE_HILIGHT "Usage: Hilight [value]\n" \
           "value: Set the hilight compensation level (0-255).\n" \
           "If no value is provided, the current hilight compensation setting is returned."

#define HELP_MESSAGE_AGAIN "Usage: AGain [value]\n" \
           "value: Set the analog gain (0-255).\n" \
           "If no value is provided, the current analog gain setting is returned."

#define HELP_MESSAGE_DGAIN "Usage: DGain [value]\n" \
           "value: Set the digital gain (0-255).\n" \
           "If no value is provided, the current digital gain setting is returned."

#define HELP_MESSAGE_HUE "Usage: Hue [value]\n" \
           "value: Set the hue level (0-255).\n" \
           "If no value is provided, the current hue setting is returned."

#define HELP_MESSAGE_MODE "Usage: Mode [value]\n" \
           "value: Set the camera operation mode.\n" \
           "Available modes: 0 (Auto), 1 (Night), 2 (Day), etc.\n" \
           "If no value is provided, the current camera mode is returned."

#define HELP_MESSAGE_FLICKER "Usage: Flicker [value]\n" \
           "value: Set the anti-flicker mode (50Hz, 60Hz, Off).\n" \
           "Available options: 0 (Off), 1 (50Hz), 2 (60Hz).\n" \
           "If no value is provided, the current anti-flicker mode is returned."

#define HELP_MESSAGE_BACKLIGHTCOMP "Usage: BacklightComp [value]\n" \
           "value: Enable or disable backlight compensation.\n" \
           "0: Disable backlight compensation, 1: Enable backlight compensation.\n" \
           "If no value is provided, the current backlight compensation setting is returned."

#define HELP_MESSAGE_DEFOGSTRENGTH "Usage: DefogStrength [value]\n" \
           "value: Set the defog strength level (0-255).\n" \
           "If no value is provided, the current defog strength setting is returned."

#define HELP_MESSAGE_GOPATTR "Usage: gopattr [encChn] [gopLength]\n" \
		"Parameters:\n" \
		"  encChn: Encoder Channel number to set the GOP attribute for.\n" \
		"  gopLength: Length of the Group of Pictures (GOP)."

#define HELP_MESSAGE_SENSORFPS "Usage: sensorfps [fps_num]\n" \
		"Parameter:\n" \
		"  fps_num: The frame rate number to set for the sensor.\n" \
		"           It specifies the number of frames per second."

#define HELP_MESSAGE_FRAMERATE "Usage: framerate [encChn] [frmRateNum] <frmRateDen>\n" \
		"Parameters:\n" \
		"  encChn: Encoder Channel number to set the framerate for.\n" \
		"  frmRateNum: Desired frame rate number.\n" \
		"  frmRateDen: Frame rate number denominator.  This value may be omited and the default value of 1 will be used."

#define HELP_MESSAGE_AUTOZOOM "Usage: SetAutoZoom [chan] [scaler_enable] [scaler_outwidth] [scaler_outheight] [crop_enable] [crop_left] [crop_top] [crop_width] [crop_height]\n" \
		"chan: Channel number\n" \
		"scaler_enable: 0 (disable) or 1 (enable) scaler\n" \
		"scaler_outwidth, scaler_outheight: Scaler output dimensions\n" \
		"crop_enable: 0 (disable) or 1 (enable) crop\n" \
		"crop_left, crop_top: Crop region start coordinates\n" \
		"crop_width, crop_height: Crop region dimensions\n" \
		"WARNING: AutoZoom requires increased performance, recommended 240Mhz ISP Clock"

#define HELP_MESSAGE_FRONTCROP "Usage: FrontCrop [enable] [top] [left] [width] [height]\n" \
		"Enable: 0 (disable) or 1 (enable)\n" \
		"Top, Left, Width, Height: Integer values specifying crop region"

#define HELP_MESSAGE_MASK "Usage: Mask [channel] [mask_en] [mask_pos_top] [mask_pos_left] [mask_width] [mask_height] [Red] [Green] [Blue]\n" \
		"channel: Channel number\n" \
		"mask_en: 0 (disable) or 1 (enable) mask\n" \
		"mask_pos_top, mask_pos_left: Mask position coordinates\n" \
		"mask_width, mask_height: Mask dimensions\n" \
		"Red, Green, Blue: Mask color values (0-255)"

#define HELP_MESSAGE_GETOSDRGNATTR "Usage: GetOSDRegionAttributes [RegionHandle]\n" \
		"RegionHandle: The handle identifier of the OSD region.\n" \
		"Description: Retrieves attributes for a specified OSD region, including type, rectangle dimensions, and format.\n" \
		"Returns: A detailed description of the OSD region's attributes (Type, Rectangle coordinates and dimensions, Format), or an error message if the region handle is not provided or invalid."

#define HELP_MESSAGE_GETOSDGRPRGNATTR "Usage: GetOSDGroupRegionAttributes [RegionHandle] [GroupNumber]\n" \
		"RegionHandle: The handle identifier of the OSD region.\n" \
		"GroupNumber: The number identifier of the OSD group.\n" \
		"Description: Retrieves attributes for a specified OSD region within a specific group, including visibility, position, scaling, alpha settings, and layer.\n" \
		"Returns: A detailed description of the OSD group region's attributes (Visibility, Offset Position, Scaling, Alpha Settings, Layer), or an error message if the region handle or group number is not provided or invalid."

#define HELP_MESSAGE_SETOSDALPHA "Usage: setOSDalpha [RegionHandle] [fgAlpha]\n" \
		"RegionHandle: The handle identifier of the OSD region.\n" \
		"fgAlpha: Foreground alpha value (0-255).\n" \
		"Description: Sets the alpha attributes for a specified OSD group region. This includes enabling/disabling alpha and setting the foreground alpha level.\n" \
		"Returns: Confirmation message on successful setting of attributes, or an error message in case of failure."

#define HELP_MESSAGE_SHOWOSD "Usage: showOSD [RegionHandle] [flag]\n" \
		"RegionHandle: The handle identifier of the OSD region.\n" \
		"flag: '1' or 'show' to display the OSD, '0' or 'hide' to hide the OSD.\n" \
		"Description: Controls the visibility of the OSD (On-Screen Display) in a specific OSD group. The function sets the OSD to be visible or hidden based on the given flag.\n" \
		"Returns: Confirmation message on successful change of visibility, or an error message in case of failure or invalid input."

#define HELP_MESSAGE_SETOSD_POS "Usage: setOSDpos [RegionHandle] [x] [y] [hooked]\n" \
		"RegionHandle: The handle identifier of the OSD region.\n" \
		"x: X-coordinate for OSD region, 0: centered, less than 0: left-aligned, greater than 0: right-aligned.\n" \
		"y: Y-coordinate for OSD region, 0: centered, less than 0: left-aligned, greater than 0: right-aligned.\n" \
		"Returns: Confirmation message indicating that the position update is done, or an error message in case of missing parameters."

#define HELP_MESSAGE_GETOSD "Usage: getOSD [RegionHandle]\n" \
		"RegionHandle: The handle identifier of the OSD region.\n" \
		"\nreturns:	<RegionHandle> <show> <x> <y> <hooked>\n" \
		"  fgAlpha:	Foreground alpha value (0-255).\n" \
		"  show:	show or hide the region.\n" \
		"  x:		X-coordinate for OSD region, 0: centered, less than 0: left-aligned, greater than 0: right-aligned.\n" \
		"  y:		Y-coordinate for OSD region, 0: centered, less than 0: left-aligned, greater than 0: right-aligned.\n" \
		"  hooked: indicates whether the OSD item positioning is hooked via IMP. \n" \
		"Description: Gets the show flag, alpha attributes and position information for a specified OSD group region.\n" \
		"Returns: Confirmation message on successful setting of attributes, or an error message in case of failure."

#define HELP_MESSAGE_SETOSD "Usage: setOSD [RegionHandle] [show] [fgAlpha] [x] [y] [hooked]\n" \
		"RegionHandle: The handle identifier of the OSD region.\n" \
		"fgAlpha: Foreground alpha value (0-255).\n" \
		"show: show or hide the region.\n" \
		"x: X-coordinate for OSD region, 0: centered, less than 0: left-aligned, greater than 0: right-aligned.\n" \
		"y: Y-coordinate for OSD region, 0: centered, less than 0: left-aligned, greater than 0: right-aligned.\n" \
		"Description: Sets the show flag, alpha attributes and position information for a specified OSD group region. This includes enabling/disabling alpha and setting the foreground alpha level.\n" \
		"Returns: Confirmation message on successful setting of attributes, or an error message in case of failure."

#define HELP_MESSAGE_HPF "Usage: aihpf [0/1]\n" \
		"Option:\n" \
		"  0 - Turn off High Pass Filter\n" \
		"  1 - Turn on High Pass Filter"

#define HELP_MESSAGE_AOAGC "Usage: aiagc [mode] [compGaindB]\n" \
		"Options:\n" \
		"  mode - Operating mode of AGC (Automatic Gain Control)\n" \
		"         0: Off\n" \
		"         Any other number: Gain Level\n" \
		"  compGaindB - Compensation gain in decibels (dB), used when mode is not 0"

#define HELP_MESSAGE_AINS "Usage: ains [-1/0-3]\n" \
		"Parameter:\n" \
		"  -1: Disable Noise Suppression\n" \
		"  0-3: Set Noise Suppression Level (0 being the lowest and 3 the highest)"

#define HELP_MESSAGE_AIEC "Usage: aiaec [0/1]\n" \
		"Parameter:\n" \
		"  0: Disable Automatic Echo Cancellation (AEC)\n" \
		"  1: Enable Automatic Echo Cancellation (AEC)"

#define HELP_MESSAGE_AIVOL "Usage: aivol [-30-120]\n" \
		"Parameter:\n" \
		"  -30 to 120: Set the Audio Input Volume Level.\n" \
		"              -30 represents the lowest volume level,\n" \
		"              120 represents the highest volume level."

#define HELP_MESSAGE_AIGAIN "Usage: aigain [0-31]\n" \
		"Parameter:\n" \
		"  0-31: Set the Audio Input Gain level.\n" \
		"        0 represents the minimum gain level,\n" \
		"        31 represents the maximum gain level."

#define HELP_MESSAGE_AIALC "Usage: aialc [0-7]\n" \
		"Parameter:\n" \
		"  0-7: Set the Automatic Input Level Control (AILC) level.\n" \
		"       0 is the lowest level and 7 is the highest level."

#define HELP_MESSAGE_AOVOL "Usage: aovol [-30-120]\n" \
		"Parameter:\n" \
		"  -30 to 120: Set the Audio Output Volume Level.\n" \
		"              -30 represents the lowest volume level,\n" \
		"              120 represents the highest volume level."

#define HELP_MESSAGE_AOGAIN "Usage: aogain [0-31]\n" \
		"Parameter:\n" \
		"  0-31: Set the Audio Output Gain level.\n" \
		"        0 is the minimum gain level and 31 is the maximum gain level."

#define HELP_MESSAGE_AOHPF "Usage: aohpf [0/1]\n" \
		"Parameter:\n" \
		"  0: Disable High Pass Filter for Audio Output\n" \
		"  1: Enable High Pass Filter for Audio Output"

#define HELP_MESSAGE_FULLDEMO "Usage: full_demo\n" \
		"Description:\n" \
		"  This command initiates a full demonstration mode, showcasing\n" \
		"  the capabilities and features of the system. Use the '-f' parameter\n" \
		"  to force all demo loops, even those which may not run reliably on lower\n" \
		"  performance SOC models."

#define HELP_MESSAGE_PLATFORM "Not supported on this platform"

#define HELP_MESSAGE_RCMODE "Usage: <encChn> <rcMode> [<mode specific parameters>]\n" \
				   "rcModes:\n" \
				   "0: FIXQP: <iInitialQP>\n" \
				   "2: CBR: <iInitialQP> <iMinQP> <iMaxQP> <bitrate>\n" \
				   "3: VBR: <iInitialQP> <iMinQP> <iMaxQP> <bitrate> <maxBitRate>\n" \
				   "4: CAPPED_VBR: <iInitialQP> <iMinQP> <iMaxQP> <bitrate> <maxBitRate> <maxPSNR>\n" \
				   "8: CAPPED_QUALITY: <iInitialQP> <iMinQP> <iMaxQP> <bitrate> <maxBitRate> <maxPSNR>"

#define HELP_MESSAGE_GETENCTYPE "Usage: <encChn>\n" \
					"Retrieves the encoding type for a video channel.\n" \
					"Encoding Types:\n" \
					"  0 - AVC (Advanced Video Coding)\n" \
					"  1 - HEVC (High Efficiency Video Coding)\n" \
					"  4 - JPEG (Joint Photographic Experts Group)\n" \
					"Example:\n" \
					"getchnencoder 2  // Retrieves encoding type for channel 2"

#define HELP_MESSAGE_FISHEYE "Usage: <encChn> <enable>\n" \
					"Fisheye correction effect may only be enabled or disabled before the channel is created."

#define HELP_MESSAGE_SETOSDCOVER "Usage: setOSDcover <enable> <color> <layer> <x0-width> <y0-height> <x1-width> <y1-height>\n" \
                                "enable: 1 (enable) or 0 (disable)\n" \
                                "color: color code as string (e.g. 'OSD_BLACK')\n" \
                                "layer: layer number\n" \
								"x0-width: stream width\n" \
								"y0-height: stream height\n" \
								"x1-width: stream width\n" \
								"y1-height: stream height"

#endif // HELP_MESSAGES_H
