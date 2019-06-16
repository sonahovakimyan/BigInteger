CC		:= g++
C_FLAGS := -std=c++11 -Wall -Wextra

SRC		:= src
INCLUDE	:= include

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif

all: $(EXECUTABLE)

clean:
	$(RM) $(EXECUTABLE)

run: all
	./$(EXECUTABLE)

$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -o $@