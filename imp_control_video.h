#ifndef IMP_CONTROL_VIDEO_H
#define IMP_CONTROL_VIDEO_H

#include <stdbool.h>
#include <stdint.h>
#include "include/imp_osd.h"
#include "include/imp_common.h"

// AE Max parameters.
extern int IMP_ISP_Tuning_SetAe_IT_MAX(unsigned int it_max);
extern int IMP_ISP_Tuning_GetAE_IT_MAX(unsigned int *it_max);

// DPC Strength.
extern int IMP_ISP_Tuning_SetDPC_Strength(unsigned int ratio);
extern int IMP_ISP_Tuning_GetDPC_Strength(unsigned int *ratio);

// DRC Strength.
extern int IMP_ISP_Tuning_SetDRC_Strength(unsigned int ratio);
extern int IMP_ISP_Tuning_GetDRC_Strength(unsigned int *ratio);

// Hue
extern int IMP_ISP_Tuning_SetBcshHue(unsigned char hue);
extern int IMP_ISP_Tuning_GetBcshHue(unsigned char *hue);

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

extern int IMP_ISP_Tuning_SetAutoZoom(IMPISPAutoZoom *ispautozoom);

// ISP Front Crop
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

// ISP Backlight Compensation
extern int IMP_ISP_Tuning_SetBacklightComp(uint32_t strength);
extern int IMP_ISP_Tuning_GetBacklightComp(uint32_t *strength);

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

// AE compensation: parameters can adjust the target of the image AE.
extern int IMP_ISP_Tuning_SetAeComp(int comp);
extern int IMP_ISP_Tuning_GetAeComp(int *comp);

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
extern int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);

// ISP Sensor FPS
extern int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
extern int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);

typedef struct {
	uint32_t ev;                    /**< exposure value*/
	uint32_t expr_us;               /**< exposure time in millisecond */
	uint32_t ev_log2;               /**< exposure time in log2 format */
	uint32_t again;                 /**< Analog gain */
	uint32_t dgain;                 /**< Digital gain */
	uint32_t gain_log2;             /**< Gain in log2 format */
}IMPISPEVAttr;

extern int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);

extern int IMP_ISP_Tuning_GetAeLuma(int *luma);

extern int IMP_ISP_Tuning_SetAwbCt(unsigned int *ct);
extern int IMP_ISP_Tuning_GetAWBCt(unsigned int *ct);

extern int IMP_ISP_Tuning_GetAFMetrices(unsigned int *metric);

extern int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);

typedef enum {
	IMPISP_TUNING_OPS_MODE_DISABLE,                 /**< DISABLE mode of the current module */
	IMPISP_TUNING_OPS_MODE_ENABLE,                  /**< ENABLE mode of the current module */
	IMPISP_TUNING_OPS_MODE_BUTT,                    /**< effect paramater, parameters have to be less than this value*/
} IMPISPTuningOpsMode;

extern int IMP_ISP_Tuning_EnableDefog(IMPISPTuningOpsMode mode);
extern int32_t IMP_ISP_Tuning_SetDefog_Strength(uint8_t *ratio);
extern int32_t IMP_ISP_Tuning_GetDefog_Strength(uint8_t *ratio);

typedef struct {
	unsigned int min_it;  /**< AE min integration time */
	unsigned int min_again;  /**< AE min analog gain */
	unsigned int min_it_short; /**< AE min integration time on short frame */
	unsigned int min_again_short; /**< AE min analog gain on short frame */
} IMPISPAEMin;

extern int IMP_ISP_Tuning_SetAeMin(IMPISPAEMin *ae_min);
extern int IMP_ISP_Tuning_GetAeMin(IMPISPAEMin *ae_min);

typedef struct {
	/* Ae Manual Attr On Linear Mode and Long Frame Which on WDR MODE */
	IMPISPTuningOpsMode AeFreezenEn;    /* Ae Freezen Manual enable ctrl */
	IMPISPTuningOpsMode AeItManualEn;       /* Ae Integration time Manual enable ctrl */
	unsigned int AeIt;                         /* Ae Integration time value */
	IMPISPTuningOpsMode AeAGainManualEn;       /* Ae Sensor Analog Gain Manual enable ctrl */
	unsigned int AeAGain;                         /* Ae Sensor Analog Gain value */
	IMPISPTuningOpsMode AeDGainManualEn;       /* Ae Sensor Digital Gain Manual enable ctrl */
	unsigned int AeDGain;                         /* Ae Sensor Digital Gain value */
	IMPISPTuningOpsMode AeIspDGainManualEn;       /* Ae Isp Digital Gain Manual enable ctrl */
	unsigned int AeIspDGain;                         /* Ae Isp Digital Gain value */

	/* Ae Mnaual Attr on Short Frame Which on WDR Mode*/
	IMPISPTuningOpsMode AeWdrShortFreezenEn;    /* AeWdrShort Freezen Manual enable ctrl */
	IMPISPTuningOpsMode AeWdrShortItManualEn;       /* AeWdrShort Integration time Manual enable ctrl */
	unsigned int AeWdrShortIt;                         /* AeWdrShort Integration time value */
	IMPISPTuningOpsMode AeWdrShortAGainManualEn;       /* AeWdrShort Sensor Analog Gain Manual enable ctrl */
	unsigned int AeWdrShortAGain;                         /* AeWdrShort Sensor Analog Gain value */
	IMPISPTuningOpsMode AeWdrShortDGainManualEn;       /* AeWdrShort Sensor Digital Gain Manual enable ctrl */
	unsigned int AeWdrShortDGain;                         /* AeWdrShort Sensor Digital Gain value */
	IMPISPTuningOpsMode AeWdrShortIspDGainManualEn;       /* AeWdrShort Isp Digital Gain Manual enable ctrl */
	unsigned int AeWdrShortIspDGain;                         /* AeWdrShort Isp Digital Gain value */
} IMPISPAEAttr;

extern int IMP_ISP_Tuning_GetAeAttr(IMPISPAEAttr *ae);

//OSD position hook data
typedef struct {
	int x;
	int y;
	uint8_t	position;  
	//position
	//		   0=fixed, 1=top, 2=topright, 3=right
	//         4=bottomright, 5=bottom, 6=bottomleft
	//		   7=left, 8=topleft	  
} IMPOSDPosHook;

/*
todo:
DPS // T20 only
// Get all T20/T40/T41 specific functions too

int32_t IMP_ISP_SetDefaultBinPath(char *path)
int32_t IMP_ISP_GetDefaultBinPath(char *path)
int IMP_ISP_EnableTuning(void)
int IMP_ISP_DisableTuning(void)
int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable)
int IMP_ISP_Tuning_SetISPCustomMode(IMPISPTuningOpsMode mode)
int IMP_ISP_Tuning_GetISPCustomMode(IMPISPTuningOpsMode mode)
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma)
int IMP_ISP_Tuning_SetAeFreeze(IMPISPTuningOpsMode mode)
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr)
int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr)
IMP_ISP_Tuning_GetWB_GOL_Statis(IMPISPWB *wb)
int IMP_ISP_Tuning_SetAwbClust(IMPISPAWBCluster *awb_cluster);
int IMP_ISP_Tuning_GetAwbClust(IMPISPAWBCluster *awb_cluster);
int IMP_ISP_Tuning_SetAwbCtTrend(IMPISPAWBCtTrend *ct_trend);
int IMP_ISP_Tuning_GetAwbCtTrend(IMPISPAWBCtTrend *ct_trend);
int IMP_ISP_Tuning_Awb_GetRgbCoefft(IMPISPCOEFFTWB *isp_core_rgb_coefft_wb_attr);
int IMP_ISP_Tuning_Awb_SetRgbCoefft(IMPISPCOEFFTWB *isp_core_rgb_coefft_wb_attr)
int IMP_ISP_Tuning_EnableMovestate(void)
IMP_ISP_Tuning_DisableMovestate(void)
int IMP_ISP_Tuning_SetAeWeight(IMPISPWeight *ae_weight)
int IMP_ISP_Tuning_GetAeWeight(IMPISPWeight *ae_weight)
int IMP_ISP_Tuning_AE_GetROI(IMPISPWeight *roi_weight)
int IMP_ISP_Tuning_AE_SetROI(IMPISPWeight *roi_weight)
int IMP_ISP_Tuning_SetAwbWeight(IMPISPWeight *awb_weight)
int IMP_ISP_Tuning_GetAwbWeight(IMPISPWeight *awb_weight)
int IMP_ISP_Tuning_GetAwbZone(IMPISPAWBZONE *awb_zone)
int IMP_ISP_Tuning_SetWB_ALGO(IMPISPAWBALGO wb_algo)
int IMP_ISP_Tuning_SetAeHist(IMPISPAEHist *ae_hist)
int IMP_ISP_Tuning_GetAeHist(IMPISPAEHist *ae_hist)
int IMP_ISP_Tuning_GetAeHist_Origin(IMPISPAEHistOrigin *ae_hist)
int IMP_ISP_Tuning_GetAwbHist(IMPISPAWBHist *awb_hist)
int IMP_ISP_Tuning_SetAwbHist(IMPISPAWBHist *awb_hist)
int IMP_ISP_Tuning_GetAfHist(IMPISPAFHist *af_hist);
int IMP_ISP_Tuning_SetAfHist(IMPISPAFHist *af_hist)
int IMP_ISP_Tuning_SetAfWeight(IMPISPWeight *af_weight)
int IMP_ISP_Tuning_GetAfWeight(IMPISPWeight *af_weight)
int IMP_ISP_Tuning_GetAfZone(IMPISPZone *af_zone)
int IMP_ISP_Tuning_WaitFrame(IMPISPWaitFrameAttr *attr)
int IMP_ISP_Tuning_GetAeZone(IMPISPZone *ae_zone)
int IMP_ISP_Tuning_GetAeTargetList(IMPISPAETargetList *at_list)
int IMP_ISP_Tuning_GetAeTargetList(IMPISPAETargetList *at_list)
int IMP_ISP_Tuning_SetModuleControl(IMPISPModuleCtl *ispmodule)
int IMP_ISP_Tuning_GetModuleControl(IMPISPModuleCtl *ispmodule)
int IMP_ISP_WDR_ENABLE(IMPISPTuningOpsMode mode)
IMP_ISP_WDR_ENABLE_Get(IMPISPTuningOpsMode* mode)
int IMP_ISP_Tuning_GetSensorAttr(IMPISPSENSORAttr *attr)
int IMP_ISP_Tuning_EnableDRC(IMPISPTuningOpsMode mode)
int IMP_ISP_Tuning_SetCCMAttr(IMPISPCCMAttr *ccm)
int IMP_ISP_Tuning_GetCCMAttr(IMPISPCCMAttr *ccm)
int IMP_ISP_Tuning_SetAeAttr(IMPISPAEAttr *ae)
int IMP_ISP_Tuning_GetAeState(IMPISPAEState *ae_state)
int IMP_ISP_Tuning_SetScalerLv(IMPISPScalerLv *scaler_level)
int32_t IMP_ISP_SetAeAlgoFunc(IMPISPAeAlgoFunc *ae_func)
int32_t IMP_ISP_SetAwbAlgoFunc(IMPISPAwbAlgoFunc *awb_func)
int IMP_ISP_Tuning_GetBlcAttr(IMPISPBlcAttr *blc) //// NEXT
int32_t IMP_ISP_Tuning_SetCsc_Attr(IMPISPCscAttr *attr)
int32_t IMP_ISP_Tuning_GetCsc_Attr(IMPISPCscAttr *attr)
int32_t IMP_ISP_Tuning_SetWdr_OutputMode(IMPISPWdrOutputMode *mode)
int32_t IMP_ISP_Tuning_GetWdr_OutputMode(IMPISPWdrOutputMode *mode)
int32_t IMP_ISP_SetFrameDrop(IMPISPFrameDropAttr *attr)
int32_t IMP_ISP_GetFrameDrop(IMPISPFrameDropAttr *attr)
int32_t IMP_ISP_SetFixedContraster(IMPISPFixedContrastAttr *attr) /// NEXT

int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderChnAttr * const attr);
int IMP_Encoder_Query(int encChn, IMPEncoderChnStat *stat);

int IMP_Encoder_SetFisheyeEnableStatus(int encChn, int enable); /// NEXT
int IMP_Encoder_GetFisheyeEnableStatus(int encChn, int *enable);
int IMP_Encoder_GetPool(int chnNum);
int IMP_Encoder_GetStreamBufSize(int encChn, uint32_t *nrStreamSize);
int IMP_Encoder_GetChnAveBitrate(int encChn, IMPEncoderStream *stream, int frames, double *br);
int IMP_Encoder_GetChnEvalInfo(int encChn, void *info);
int IMP_Encoder_SetChnEntropyMode(int encChn,IMPEncoderEntropyMode eEntropyMode);
int IMP_FrameSource_GetChnAttr(int chnNum, IMPFSChnAttr *chnAttr);
int IMP_FrameSource_GetFrameDepth(int chnNum, int *depth);
int IMP_FrameSource_ChnStatQuery(int chnNum, IMPFSChannelState *pstate);

*/

#endif // IMP_CONTROL_VIDEO_H
