# Noms des exécutables
EXEC = main
TEST_EXEC = test

# Fichiers source communs
SRC_COMMON = Provider.cpp User.cpp AirCleaner.cpp PrivateIndividual.cpp Attribut.cpp Measurement.cpp Sensor.cpp

# Fichiers source pour l'exécutable principal
SRC = main.cpp $(SRC_COMMON)

# Fichiers source pour l'exécutable de test
TEST_SRC = main_test.cpp $(SRC_COMMON)

# Options du compilateur
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Cibles
all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_SRC)

clean:
	rm -f $(EXEC) $(TEST_EXEC)

.PHONY: all clean test
