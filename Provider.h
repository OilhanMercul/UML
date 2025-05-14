using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>

#include "User.h"
#include "AirCleaner.h"

class Provider {
protected: 
    list<AirCleaner> airCleaners;
    string companyName;

public:
    // Getters and Setters
    void setCompanyName(const string& name);
    string getCompanyName() const;
    void setAirCleaners(const list<AirCleaner>& airCleaners);
    list<AirCleaner> getAirCleaners() const;

    // Constructors and Destructor
    Provider(const string& name);
    Provider(const Provider& user);
    virtual ~Provider() {}
    
};
