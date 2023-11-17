# Makefile for libimp_control.so

#CROSS_COMPILE=mipsel-openipc-linux-musl-

# Compiler settings
CC := $(CROSS_COMPILE)gcc
CFLAGS := -fPIC -std=gnu99 -shared -ldl -lm -pthread

# Source files
SRCS := setlinebuf.c command.c imp_control.c

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
	@$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up build artifacts
clean:
	@echo "Cleaning up..."
	@rm -f $(TARGET) version.h

.PHONY: all clean version
