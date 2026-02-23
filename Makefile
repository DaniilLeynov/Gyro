GCC = gcc
TARGET = gyro
GCCFLAGS = -I./include -Wall
SOURCES = $(wildcard src/*.c)
BUILD_DIR = build
RAY_LIB = -lraylib
LM_LIB = -lm

$(TARGET): $(SOURCES) | $(BUILD_DIR)
	$(GCC) $(GCCFLAGS) $(SOURCES) -o $(BUILD_DIR)/$(TARGET) $(RAY_LIB) $(LM_LIB) 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


clean:
	rm -r $(BUILD_DIR)/$(TARGET)

.PHONY: clean

