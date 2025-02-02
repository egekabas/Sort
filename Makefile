CC = gcc
CFLAGS = -Wall -Wextra -g
OPTFLAGS = -O3
DEBUGFLAGS = -DDEBUG

SRC_DIR = src
OBJ_DIR = obj
DEBUG_DIR = debug

TARGET = sort

SRCS := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(SRC_DIR)/*.h)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEBUG_OBJS := $(patsubst $(SRC_DIR)/%.c, $(DEBUG_DIR)/%.o, $(SRCS))

all: $(TARGET)  # Default target
 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) 
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) 
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $^ -o $@

debug: $(DEBUG_OBJS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $^ -o $(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
