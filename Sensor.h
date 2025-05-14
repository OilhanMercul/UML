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

    //Constructors and Destructor
    Sensor(int id, const string& latitude, const string& longitude);
    Sensor(const Sensor& sensor);
    ~Sensor();


};
