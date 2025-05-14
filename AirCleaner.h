#ifndef AIRCLEANER_H
#define AIRCLEANER_H

using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

struct Date {
    int year;
    int month;
    int day;

    Date(int y = 0, int m = 0, int d = 0) : year(y), month(m), day(d) {}
};

class AirCleaner {
protected:
    // Attributs
    int id;
    std::string latitude;
    std::string longitude;
    Date start;
    Date end;

public:

    //Getters and Setters
    void setId(int id);
    void setLatitude(const string& latitude);
    void setLongitude(const string& longitude);
    void setStart(const Date& start);
    void setEnd(const Date& end);
    int getId() const;
    string getLatitude() const;
    string getLongitude() const;
    Date getStart() const;
    Date getEnd() const;
    
    void print() const {
        cout << "AirCleaner ID: " << id << endl;
        cout << "Latitude: " << latitude << endl;
        cout << "Longitude: " << longitude << endl;
        cout << "Start Date: " << start.year << "-" << start.month << "-" << start.day << endl;
        cout << "End Date: " << end.year << "-" << end.month << "-" << end.day << endl;
    }

    //Constructors and Destructor    
    AirCleaner(int id, const string& lat, const string& lon, const Date& start, const Date& end);
    AirCleaner(const AirCleaner& aircleaner);
    ~AirCleaner();
};


#endif