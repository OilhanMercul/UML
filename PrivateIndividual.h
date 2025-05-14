#ifndef PRIVATEINDIVIDUAL_H
#define PRIVATEINDIVIDUAL_H

using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>

#include "User.h"
#include "Sensor.h"

class PrivateIndividual : public User {
protected:
    //Attributes
    string firstName;
    string lastName;
    string phone;
    list<Sensor> sensors;
    int points;
    bool reliable;
    string address;


public:
    //Getters and Setters
    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    void setPhone(const string& phone);
    void setAddress(const string& address);
    string getFirstName() const;
    string getLastName() const;
    string getPhone() const;
    string getAddress() const;
    list<Sensor> getSensors() const;
    void setSensors(const list<Sensor>& sensors);
    void setPoints(int points);
    int getPoints() const;
    bool getReliable() const;
    void setReliable(bool reliable);

    void print() const; // Pure virtual function

    //Constructors and Destructor
    PrivateIndividual(int id, const string& password, const string& email, const string& firstName, const string& lastName, const string& phone, const string& address);
    PrivateIndividual(const PrivateIndividual& privateIndividual);
    virtual ~PrivateIndividual();

    //Methods
    int consultPoints();
};


#endif