#ifndef ATTRIBUT_H
#define ATTRIBUT_H

using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

#include "User.h"

class Attribut {
protected:
    //Atributes
    string id;
    string unit;
    string description;

public:
    //Getters and Setters
    void setId(string id);
    void setUnit(const string& unit);
    void setDescription(const string& description);
    string getId() const;
    string getUnit() const;
    string getDescription() const;

    //Operator
    Attribut& operator=(const Attribut& other);

    //Constructors and Destructor
    Attribut(string id, const string& unit, const string& description);
    Attribut() : id(""), unit(""), description("") {}
    Attribut(const Attribut& attribut);
    void print() const {
        cout << "Attribut ID: " << id << endl;
        cout << "Unit: " << unit << endl;
        cout << "Description: " << description << endl;
    }

};

#endif