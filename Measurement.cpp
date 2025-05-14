using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include  <array>

#include "Measurement.h"

// Constructor
Measurement::Measurement(int id, const Date& date, const Sensor& sensor, const Attribut& attribut, float value){
    this->id=id;
    this->date=date;
    this->sensor=sensor;
    this->attribut=attribut;
    this->value=value;
    }

// Copy constructor
Measurement::Measurement(const Measurement& measurement){
    this->id=measurement.id;
    this->date=measurement.date;
    this->sensor=measurement.sensor;
    this->attribut=measurement.attribut;
    this->value=measurement.value;
}

// Destructor
Measurement::~Measurement() {}

// Getters
int Measurement::getId() const {
    return id;
}

Date Measurement::getDate() const {
    return date;
}

const Sensor& Measurement::getSensor() const {
    return sensor;
}

const Attribut& Measurement::getAttribut() const {
    return attribut;
}

float Measurement::getValue() const {
    return value;
}

// Setters
void Measurement::setId(int id) {
    this->id = id;
}

void Measurement::setDate(const Date& date) {
    this->date = date;
}

void Measurement::setSensor(const Sensor& sensor) {
    this->sensor = sensor;
}

void Measurement::setAttribut(const Attribut& attribut) {
    this->attribut = attribut;
}

void Measurement::setValue(float value) {
    this->value = value;
}