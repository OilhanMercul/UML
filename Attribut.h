#ifndef ATTRIBUT_H
#define ATTRIBUT_H

using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include  <array>

class Attribut {
protected:
    //Atributes
    int id;
    string unit;
    string description;

    //Getters and Setters
    void setId(int id);
    void setUnit(const string& unit);
    void setDescription(const string& description);
    int getId() const;
    string getUnit() const;
    string getDescription() const;

    //Constructors and Destructor
    Attribut(int id, const string& unit, const string& description);
    Attribut(const User& attribut);
    ~Attribut();

};

#endif