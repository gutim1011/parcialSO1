# Compilador y flags
CC = g++
CFLAGS = -Wall -Wextra -std=c++17

# Nombre del ejecutable
TARGET = rle_compresor

# Archivo fuente
SRC = rle.cpp
OBJ = rle.o

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(TARGET) $(OBJ)
