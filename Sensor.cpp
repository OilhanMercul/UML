#include "Sensor.h"

Sensor::Sensor(int id, const string& latitude, const string& longitude) {
    this->id = id;
    this->latitude = latitude;
    this->longitude = longitude;
}

Sensor::Sensor(const Sensor& sensor) {
    this->id = sensor.id;
    this->latitude = sensor.latitude;
    this->longitude = sensor.longitude;
}

void Sensor::setId(int id) {
    this->id = id;
}

int Sensor::getId() const {
    return this->id;
}

void Sensor::setLatitude(const string& latitude) {
    this->latitude = latitude;
}

string Sensor::getLatitude() const {
    return this->latitude;
}

void Sensor::setLongitude(const string& longitude) {
    this->longitude = longitude;
}

string Sensor::getLongitude() const {
    return this->longitude;
}

Sensor& Sensor::operator=(const Sensor& other) {
    if (this != &other) {
        this->id = other.id;
        this->latitude = other.latitude;
        this->longitude = other.longitude;
    }
    return *this;
}
