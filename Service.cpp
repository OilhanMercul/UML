#include "Service.h"
#include <cmath>

Service::Service() {
    // Constructor body if needed
}

// Returns (radius, improvement)
std::pair<float, float> Service::displayImpactCleaners(const AirCleaner& airCleaner) {
    std::vector<Measurement> beforeData, duringData, afterData;

    std::string lat = airCleaner.getLatitude();
    std::string lon = airCleaner.getLongitude();
    Date start = airCleaner.getStart();
    Date end = airCleaner.getEnd();

    std::vector<Measurement> nearby = getMeasurementsNear(lat, lon);

    for (const auto& m : nearby) {
        Date d = m.getDate();
        if (d.year < start.year || (d.year == start.year && d.month < start.month) ||
            (d.year == start.year && d.month == start.month && d.day < start.day)) {
            beforeData.push_back(m);
        } else if (d.year > end.year || (d.year == end.year && d.month > end.month) ||
                   (d.year == end.year && d.month == end.month && d.day > end.day)) {
            afterData.push_back(m);
        } else {
            duringData.push_back(m);
        }
    }

    float avgBefore = computeAverage(beforeData);
    float avgDuring = computeAverage(duringData);
    float avgAfter = computeAverage(afterData);
    float improvement = calculateImprovement(avgBefore, avgAfter);

    float radius = 0.0f;

    for (const auto& m : afterData) {
        Sensor s = m.getSensor();
        std::vector<Measurement> otherMs = getMeasurementsBySensor(s);

        for (const auto& other : otherMs) {
            float diff = std::fabs(m.getValue() - other.getValue());
            if (diff <= 0.1f * other.getValue()) {
                radius = determineDistance(m.getSensor(), other.getSensor());
            }
        }
    }

    return {radius, improvement};
}

// Returns (airQualityIndex, meanIndex)
std::pair<float, float> Service::getAirQuality(const std::string& lat, const std::string& lon, const Date& date) {
    std::vector<Measurement> all = getMeasurementsByDate(date);
    std::vector<Measurement> valid;
    std::vector<Attribut> attribList;

    for (const auto& m : all) {
        Sensor s = m.getSensor();
        if (s.getLatitude() == lat && s.getLongitude() == lon) {
            valid.push_back(m);
            attribList.push_back(getInfoAttribute(m));
        }
    }

    float airQualityIndex = computeAverage(valid);
    float meanIndex = airQualityIndex; // Assuming same for simplicity

    return {airQualityIndex, meanIndex};
}

// Dummy implementations of helpers (to be implemented fully)
std::vector<Measurement> Service::getMeasurementsNear(const std::string& lat, const std::string& lon) {
    // TODO: filter measurements by coordinates near lat/lon
    return measurements;
}

std::vector<Measurement> Service::getMeasurementsByDate(const Date& date) {
    std::vector<Measurement> result;
    for (const auto& m : measurements) {
        if (m.getDate().year == date.year &&
            m.getDate().month == date.month &&
            m.getDate().day == date.day) {
            result.push_back(m);
        }
    }
    return result;
}

Sensor Service::getSensorByMeasurement(const Measurement& m) {
    return m.getSensor();
}

Attribut Service::getInfoAttribute(const Measurement& m) {
    return m.getAttribut();
}

float Service::computeAverage(const std::vector<Measurement>& data) {
    if (data.empty()) return 0.0f;
    float sum = 0.0f;
    for (const auto& m : data) {
        sum += m.getValue();
    }
    return sum / data.size();
}

float Service::calculateImprovement(float before, float after) {
    if (before == 0) return 0.0f;
    return ((before - after) / before) * 100.0f;
}

float Service::determineDistance(const Sensor& s1, const Sensor& s2) {
    // TODO: implement proper distance computation if coordinates are numerical
    return 0.0f;
}

std::vector<Measurement> Service::getMeasurementsBySensor(const Sensor& s) {
    std::vector<Measurement> result;
    for (const auto& m : measurements) {
        if (m.getSensor().getId() == s.getId()) {
            result.push_back(m);
        }
    }
    return result;
}
