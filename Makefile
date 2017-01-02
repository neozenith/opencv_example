# Global Variables
INCLUDE_DIR := -I. -I/usr/local/include/
LIBS_DIR := -L. -L/usr/local/lib/
CC := g++
LIBS := -lstdc++ -lopencv_imgcodecs -lopencv_highgui -lopencv_core


# Build Targets
all:
	$(CC) \
	$(INCLUDE_DIR) \
	$(LIBS_DIR) \
	$(LIBS) \
	-o test main.cpp 
