# Copyright (c) 2017 Json Lee. All rights reserved.
# For more info, see [here](https://github.com/lijiansong) or my [github page](https://lijiansong.github.io/)

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
CC = gcc -g
COMMON_FLAGS=-c -w -O2
#SOURCES=main.c utils.c
SOURCES=$(SRC_DIR)/elf-parser.c utils.c
PROJECT_OBJECTS=$(SOURCES:.c=.o)
PROJECT=elf-parser

all: $(SOURCES) $(PROJECT)

$(PROJECT): $(PROJECT_OBJECTS)
	@echo Compiling $(SOURCES)
	@echo Linking $@
	$(CC) $(PROJECT_OBJECTS) -o $@

.c.o:
	$(CC) $(COMMON_FLAGS) $< -o $@
clean:
	$(QUIET)rm -f *.o *.S elf-parser
