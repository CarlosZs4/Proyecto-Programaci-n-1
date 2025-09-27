# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -D_DEFAULT_SOURCE
LDFLAGS = 

# Archivos objeto
OBJS = main.o AsistenteIA.o lista.o pila.o usuarios.o

# Nombre del ejecutable
TARGET = proyecto

# Regla principal
all: $(TARGET)

# Enlace del ejecutable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Regla genérica para archivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean rebuild