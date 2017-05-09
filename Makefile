CC=gcc
TARGET=main

all:$(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $< -lGLEW -lglfw -lGL -o $(TARGET)

$(TARGET).o: $(TARGET).c
	$(CC) -c $<

run: $(TARGET)
	./$(TARGET)
