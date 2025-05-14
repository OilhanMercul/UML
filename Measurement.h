#ifndef MEASUREMENT_H
#define MEASUREMENT_H

using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include  <array>
#include "AirCleaner.h" // pour la struct Date
#include "Sensor.h"
#include "Attribut.h"

class Measurement {
protected:
    // Attributes
    int id;
    Date date;
    Sensor sensor;
    Attribut attribut;
    float value;

public:
    // Getters
    int getId() const;
    Date getDate() const;
    const Sensor& getSensor() const;
    const Attribut& getAttribut() const;
    float getValue() const;

    // Setters
    void setId(int newId);
    void setDate(const Date& newDate);
    void setSensor(const Sensor& newSensor);
    void setAttribut(const Attribut& newAttribut);
    void setValue(float newValue);

    // Constructors and Destructor
    Measurement(int id, const Date& date, const Sensor& sensor, const Attribut& attribut, float value);
    Measurement(const Measurement& measurement);
    ~Measurement();
};

#endif