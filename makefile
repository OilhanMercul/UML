# Nom de l'exécutable
TARGET = AirWatcher

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -g

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Règle par défaut
all: $(BIN_DIR)/$(TARGET)

# Création de l'exécutable
$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Nettoyage complet
distclean: clean
	rm -f *~ $(SRC_DIR)/*~ $(SRC_DIR)/*.bak

# Règles phony
.PHONY: all clean distclean