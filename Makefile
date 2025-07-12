# Files & Paths
ROOT	:= .
BIN 	:= ${ROOT}/bin
SRC 	:= ${ROOT}/src
INC 	:= ${ROOT}/inc
BUILD 	:= ${ROOT}/build
TARGET 	:= ${BIN}/genesis

# Compiler
CC := clang

# Compiler Flags
CFLAGS := -c
CFLAGS += -Wall
CFLAGS += -I${INC}

# Linker Flags
LFLAGS := 

.PHONY: all clean redo

all: ${TARGET}
	@mkdir -p $(dir $@)

clean:
	@rm -rf ${BIN}/*
	@rm -rf ${BUILD}/*

redo:
	make clean && make

