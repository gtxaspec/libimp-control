# Makefile for libimp_control.so

#CROSS_COMPILE=mipsel-openipc-linux-musl-

# Compiler settings
CC := $(CROSS_COMPILE)gcc
CFLAGS := -fPIC -std=gnu99 -shared -ldl -lm -pthread -Os -ffunction-sections -fdata-sections -fomit-frame-pointer
LDFLAGS := -Wl,--gc-sections

# Macro for T10/T20/T30/T21
ifeq ($(CONFIG_SOC),t21)
    # If CONFIG_SOC is T21
    CFLAGS += -DCONFIG_T20 -DCONFIG_T21
else ifeq ($(filter $(CONFIG_SOC),t10 t20 t30),)
    # If CONFIG_SOC is NOT T10/T20/T30 (implies T31 or others)
    CFLAGS += -DCONFIG_T31
else
    # If CONFIG_SOC is T10/T20/T30
    CFLAGS += -DCONFIG_T20
endif

# Source files
SRCS := command.c imp_control.c imp_control_audio.c imp_control_video.c imp_control_util.c imp_demo.c

# Target library
TARGET := libimp_control.so

# Define commit_tag (example: get from git or environment)
commit_tag ?= $(shell git rev-parse --short HEAD)

# Default target
all: version $(TARGET)

# Version target as a file target
version.h:
	@echo "Updating version.h with commit tag $(commit_tag)"
	@sed 's/COMMIT_TAG/"$(commit_tag)"/g' version.tpl.h > version.h

# Rule to build the target library
$(TARGET): $(SRCS) version.h
	@echo "Building target $(TARGET) with CC=$(CC)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRCS)
	@echo "Stripping target $(TARGET)"
	@$(CROSS_COMPILE)strip --strip-unneeded $(TARGET)

# Clean up build artifacts
clean:
	@echo "Cleaning up..."
	@rm -f $(TARGET) version.h

.PHONY: all clean version
