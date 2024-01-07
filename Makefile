TARGET_EXEC := domino

CC := gcc
CFLAGS := -Werror -Wall -Wextra -pedantic -I include -g

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RM := rm -rf
ifeq ($(OS),Windows_NT)
	RM = rmdir /s /q
endif

.PHONY: all
all: $(BIN_DIR)/$(TARGET_EXEC)

$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	@-mkdir $(@D)
	@-$(CC) $(OBJS) -o $(BIN_DIR)/$(TARGET_EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@-mkdir $(@D)
	@-$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@-$(RM) $(OBJ_DIR) $(BIN_DIR)

.PHONY: rebuild
rebuild: clean all

