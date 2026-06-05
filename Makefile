CC = gcc
C_STD = -std=c11
CFLAGS = $(C_STD) -Wall -Og -g
INCLUDE = -I ./head

OBJ_DIR = objs
SRCS = $(wildcard src/*.c) main.c
OBJS = $(SRCS:.c=.o)

TARGET = management_system

all: $(TARGET)

$(TARGET): $(OBJS) | $(OBJ_DIR)
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $(OBJS)
	mv $(OBJS) $(OBJ_DIR)

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(TARGET) $(OBJ_DIR)

.PHONY: all clean
