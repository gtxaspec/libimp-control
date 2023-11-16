# Makefile for libimp_control.so

# Compiler settings
CC := mips-linux-uclibc-gnu-gcc
CFLAGS := -fPIC -std=gnu99 -shared -ldl -lm -pthread

# Source files
SRCS := setlinebuf.c command.c imp_control.c control_old.c

# Target library
TARGET := libimp_control.so

# Define commit_tag (example: get from git or environment)
commit_tag ?= $(shell git rev-parse --short HEAD)

# Default target
all: version $(TARGET)

# Version target
version:
	@if ! grep -q "$(commit_tag)" version.h 2>/dev/null ; then \
		echo "Updating version.h with commit tag $(commit_tag)"; \
		sed 's/COMMIT_TAG/"$(commit_tag)"/g' version.tpl.h > version.h; \
	else \
		echo "version.h is up to date with commit tag $(commit_tag)"; \
	fi

# Rule to build the target library
$(TARGET): $(SRCS) version.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up build artifacts
clean:
	rm -f $(TARGET) version.h

.PHONY: all version clean
