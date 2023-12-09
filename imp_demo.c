#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "imp_control_video.h"
#include <unistd.h>

// Function to generate random numbers within a specified range
int randomRange(int min, int max) {
	return min + rand() % (max - min + 1);
}

// Declaration of IMPTune function
char *IMPTune(int fd, char *tokenPtr);

// Function to demonstrate Mask settings
char* MaskDemo() {
	srand(time(NULL)); // Seed the random number generator
	printf("Starting Mask Demo\n");

	time_t start, now;
	time(&start);

	while (1) {
		time(&now);
		if (difftime(now, start) >= 10) break;

		char command[256];
		snprintf(command, sizeof(command), "mask 0 1 %d %d 320 240 %d %d %d",
				 randomRange(0, 640), randomRange(0, 1024),
				 randomRange(0, 255), randomRange(0, 255), randomRange(0, 255));

		printf("Command: %s\n", command); // Debug print
		IMPTune(0, command);
		usleep(500000);
	}

	char finalCommand[] = "mask 0 0 516 34 320 240 49 98 163";
	printf("Final Command: %s\n", finalCommand);
	IMPTune(0, finalCommand);

	return "Mask demo complete";
}

// Function to ramp control values for various settings
void rampControlValue(const char *controlName) {
	int value;
	int (*setFunctionInt)(int) = NULL;
	int (*setFunctionChar)(unsigned char) = NULL;
	int (*setFunctionUint)(uint32_t) = NULL;

	// Assign appropriate function based on control name
	if (strcmp(controlName, "brightness") == 0) {
		setFunctionChar = &IMP_ISP_Tuning_SetBrightness;
	} else if (strcmp(controlName, "contrast") == 0) {
		setFunctionChar = &IMP_ISP_Tuning_SetContrast;
	} else if (strcmp(controlName, "saturation") == 0) {
		setFunctionChar = &IMP_ISP_Tuning_SetSaturation;
	} else if (strcmp(controlName, "sharpness") == 0) {
		setFunctionChar = &IMP_ISP_Tuning_SetSharpness;
	} else if (strcmp(controlName, "sinter") == 0) {
		setFunctionUint = &IMP_ISP_Tuning_SetSinterStrength;
	} else if (strcmp(controlName, "temper") == 0) {
		setFunctionUint = &IMP_ISP_Tuning_SetTemperStrength;
	} else if (strcmp(controlName, "aecomp") == 0) {
		setFunctionInt = &IMP_ISP_Tuning_SetAeComp;
#ifndef CONFIG_T20
	} else if (strcmp(controlName, "dpc") == 0) {
		setFunctionUint = &IMP_ISP_Tuning_SetDPC_Strength;
#else
	printf("not supported on platform");
#endif
	} else if (strcmp(controlName, "drc") == 0) {
#ifndef CONFIG_T20
		setFunctionUint = &IMP_ISP_Tuning_SetDRC_Strength;
#else
	printf("not supported on platform");
#endif
	} else if (strcmp(controlName, "hue") == 0) {
#ifndef CONFIG_T20
		setFunctionChar = &IMP_ISP_Tuning_SetBcshHue;
#else
	printf("not supported on platform");
#endif
	}

	// Ramping logic for the control values
	for (value = 127; value >= 1; value--) {
		if (setFunctionInt) setFunctionInt(value);
		else if (setFunctionChar) setFunctionChar(value);
		else if (setFunctionUint) setFunctionUint(value);
		usleep(10000); // 0.05 seconds
	}

	for (value = 1; value <= 255; value++) {
		if (setFunctionInt) setFunctionInt(value);
		else if (setFunctionChar) setFunctionChar(value);
		else if (setFunctionUint) setFunctionUint(value);
		usleep(10000); // 0.05 seconds
	}

	for (value = 255; value >= 127; value--) {
		if (setFunctionInt) setFunctionInt(value);
		else if (setFunctionChar) setFunctionChar(value);
		else if (setFunctionUint) setFunctionUint(value);
		usleep(10000); // 0.05 seconds
	}
}

// Function to demonstrate White Balance settings
char* WhitebalanceDemo() {
	printf("Starting Whitebalance Demo\n");

	for (int wb = 1; wb <= 9; wb++) {
		char command[256];
		snprintf(command, sizeof(command), "whitebalance %d", wb % 10);

		printf("Command: %s\n", command); // Debug print
		IMPTune(0, command);
		sleep(2); // 1 second
	}

	return "Whitebalance demo complete";
}

// Function to demonstrate Auto Zoom feature
char* AutoZoomDemo() {
	printf("Starting AutoZoom Demo\n");

	for (double zoom = 1.0; zoom <= 1.5; zoom += 0.1) {
		int outWidth = (int)(1920 * zoom);
		int outHeight = (int)(1080 * zoom);

		char command[256];
		snprintf(command, sizeof(command), "autozoom 0 1 %d %d 1 0 0 1920 1080", outWidth, outHeight);

		printf("Autozoom: %.1f\n", zoom); // Debug print
		printf("Command: %s\n", command); // Debug print
		IMPTune(0, command);
		sleep(1); // 1 second
	}

	for (double zoom = 1.5; zoom >= 1.0; zoom -= 0.1) {
		int outWidth = (int)(1920 * zoom);
		int outHeight = (int)(1080 * zoom);

		char command[256];
		snprintf(command, sizeof(command), "autozoom 0 1 %d %d 1 0 0 1920 1080", outWidth, outHeight);

		printf("Autozoom: %.1f\n", zoom); // Debug print
		printf("Command: %s\n", command); // Debug print
		IMPTune(0, command);
		sleep(1); // 1 second
	}

	char finalCommand[] = "autozoom 0 0 2304 1296 0 0 0 1920 1080";
	printf("Final Command: %s\n", finalCommand); // Debug print
	IMPTune(0, finalCommand);

	return "Autozoom demo complete";
}

// Function to demonstrate Front Crop feature
char* FrontCropDemo() {
	printf("Starting Front Crop Demo\n");

	for (int v = 0; v <= 350; v++) {
		char command[1024];
		snprintf(command, sizeof(command), "frontcrop 1 %d 0 1280 720", v);
		IMPTune(0, command);
		usleep(8000); // 0.008 seconds
	}

	for (int v = 350; v >= 0; v--) {
		char command[1024];
		snprintf(command, sizeof(command), "frontcrop 1 %d 0 1280 720", v);
		IMPTune(0, command);
		usleep(8000); // 0.008 seconds
	}

	sleep(1);

	for (int v = 0; v <= 600; v++) {
		char command[1024];
		snprintf(command, sizeof(command), "frontcrop 1 0 %d 1280 720", v);
		IMPTune(0, command);
		usleep(8000); // 0.008 seconds
	}

	for (int v = 600; v >= 0; v--) {
		char command[1024];
		snprintf(command, sizeof(command), "frontcrop 1 0 %d 1280 720", v);
		IMPTune(0, command);
		usleep(8000); // 0.008 seconds
	}

	sleep(1);

	char finalCommand[] = "frontcrop 1 0 0 1920 1080";
	printf("Final Command: %s\n", finalCommand); // Debug print
	IMPTune(0, finalCommand);

	return "Front Crop demo complete";
}

void ispdemo() {
IMP_ISP_Tuning_SetISPRunningMode(1);
sleep(2);
IMP_ISP_Tuning_SetISPRunningMode(0);
}

// Function to run the full demo sequence
char* fullDemo() {
	printf("Starting Full Demo\n");
	const char *controls[] = {"brightness", "contrast", "saturation", "sharpness", "sinter", "temper", "aecomp", "dpc", "drc", "hue"};
	int numControls = sizeof(controls) / sizeof(controls[0]);

	MaskDemo();
	sleep(1);
	WhitebalanceDemo();
	sleep(1);
	FrontCropDemo();
	sleep(1);
// Autozoom requires performant SOCs for now    
//    AutoZoomDemo();
//    sleep(1);
	ispdemo();
	sleep(1);
	// Ramp all the controls
	for (int i = 0; i < numControls; i++) {
		printf("Ramping %s\n", controls[i]);
		rampControlValue(controls[i]);
		printf("Ramping %s complete\n", controls[i]);
	}
	return "Demo complete, restart for best performance.";
}
