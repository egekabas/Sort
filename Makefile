CC = gcc
CFLAGS = -Wall -Wextra -g
OPTFLAGS = -O3

SRC_DIR = src
OBJ_DIR = obj
TARGET = sort

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)  # Default target

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
