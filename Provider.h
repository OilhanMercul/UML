#ifndef PROVIDER_H
#define PROVIDER_H

using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>

#include "User.h"
#include "AirCleaner.h"

class Provider : public User {
protected: 
    list<AirCleaner> airCleaners;
    string companyName;

public:
    // Getters and Setters
    void setCompanyName(const string& name);
    string getCompanyName() const;
    void setAirCleaners(const list<AirCleaner>& airCleaners);
    list<AirCleaner> getAirCleaners() const;
    virtual void print() const; // Pure virtual function

    // Constructors and Destructor
    Provider(int id, const string& password, const string& email, const string& name);
    Provider(const Provider& user);
};


#endif