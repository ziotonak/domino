NAME        := domino
CC          := gcc
CFLAGS      := -Werror -Wall -Wextra -pedantic -I include -g


SRC_DIR     := lib
OBJ_DIR     := obj
BIN_DIR     := bin

SRCS 		:= $(wildcard $(SRC_DIR)/*.c)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RM          := rm -rf
ifeq ($(OS),Windows_NT)
	RM = rmdir /s /q
endif


all: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(OBJS)
	@-mkdir $(@D)
	@-$(CC) $(OBJS) -o $(BIN_DIR)/$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@-mkdir $(@D)
	@-$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<



.PHONY: clean rebuild

clean:
	@-$(RM) $(OBJ_DIR)
	@-$(RM) $(BIN_DIR)

rebuild:
	@-$(MAKE) clean
	@-$(MAKE) all
