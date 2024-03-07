.PHONY: all clean

LIB_NAME := test
CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/objs


LIB_DIR := $(CUR_DIR)/libs
LIB_STATIC := $(LIB_DIR)/static
LIB_SHARED := $(LIB_DIR)/shared

INC_FLAGS := -I $(INC_DIR) 
CC := gcc

mk_objs_shared_lib:
	$(CC) -c       $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/hello.c -o $(OBJ_DIR)/hello.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/math.c -o $(OBJ_DIR)/math.o $(INC_FLAGS)

mk_objs_static_lib:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/hello.c -o $(OBJ_DIR)/hello.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/math.c -o $(OBJ_DIR)/math.o $(INC_FLAGS)

mk_shared:
	$(CC) -shared $(OBJ_DIR)/hello.o $(OBJ_DIR)/math.o -o $(LIB_SHARED)/lib$(LIB_NAME).so

mk_static:
	ar rcs $(LIB_SHARED)/lib$(LIB_NAME).a $(OBJ_DIR)/hello.o $(OBJ_DIR)/math.o

install:
	cp -f $(LIB_SHARED)/lib$(LIB_NAME).so /usr/lib

all_shared_lib:mk_objs_shared_lib mk_shared install
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_SHARED) -l$(LIB_NAME) -o $(BIN_DIR)/use-shared-library

all_static_lib: mk_objs_static_lib mk_static
	$(CC)  $(OBJ_DIR)/main.o  -L$(LIB_STATIC) -l$(LIB_NAME) -o $(BIN_DIR)/use-static-library
	
clean: 
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED)/lib$(LIB_NAME).so
	rm -rf $(BIN_DIR)/use-shared-library






