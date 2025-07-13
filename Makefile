# -------------------------------------
# | Paths |
# -------------------------------------
ROOT	:= .
BIN 	:= ${ROOT}/bin
SRC 	:= ${ROOT}/src
INC 	:= ${ROOT}/inc
BUILD 	:= ${ROOT}/build

# -------------------------------------
# | Files |
# -------------------------------------
TARGET 	:= ${BIN}/genesis
OBJS	:= ${BUILD}/main.o
OBJS	+= ${BUILD}/lex.o
OBJS	+= ${BUILD}/parse.o
OBJS	+= ${BUILD}/ast.o
OBJS	+= ${BUILD}/type.o
OBJS	+= ${BUILD}/token.o
OBJS	+= ${BUILD}/variable.o
OBJS	+= ${BUILD}/vector.o
OBJS	+= ${BUILD}/hashmap.o
OBJS	+= ${BUILD}/assertf.o
OBJS	+= ${BUILD}/utility.o
OBJS	+= ${BUILD}/generics.o

# -------------------------------------
# | Compiler |
# -------------------------------------
CC := clang

# -------------------------------------
# | Compiler Flags |
# -------------------------------------
CFLAGS := -c
CFLAGS += -Wall
CFLAGS += -std=c17
CFLAGS += -I${INC}

# -------------------------------------
# | Linker Flags |
# -------------------------------------
LFLAGS := -WI,-e,main

.PHONY: all clean check redo

all: ${TARGET}

${TARGET}: ${OBJS}
	@mkdir -p $(dir $@)
	${CC} ${LFLAGS} ${OBJS} -o $@

${BUILD}/%.o: ${SRC}/%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} $< -o $@

clean:
	@rm -rf ${BIN}/*
	@rm -rf ${BUILD}/*

check:
	@make && make clean

redo:
	@make clean && make

