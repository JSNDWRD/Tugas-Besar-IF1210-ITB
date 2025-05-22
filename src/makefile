# Compiler and flags
CC = gcc
CFLAGS = -g -Wall

# Directories
CDIR = c
BUILD_DIR = build
CBUILD_DIR = $(BUILD_DIR)/c

# Source and object files
MAIN_SRCS = $(wildcard *.c)
C_SRCS = $(wildcard $(CDIR)/*.c)

MAIN_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(MAIN_SRCS))
C_OBJS = $(patsubst $(CDIR)/%.c, $(CBUILD_DIR)/%.o, $(C_SRCS))

OBJS = $(MAIN_OBJS) $(C_OBJS)

# Executable
TARGET = main

# Default target
all: prepare_dirs $(TARGET)

# Prepare required directories
prepare_dirs:
	mkdir -p $(BUILD_DIR) $(CBUILD_DIR)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile main .c files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile c/*.c files
$(CBUILD_DIR)/%.o: $(CDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)