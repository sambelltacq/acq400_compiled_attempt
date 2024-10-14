#CXX = g++
CXX = arm-linux-gnueabihf-g++
CXXFLAGS = -Iinclude -O2 -std=c++17

SRC_FILES = src/*
TARGET = bin/render_template

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf bin

.PHONY: all clean
