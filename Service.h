#ifndef SERVICE_H
#define SERVICE_H

#include <vector>
#include <string>
#include <utility>
#include "Sensor.h"
#include "Measurement.h"
#include "AirCleaner.h"
#include "Attribut.h"

using namespace std;

class Service {
public:
    Service();

    // Primary methods
    pair<float, float> displayImpactCleaners(const AirCleaner& airCleaner);
    pair<float, float> getAirQuality(const string& lat, const string& lon, const Date& date);

private:
    vector<AirCleaner> airCleaners;
    vector<Sensor> sensors;
    vector<Measurement> measurements;
    vector<Attribut> attributs;
    vector<PrivateIndividual> privateIndividuals;
    vector<Provider> providers;

    // Helper methods
    vector<Measurement> getMeasurementsNear(const string& lat, const string& lon);
    vector<Measurement> getMeasurementsByDate(const Date& date);
    Sensor getSensorByMeasurement(const Measurement& m);
    Attribut getInfoAttribute(const Measurement& m);
    float computeAverage(const vector<Measurement>& data);
    float calculateImprovement(float before, float after);
    float determineDistance(const Sensor& s1, const Sensor& s2);
    vector<Measurement> getMeasurementsBySensor(const Sensor& s);
};

#endif // SERVICE_H
