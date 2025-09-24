# Define el compilador y las banderas de compilación
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Define el nombre del ejecutable final
TARGET = mi_proyecto

# Define los archivos objeto que componen el proyecto
# Los archivos .o son archivos compilados intermedios
OBJS = main.o lista.o pila.o cola.o

# La regla por defecto: construye el ejecutable final
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regla para limpiar el proyecto
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Proyecto limpio."

# Reglas específicas para cada archivo objeto
# Le dice a 'make' cómo compilar un archivo .c en un archivo .o
main.o: main.c lista.h pila.h cola.h
	$(CC) $(CFLAGS) -c main.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c lista.c

pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -c pila.c

cola.o: cola.c cola.h
	$(CC) $(CFLAGS) -c cola.c