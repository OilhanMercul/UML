#include "AirCleaner.h"

AirCleaner::AirCleaner(int id, const string& lat, const string& lon, const Date& start, const Date& end){
    this->id = id;
    this->latitude = lat;
    this->longitude = lon;
    this->start = start;
    this->end = end;
}



AirCleaner::AirCleaner(const AirCleaner& aircleaner) {
    this->id = aircleaner.id;
    this->latitude = aircleaner.latitude;
    this->longitude = aircleaner.longitude;
    this->start = aircleaner.start;
    this->end = aircleaner.end;
}

AirCleaner::~AirCleaner() {}

int AirCleaner::getId() const {
    return id;
}

std::string AirCleaner::getLatitude() const {
    return latitude;
}

std::string AirCleaner::getLongitude() const {
    return longitude;
}

Date AirCleaner::getStart() const {
    return start;
}

Date AirCleaner::getEnd() const {
    return end;
}

void AirCleaner::setId(int newId) {
    id = newId;
}

void AirCleaner::setLatitude(const std::string& lat) {
    latitude = lat;
}

void AirCleaner::setLongitude(const std::string& lon) {
    longitude = lon;
}

void AirCleaner::setStart(const Date& d) {
    start = d;
}

void AirCleaner::setEnd(const Date& d) {
    end = d;
}

AirCleaner& AirCleaner::operator=(const AirCleaner& other) {
    if (this != &other) {
        id = other.id;
        latitude = other.latitude;
        longitude = other.longitude;
        start = other.start;
        end = other.end;
    }
    return *this;
}
