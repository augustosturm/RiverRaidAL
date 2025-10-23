CC := gcc
CFLAGS := -I. -IEntities -IMenuScore -Wall -Wextra -std=c99 
LDFLAGS := -lraylib -lm -lpthread -ldl -lrt -lX11

TARGET := main.out
SRC := main.c $(wildcard Entities/*.c) $(wildcard MenuScore/*.c)
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
