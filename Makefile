# Paths
ROOT	:= .
BIN 	:= ${ROOT}/bin
SRC 	:= ${ROOT}/src
INC 	:= ${ROOT}/inc
BUILD 	:= ${ROOT}/build

# Files
TARGET 	:= ${BIN}/genesis
OBJS	:= ${BUILD}/main.o
OBJS	+= ${BUILD}/utility.o

# Compiler
CC := clang

# Compiler Flags
CFLAGS := -c
CFLAGS += -Wall
CFLAGS += -std=c17
CFLAGS += -I${INC}

# Linker Flags
LFLAGS := 

.PHONY: all clean redo

all: ${TARGET}
	@mkdir -p $(dir $@)

${TARGET}: ${OBJS}
	@mkdir -p $(dir $@)
	${CC} ${LFLAGS} ${OBJS} -o $@

${BUILD}/%.o: ${SRC}/%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} $< -o $@

clean:
	@rm -rf ${BIN}/*
	@rm -rf ${BUILD}/*

redo:
	make clean && make

