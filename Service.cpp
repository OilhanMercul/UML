#include "Service.h"
#include <cmath>
#include <corecrt_math_defines.h>
using namespace std;


// Constructeur par défaut
Service::Service() {
    
}

//Analyser l'impact d’un cleaner
pair<float, float> Service::displayImpactCleaners(const AirCleaner& airCleaner) {
    // Vecteur avec les mesures avant, pendant et après l’activité du purificateur
    vector<Measurement> beforeData, duringData, afterData;

    //Données du cleaner
    string lat = airCleaner.getLatitude();
    string lon = airCleaner.getLongitude();
    Date start = airCleaner.getStart();
    Date end = airCleaner.getEnd();

    //Mesures autour du cleaner (à implémenter)
    vector<Measurement> nearby = getMeasurementsNear(lat, lon);

    // Trier les mesures par période
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

    //Calcul des moyennes pour chaque période
    float avgBefore = computeAverage(beforeData);
    float avgDuring = computeAverage(duringData);
    float avgAfter = computeAverage(afterData);

    // Calcul du % d'd'improvement
    float improvement = calculateImprovement(avgBefore, avgAfter);

    //Calcul du rayon
    float radius = 0.0f;

    for (const auto& m : afterData) {
        Sensor s = m.getSensor();
        vector<Measurement> otherMs = getMeasurementsBySensor(s);

        for (const auto& other : otherMs) {
            float diff = std::fabs(m.getValue() - other.getValue());
            if (diff <= 0.1f * other.getValue()) {
                // Influence détectée : calculer la distance (TODO: améliorer ce calcul)
                radius = determineDistance(m.getSensor(), other.getSensor());
            }
        }
    }
    return {radius, improvement};
}

//Analyser la qualité de l’air à un endroit donné et un jour précis
pair<float, float> Service::getAirQuality(const string& lat, const string& lon, const Date& date) {
    vector<Measurement> all = getMeasurementsByDate(date);
    vector<Measurement> valid;
    vector<Attribut> attribList;

    for (const auto& m : all) {
        Sensor s = m.getSensor();
        if (s.getLatitude() == lat && s.getLongitude() == lon) {
            valid.push_back(m);
            attribList.push_back(getInfoAttribute(m));
        }
    }

    float airQualityIndex = computeAverage(valid);
    float meanIndex = airQualityIndex;

    return {airQualityIndex, meanIndex};
}


// À implémenter : Récupérer les mesures proches d’un point (ex. dans un rayon de 1km)
vector<Measurement> Service::getMeasurementsNear(const string& lat, const string& lon) {
    vector<Measurement> result;
    float centerLat = stof(lat);
    float centerLon = stof(lon);

    for (const auto& m : measurements) {
        Sensor s = m.getSensor();
        float sensorLat = stof(s.getLatitude());
        float sensorLon = stof(s.getLongitude());

        float dLat = (sensorLat - centerLat) * M_PI / 180.0f;
        float dLon = (sensorLon - centerLon) * M_PI / 180.0f;

        float a = sin(dLat / 2) * sin(dLat / 2) +
                  cos(centerLat * M_PI / 180.0f) * cos(sensorLat * M_PI / 180.0f) *
                  sin(dLon / 2) * sin(dLon / 2);
        float c = 2 * atan2(sqrt(a), sqrt(1 - a));
        float distance = 6371.0f * c; // Earth radius in km

        if (distance <= 1.0f) {
            result.push_back(m);
        }
    }
    return result;
}

//Obtenir les mesures à une date précise
vector<Measurement> Service::getMeasurementsByDate(const Date& date) {
    vector<Measurement> result;
    for (const auto& m : measurements) {
        if (m.getDate().year == date.year &&
            m.getDate().month == date.month &&
            m.getDate().day == date.day) {
            result.push_back(m);
        }
    }
    return result;
}

//Renvoyer le capteur associe a une mesure
Sensor Service::getSensorByMeasurement(const Measurement& m) {
    return m.getSensor();
}

//Recuperer l’attribut mesure
Attribut Service::getInfoAttribute(const Measurement& m) {
    return m.getAttribut();
}

//Calculer la moyenne des valeurs de pollution
float Service::computeAverage(const vector<Measurement>& data) {
    if (data.empty()) return 0.0f;
    float sum = 0.0f;
    for (const auto& m : data) {
        sum += m.getValue();
    }
    return sum / data.size();
}

//Calculer le % d’amélioration
float Service::calculateImprovement(float before, float after) {
    if (before == 0) return 0.0f;
    return ((before - after) / before) * 100.0f;
}

//À implémenter correctement : Calculer la distance entre 2 capteurs
float Service::determineDistance(const Sensor& s1, const Sensor& s2) {
    const float R = 6371.0f; // Radius of Earth in kilometers
    float lat1 = stof(s1.getLatitude()) * M_PI / 180.0f;
    float lon1 = stof(s1.getLongitude()) * M_PI / 180.0f;
    float lat2 = stof(s2.getLatitude()) * M_PI / 180.0f;
    float lon2 = stof(s2.getLongitude()) * M_PI / 180.0f;

    float dlat = lat2 - lat1;
    float dlon = lon2 - lon1;

    float a = sin(dlat / 2) * sin(dlat / 2) +
              cos(lat1) * cos(lat2) *
              sin(dlon / 2) * sin(dlon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

//Retourner les mesures d'un capteur
vector<Measurement> Service::getMeasurementsBySensor(const Sensor& s) {
    std::vector<Measurement> result;
    for (const auto& m : measurements) {
        if (m.getSensor().getId() == s.getId()) {
            result.push_back(m);
        }
    }
    return result;
}
