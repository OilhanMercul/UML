#ifndef SENSOR_H
#define SENSOR_H

using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

class Sensor {
protected:
    //Attributes
    int id;
    string latitude;
    string longitude;

public:
    //Getters and Setters
    void setId(int id);
    void setLatitude(const string& latitude);
    void setLongitude(const string& longitude);
    int getId() const;
    string getLatitude() const;
    string getLongitude() const;


    //Operator
    Sensor& operator=(const Sensor& other); 


    void print() const {
        cout << "Sensor ID: " << id << endl;
        cout << "Latitude: " << latitude << endl;
        cout << "Longitude: " << longitude << endl;
    }


    //Constructors and Destructor
    Sensor(int id, const string& latitude, const string& longitude);
    Sensor(const Sensor& sensor);
    Sensor() : id(0), latitude(""), longitude("") {}


};


#endif