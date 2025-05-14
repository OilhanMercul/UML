using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include  <array>

#include "Provider.h"

Provider::Provider(const string& name) : companyName(name) {
    // Constructor implementation
}

Provider::Provider(const Provider& user) : companyName(user.companyName), airCleaners(user.airCleaners) {
    // Copy constructor implementation
}

void Provider::setCompanyName(const string& name) {
    companyName = name;
}

string Provider::getCompanyName() const {
    return companyName;
}

void Provider::setAirCleaners(const list<AirCleaner>& airCleaners) {
    this->airCleaners = airCleaners;
}

list<AirCleaner> Provider::getAirCleaners() const {
    return airCleaners;
}

