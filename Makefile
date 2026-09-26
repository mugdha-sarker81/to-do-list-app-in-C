CC = gcc
CFLAGS ?= -std=c11 -Wall -Wextra
ifeq ($(OS),Windows_NT)
TARGET = todo.exe
else
TARGET = todo
endif
SOURCES = main.c tasks.c habits.c calendar.c
HEADERS = tasks.h habits.h calendar.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	$(RM) todo todo.exe
