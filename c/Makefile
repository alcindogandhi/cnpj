CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
SRC_DIR = src
MAIN_DIR = main
BUILD_DIR = build
INCLUDE_DIR = include

CNPJ_SRCS = $(SRC_DIR)/cnpj.c $(MAIN_DIR)/cnpj.c 
CNPJ_OBJS = $(BUILD_DIR)/cnpj.o $(BUILD_DIR)/cnpj_main.o
CNPJ_TARGET = $(BUILD_DIR)/cnpj

CPF_SRCS = $(SRC_DIR)/cpf.c $(MAIN_DIR)/cpf.c 
CPF_OBJS = $(BUILD_DIR)/cpf.o $(BUILD_DIR)/cpf_main.o
CPF_TARGET = $(BUILD_DIR)/cpf

all: cnpj cpf

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

cnpj: $(BUILD_DIR) $(CNPJ_TARGET)

cpf: $(BUILD_DIR) $(CPF_TARGET)

$(CNPJ_TARGET): $(CNPJ_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/cnpj.o: $(SRC_DIR)/cnpj.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/cnpj_main.o: $(MAIN_DIR)/cnpj.c 
	$(CC) $(CFLAGS) -c $^ -o $@

$(CPF_TARGET): $(CPF_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/cpf.o: $(SRC_DIR)/cpf.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/cpf_main.o: $(MAIN_DIR)/cpf.c 
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all clean rebuild cnpj cpf
