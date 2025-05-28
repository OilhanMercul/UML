#include "Service.h"

// Constructeur par défaut
Service::Service() {
    // Chargement des capteurs (sensor.csv)
    {
        ifstream file("fichiers_csv/sensors.csv");
        if (!file.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier sensors.csv" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, lat, lon;
            getline(ss, id, ';');
            getline(ss, lat, ';');
            getline(ss, lon, ';');
            int numericId = 0;
            size_t pos = id.find_first_of("0123456789");
            if (pos != string::npos) {
                numericId = stoi(id.substr(pos));
            }
            Sensor sensor;
            sensor.setId(numericId);
            sensor.setLatitude(lat);
            sensor.setLongitude(lon);
            sensors.push_back(sensor);
        }
    }

    // Chargement des mesures (measurements.csv)
    {
        ifstream file("fichiers_csv/measurements.csv");
        if (!file.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier measurements.csv" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string timestamp, sensorId, attributeId, valueStr;
            getline(ss, timestamp, ';');
            getline(ss, sensorId, ';');
            int numericSensorId = 0;
            size_t pos = sensorId.find_first_of("0123456789");
            if (pos != string::npos) {
                numericSensorId = stoi(sensorId.substr(pos));
            }
            sensorId = to_string(numericSensorId);

            getline(ss, attributeId, ';');
            getline(ss, valueStr, ';');
            float value = stof(valueStr);

            auto it = find_if(sensors.begin(), sensors.end(), [&](const Sensor& s){ return s.getId() == stoi(sensorId); });
            Attribut attr;
            attr.setId(attributeId);
            if (it != sensors.end()) {
                Measurement measurement(
                    measurements.size() + 1,
                    Date(stoi(timestamp.substr(0, 4)), stoi(timestamp.substr(5, 2)), stoi(timestamp.substr(8, 2))),
                    *it,
                    attr,
                    value
                );
                measurements.push_back(measurement);
            }
        }
    }

    // Chargement des attributs (attributes.csv)
    {
        ifstream file("fichiers_csv/attributes.csv");
        if (!file.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier attributes.csv" << endl;
            return;
        }
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string attributeId, unit, description;
            getline(ss, attributeId, ';');
            getline(ss, unit, ';');
            getline(ss, description, ';');
            Attribut attribut;
            attribut.setId(attributeId);
            attribut.setUnit(unit);
            attribut.setDescription(description);
            attributs.push_back(attribut);
        }
    }

    for (auto& m : measurements) {
        auto it = find_if(attributs.begin(), attributs.end(), [&](const Attribut& a){ return a.getId() == m.getAttribut().getId(); });
        if (it != attributs.end()) {
            m.setAttribut(*it);
        }
    }

    // Chargement des cleaners (cleaners.csv)
    {
        ifstream file("fichiers_csv/cleaners.csv");
        if (!file.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier cleaners.csv" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string cleanerId, lat, lon, start, stop;
            getline(ss, cleanerId, ';');
            size_t pos = cleanerId.find_first_of("0123456789");
            if (pos != string::npos) {
                cleanerId = cleanerId.substr(pos);
            }
            getline(ss, lat, ';');
            getline(ss, lon, ';');
            getline(ss, start, ';');
            getline(ss, stop, ';');
            AirCleaner cleaner(
                stoi(cleanerId),
                lat,
                lon,
                Date(stoi(start.substr(0, 4)), stoi(start.substr(5, 2)), stoi(start.substr(8, 2))),
                Date(stoi(stop.substr(0, 4)), stoi(stop.substr(5, 2)), stoi(stop.substr(8, 2)))
            );
            airCleaners.push_back(cleaner);
        }
    }

    // Chargement des providers (providers.csv)
    {
        ifstream file("fichiers_csv/providers.csv");
        if (!file.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier providers.csv" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string providerId, cleanerId;
            getline(ss, providerId, ';');
            getline(ss, cleanerId, ';');
            size_t pos = providerId.find_first_of("0123456789");
            if (pos != string::npos) {
                providerId = providerId.substr(pos);
            }
            pos = cleanerId.find_first_of("0123456789");
            if (pos != string::npos) {
                cleanerId = cleanerId.substr(pos);
            }
            Provider provider;
            provider.setId(stoi(providerId));
            auto itCleaner = find_if(airCleaners.begin(), airCleaners.end(), [&](const AirCleaner& c){ return c.getId() == stoi(cleanerId); });
            if (itCleaner != airCleaners.end()) {
                provider.addAirCleaner(*itCleaner);
            }
            providers.push_back(provider);
        }
    }

    // Chargement des utilisateurs privés (users.csv)
    {
        ifstream file("fichiers_csv/users.csv");
        if (!file.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier users.csv" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string userId, sensorId;
            getline(ss, userId, ';');
            getline(ss, sensorId, ';');
            size_t pos = userId.find_first_of("0123456789");
            if (pos != string::npos) {
                userId = userId.substr(pos);
            }
            pos = sensorId.find_first_of("0123456789");
            if (pos != string::npos) {
                sensorId = sensorId.substr(pos);
            }
            PrivateIndividual user;
            user.setId(stoi(userId));
            auto itSensor = find_if(sensors.begin(), sensors.end(), [&](const Sensor& s){ return s.getId() == stoi(sensorId); });
            if (itSensor != sensors.end()) {
                user.addSensor({*itSensor});
            }
            privateIndividuals.push_back(user);
        }
    }
}

pair<float, float> Service::displayImpactCleaners(const AirCleaner& airCleaner) {
    vector<Measurement> beforeData, duringData, afterData;
    string lat = airCleaner.getLatitude();
    string lon = airCleaner.getLongitude();
    Date start = airCleaner.getStart();
    Date end = airCleaner.getEnd();

    vector<Measurement> nearby = getMeasurementsNear(lat, lon);

    for (const auto& m : nearby) {
        Date d = m.getDate();
        if (d < start) {
            beforeData.push_back(m);
        } else if (d > end) {
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
        vector<Measurement> otherMs = getMeasurementsBySensor(s);
        for (const auto& other : otherMs) {
            float diff = std::fabs(m.getValue() - other.getValue());
            if (diff <= 0.1f * other.getValue()) {
                radius = determineDistance(m.getSensor(), other.getSensor());
            }
        }
    }

    return {radius, improvement};
}

pair<float, float> Service::getAirQuality(const string& lat, const string& lon, const Date& date) {
    vector<Measurement> all = getMeasurementsByDate(date);
    vector<Measurement> valid;
    for (const auto& m : all) {
        Sensor s = m.getSensor();
        if (s.getLatitude() == lat && s.getLongitude() == lon) {
            valid.push_back(m);
        }
    }
    float airQualityIndex = computeAverage(valid);
    float meanIndex = airQualityIndex;
    return {airQualityIndex, meanIndex};
}

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
        float distance = 6371.0f * c;

        if (distance <= 1.0f) {
            result.push_back(m);
        }
    }
    return result;
}

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

Sensor Service::getSensorByMeasurement(const Measurement& m) {
    return m.getSensor();
}

Attribut Service::getInfoAttribute(const Measurement& m) {
    return m.getAttribut();
}

float Service::computeAverage(const vector<Measurement>& data) {
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
    const float R = 6371.0f;
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

vector<Measurement> Service::getMeasurementsBySensor(const Sensor& s) {
    std::vector<Measurement> result;
    for (const auto& m : measurements) {
        if (m.getSensor().getId() == s.getId()) {
            result.push_back(m);
        }
    }
    return result;
}
