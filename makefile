# Nom de l'exécutable
EXEC = main

# Fichiers source
SRC = main.cpp Provider.cpp User.cpp AirCleaner.cpp PrivateIndividual.cpp Attribut.cpp Measurement.cpp Sensor.cpp 

# Options du compilateur
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Cibles
all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

clean:
	rm -f $(EXEC)

.PHONY: all clean
