# Nombre del ejecutable
TARGET = nesemu

# Directorios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Compilador y banderas
CC = gcc
CFLAGS = -Wall -I$(INC_DIR) `sdl2-config --cflags`  # Usamos las banderas de compilación de sdl2-config
LDFLAGS = `sdl2-config --libs`  # Usamos las banderas de enlace de sdl2-config

# Archivos fuente y objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Regla principal
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)  # Añadimos LDFLAGS en la regla de enlace

# Compilación de objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear directorio de objetos si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpiar
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)


