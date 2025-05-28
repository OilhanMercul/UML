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
    int points;
    string address;
    string firstName;
    string lastName;
    string phone;
    list<Sensor> sensors;
    bool reliable;



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
    void addSensor(const Sensor& sensor) { sensors.push_back(sensor); }
    void setPoints(int points);
    int getPoints() const;
    bool getReliable() const;
    void setReliable(bool reliable);

    void print() const; // Pure virtual function

    //Constructors and Destructor
    PrivateIndividual(int id, const string& password, const string& email, const string& firstName, const string& lastName, const string& phone, const string& address);
    PrivateIndividual() : User(), points(0), address(""), firstName(""), lastName(""), phone(""), reliable(true) {};
    PrivateIndividual(const PrivateIndividual& privateIndividual);

    //Methods
    int consultPoints();
};


#endif