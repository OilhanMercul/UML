#include "Provider.h"



Provider::Provider(int id, const string& password, const string& email, const string& name)
    : User(id, password, email), companyName(name), airCleaners() {
    this->airCleaners = list<AirCleaner>(); // Initialize airCleaners to an empty list
}

Provider::Provider(const Provider& user)
    : User(user), companyName(user.companyName), airCleaners(user.airCleaners) {
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

void Provider::print() const {
    cout << "Provider ID: " << id << endl; // Assuming id is inherited from User
    cout << "Provider Password: " << password << endl; // Assuming password is inherited from User
    cout << "Provider Email: " << email << endl; // Assuming email is inherited from User
    cout << "Company Name: " << companyName << endl;
    cout << "Air Cleaners: " << endl;
    for (const auto& airCleaner : airCleaners) {
        airCleaner.print(); // Assuming AirCleaner has a print method
    }
}

void Provider::addAirCleaner(const AirCleaner& airCleaner) {
    airCleaners.push_back(airCleaner);
}

