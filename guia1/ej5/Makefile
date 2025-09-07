# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Wextra -g

# Nombre del ejecutable
TARGET = ej5

# Busca automáticamente todos los .c del directorio
SRCS = $(wildcard *.c)

# Convierte cada .c en su .o correspondiente
OBJS = $(SRCS:.c=.o)

# Regla principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regla genérica para compilar cada .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos
clean:
	rm -f $(TARGET) $(OBJS)
