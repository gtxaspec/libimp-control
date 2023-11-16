# libimp_control.so

CC = mips-linux-uclibc-gnu-gcc
CFLAGS = -fPIC -std=gnu99 -shared -ldl -lm -pthread
CC_SRCS = setlinebuf.c command.c imp_control.c video_callback.c
TARGET = libimp_control.so

all: ${TARGET}

${TARGET}: ${CC_SRCS}
	${CC} ${CFLAGS} -o ${TARGET} ${CC_SRCS}

clean:
	rm -f libimp_control.so

