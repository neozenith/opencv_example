# Global Variables
CFLAGS := -Wall
INCLUDE_DIR := -I. -I/usr/local/include/
LIBS_DIR := -L. -L/usr/local/lib/
CC := g++
LIBS := -lstdc++ \
	-lopencv_imgcodecs \
	-lopencv_highgui \
	-lopencv_core \
	-lopencv_imgproc \
	-lopencv_videoio


# Build Targets
all:
	$(CC) \
	$(CFLAGS) \
	$(INCLUDE_DIR) \
	$(LIBS_DIR) \
	$(LIBS) \
	-o test main.cpp 

clean:
	rm -rf test
