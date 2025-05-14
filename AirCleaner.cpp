using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include  <array>

#include "AirCleaner.h"

AirCleaner::AirCleaner(int id, std::string lat, std::string lon, Date start, Date end)
    : id(id), latitude(lat), longitude(lon), start(start), end(end) {}

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
