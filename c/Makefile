CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = $(BUILD_DIR)/cnpj

all: $(TARGET)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: all clean rebuild
