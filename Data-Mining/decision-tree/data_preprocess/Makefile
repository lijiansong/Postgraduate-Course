# Copyright (c) 2016 Json Lee. All rights reserved.
# For more info, see [here](https://github.com/lijiansong) or my [github page](https://lijiansong.github.io/)

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
CC = g++ -g
COMMON_FLAGS=-c -w -O2
#SOURCES=main.cpp utils.cpp
SOURCES=$(SRC_DIR)/main.cpp pre_process.cpp
PROJECT_OBJECTS=$(SOURCES:.c=.o)
PROJECT=pre-process

all: $(SOURCES) $(PROJECT)

$(PROJECT): $(PROJECT_OBJECTS)
	@echo Compiling $(SOURCES)
	@echo Linking $@
	$(CC) $(PROJECT_OBJECTS) -o $@

.c.o:
	$(CC) $(COMMON_FLAGS) $< -o $@
clean:
	$(QUIET)rm -f *o pre-process
	$(QUIET)rm -f kddcup.data_10_percent.txt_preprocessing
