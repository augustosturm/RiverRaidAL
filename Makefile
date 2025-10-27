CC := gcc
CFLAGS := -I. -IEntidades -IMenuScore -Wall -Wextra -std=c99 
LDFLAGS := -lraylib -lm -lpthread -ldl -lrt -lX11

TARGET := main.out
SRC := main.c $(wildcard Entidades/*.c) $(wildcard Menu/*.c) $(wildcard Menu/MenuScore/*.c)
OBJ := $(SRC:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
