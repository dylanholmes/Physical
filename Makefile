SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .h .cc .o

FRAMEWORKS= -framework OpenGL -framework SDL2

CXX=g++
CXXFLAGS=$(FRAMEWORKS)

SRC_DIR=./src
BUILD_DIR=./build

HEADERS=$(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/**/*.h)
SRC=$(wildcard $(SRC_DIR)/*.cc) $(wildcard $(SRC_DIR)/**/*.cc)

DEMO_SRC_DIR=$(SRC_DIR)/demos
DEMO_BUILD_DIR=$(BUILD_DIR)/demos
DEMO_NAMES=$(patsubst $(DEMO_SRC_DIR)/%.cc, %, $(filter $(DEMO_SRC_DIR)/%, $(SRC)))

SHADER_SRC_DIR=$(SRC_DIR)/shaders
SHADER_DEMO_BUILD_DIR=$(DEMO_BUILD_DIR)/shaders

all: beef $(DEMO_NAMES)

beef:
	@echo $(DEMO_NAMES)
	@echo

$(DEMO_NAMES): $(HEADERS) $(SRC) demo_shaders
	mkdir -p $(DEMO_BUILD_DIR)
	$(CXX) $(SRC) -o $(DEMO_BUILD_DIR)/$@ $(CXXFLAGS) 

demo_shaders:
	cp -r $(SHADER_SRC_DIR) $(SHADER_DEMO_BUILD_DIR)

.PHONY: clean demo_shaders
