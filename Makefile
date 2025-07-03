TARGET = aardvark_i2c_example.exe
SRC = src/main.c src/aardvark.c
INCLUDE_PATH = include
CC = gcc
CFLAGS = -I$(INCLUDE_PATH) -Wall -Wextra

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	del /Q $(TARGET)

.PHONY: all clean
