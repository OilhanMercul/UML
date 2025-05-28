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

float Service::getAirQuality(const string& lat, const string& lon, const Date& date) {
    vector<Measurement> allMeasurements = getMeasurementsByDate(date);
    vector<Measurement> closestMeasurements;

    float minDistance = INFINITY;

    for (const Measurement& m : allMeasurements) {
        Sensor sensor = getSensorByMeasurement(m);

        // Calculer la distance entre le capteur et les coordonnées données
        float distance = determineDistance(sensor, Sensor(0, lat, lon)); // Sensor temporaire à la position demandée

        if (distance < minDistance) {
            minDistance = distance;
            closestMeasurements.clear();
            closestMeasurements.push_back(m);
        } else if (abs(distance - minDistance) < 1e-6) {
            closestMeasurements.push_back(m);
        }
    }

    // Grouper les mesures par type de polluant
    map<string, vector<float>> pollutantValues;
    for (const Measurement& m : closestMeasurements) {
        Attribut attr = getInfoAttribute(m);
        string type = attr.getType();
        float value = attr.getValue();

        // On ne garde que les attributs pertinents pour l’indice ATMO
        if (type == "O3" || type == "NO2" || type == "SO2" || type == "PM10") {
            pollutantValues[type].push_back(value);
        }
    }

    // Calculer les moyennes
    map<string, float> averages;
    for (const auto& [type, values] : pollutantValues) {
        float sum = 0;
        for (float v : values) {
            sum += v;
        }
        averages[type] = values.empty() ? 0 : sum / values.size();
    }

    // Calculer l’indice ATMO à partir des moyennes
    return calculateAtmoIndex(averages);
}

int getIndiceForPollutant(float value, const vector<pair<int,int>>& seuils) {
    // seuils = vecteur de paires (min, max) pour chaque niveau de 1 à 10
    for (int i = 0; i < seuils.size(); ++i) {
        if ((i == seuils.size() - 1 && value >= seuils[i].first) || // dernier seuil inclusif min à l'infini
            (value >= seuils[i].first && value <= seuils[i].second)) {
            return i + 1; // indice 1-based
        }
    }
    return 10; // par défaut très mauvais si aucune correspondance
}

int Service::calculateAtmoIndex(const map<string, float>& averages) {
    // Seuils ATMO pour chaque polluant (min, max)
    static const vector<pair<int,int>> seuilsO3 = {
        {0,29}, {30,54}, {55,79}, {80,104}, {105,129}, {130,149}, {150,179}, {180,209}, {210,239}, {240, INT_MAX}
    };
    static const vector<pair<int,int>> seuilsSO2 = {
        {0,39}, {40,79}, {80,119}, {120,159}, {160,199}, {200,249}, {250,299}, {300,399}, {400,499}, {500, INT_MAX}
    };
    static const vector<pair<int,int>> seuilsNO2 = {
        {0,29}, {30,54}, {55,84}, {85,109}, {110,134}, {135,164}, {165,199}, {200,274}, {275,399}, {400, INT_MAX}
    };
    static const vector<pair<int,int>> seuilsPM10 = {
        {0,6}, {7,13}, {14,20}, {21,27}, {28,34}, {35,41}, {42,49}, {50,64}, {65,79}, {80, INT_MAX}
    };

    int indiceMax = 1;

    if (averages.count("O3"))
        indiceMax = max(indiceMax, getIndiceForPollutant(averages.at("O3"), seuilsO3));
    if (averages.count("SO2"))
        indiceMax = max(indiceMax, getIndiceForPollutant(averages.at("SO2"), seuilsSO2));
    if (averages.count("NO2"))
        indiceMax = max(indiceMax, getIndiceForPollutant(averages.at("NO2"), seuilsNO2));
    if (averages.count("PM10"))
        indiceMax = max(indiceMax, getIndiceForPollutant(averages.at("PM10"), seuilsPM10));

    return indiceMax;
}



// À implémenter : Récupérer les mesures proches d’un point (ex. dans un rayon de 1km)
// Ca à l'aire correct
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

//Obtenir les mesures à une date précise
// Ca à l'aire ok
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

//Calculer la moyenne des valeurs de pollution
float Service::computeAverage(const vector<Measurement>& data) {
    if (data.empty()) return 0.0f;

    unordered_map<string, pair<float, int>> attrSums; // key: attribute ID, value: {sum, count}

    for (const auto& m : data) {
        string attrId = m.getAttribut().getId();
        attrSums[attrId].first += m.getValue();
        attrSums[attrId].second += 1;
    }

    float totalAverage = 0.0f;
    for (const auto& [_, sumCount] : attrSums) {
        float avg = sumCount.first / sumCount.second;
        totalAverage += avg;
    }

    return totalAverage / attrSums.size(); // mean of means
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
    vector<Measurement> result;
    for (const auto& m : measurements) {
        if (m.getSensor().getId() == s.getId()) {
            result.push_back(m);
        }
    }
    return result;
}
