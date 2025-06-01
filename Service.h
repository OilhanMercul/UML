#ifndef SERVICE_H
#define SERVICE_H

#define _USE_MATH_DEFINES
#include "Sensor.h"
#include "Measurement.h"
#include "AirCleaner.h"
#include "Attribut.h"
#include "PrivateIndividual.h"
#include "Provider.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

class Service {
public:
    Service();

    // Primary methods
    pair<float, float> displayImpactCleaners(const AirCleaner& airCleaner);
    float getAirQuality(const string& lat, const string& lon, const Date& date, const int radius = 10);

    const vector<AirCleaner>& getAirCleaners() const { return airCleaners; }
    const vector<Sensor>& getSensors() const { return sensors; }
    const vector<Measurement>& getMeasurements() const { return measurements; }
    const vector<Attribut>& getAttributs() const { return attributs; }
    const vector<PrivateIndividual>& getPrivateIndividuals() const { return privateIndividuals; }
    const vector<Provider>& getProviders() const { return providers; }

    float computeAtmoIndex(const vector<Measurement>& data);
    int getAtmoIndex(const string& attributeId, float value);

private:
    vector<AirCleaner> airCleaners;
    vector<Sensor> sensors;
    vector<Measurement> measurements;
    vector<Attribut> attributs;
    vector<PrivateIndividual> privateIndividuals;
    vector<Provider> providers;

    int calculateAtmoIndex(const map<string, float> &averages);

    // Helper methods
    vector<Measurement> getMeasurementsNear(const string& lat, const string& lon);
    vector<Measurement> getMeasurementsByDate(const Date& date);
    Sensor getSensorByMeasurement(const Measurement& m);
    Attribut getInfoAttribute(const Measurement& m);
    float computeAverage(const vector<Measurement>& data);
    float calculateImprovement(float before, float after);
    
};

#endif // SERVICE_H
