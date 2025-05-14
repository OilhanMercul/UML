#ifndef SERVICE_H
#define SERVICE_H

#include <vector>
#include <string>
#include <utility>
#include "Sensor.h"
#include "Measurement.h"
#include "AirCleaner.h"
#include "Attribut.h"

class Service {
public:
    Service();

    // Primary methods
    std::pair<float, float> displayImpactCleaners(const AirCleaner& airCleaner);
    std::pair<float, float> getAirQuality(const std::string& lat, const std::string& lon, const Date& date);

private:
    std::vector<AirCleaner> airCleaners;
    std::vector<Sensor> sensors;
    std::vector<Measurement> measurements;
    std::vector<Attribut> attributs;

    // Helper methods
    std::vector<Measurement> getMeasurementsNear(const std::string& lat, const std::string& lon);
    std::vector<Measurement> getMeasurementsByDate(const Date& date);
    Sensor getSensorByMeasurement(const Measurement& m);
    Attribut getInfoAttribute(const Measurement& m);
    float computeAverage(const std::vector<Measurement>& data);
    float calculateImprovement(float before, float after);
    float determineDistance(const Sensor& s1, const Sensor& s2);
    std::vector<Measurement> getMeasurementsBySensor(const Sensor& s);
};

#endif // SERVICE_H
