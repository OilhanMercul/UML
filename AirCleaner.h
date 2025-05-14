using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include  <array>

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
    void setlongitude(const string& longitude);
    void setStart(const Date& start);
    void setEnd(const Date& end);
    int getId() const;
    string getLatitude() const;
    string getLongitude() const;
    Date getStart() const;
    Date getEnd() const;

    //Constructors and Destructor    
    AirCleaner(int id, string lat, string lon, Date start, Date end)
        : id(id), latitude(lat), longitude(lon), start(start), end(end) {}
    AirCleaner(const AirCleaner& user);
    virtual ~AirCleaner() {}
};
