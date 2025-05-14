using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include  <array>

#include "Attribut.h"


//Constructeur
Attribut::Attribut(int id, const string& unit, const string& description){
    this->id = id;
    this->unit = unit;
    this->description = description;
}

Attribut::Attribut(const Attribut& attribut) {
    this->unit = user.unit;
    this->description = user.description;
    this->id = user.id;
}


//Setters et getters
void Attribut::setUnit(const string& unit) {
    this->unit = unit;
}

string Attribut::getUnit() const {
    return this->password;
}

void Attribut::setDescription(const string& description) {
    this->description = description;
}

string Attribut::getDescription() const {
    return this->description;
}

void Attribut::setId(int id) {
    this->id = id;
}

int Attribut::getId() const {
    return this->id;
}