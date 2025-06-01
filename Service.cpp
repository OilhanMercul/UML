#include "Service.h"

// Constructeur par défaut de la classe Service
Service::Service() {
    // Chargement des capteurs depuis le fichier sensors.csv
    {
        ifstream file("fichiers_csv/sensors.csv"); // Ouverture du fichier en lecture
        if (!file.is_open()) { // Vérifie si le fichier s'est bien ouvert
            cerr << "Erreur lors de l'ouverture du fichier sensors.csv" << endl; // Message d'erreur si échec
            return; // Sort de la fonction constructeur
        }
        string line;
        while (getline(file, line)) { // Lecture ligne par ligne du fichier
            stringstream ss(line); // Conversion de la ligne en flux pour extraction plus facile
            string id, lat, lon;
            getline(ss, id, ';');  // Extraction de l'ID capteur (jusqu'au ;)
            getline(ss, lat, ';'); // Extraction de la latitude
            getline(ss, lon, ';'); // Extraction de la longitude

            int numericId = 0;
            // Extraction de la partie numérique de l'ID (suppose que l'ID contient des chiffres)
            size_t pos = id.find_first_of("0123456789");
            if (pos != string::npos) {
                numericId = stoi(id.substr(pos)); // Conversion de la partie numérique en entier
            }
            Sensor sensor; // Création d'un objet Sensor
            sensor.setId(numericId);      // Assignation de l'ID numérique
            sensor.setLatitude(lat);      // Assignation de la latitude
            sensor.setLongitude(lon);     // Assignation de la longitude
            sensors.push_back(sensor);    // Ajout du capteur à la liste des capteurs
        }
    }

    // Chargement des mesures depuis measurements.csv
    {
        ifstream file("fichiers_csv/measurements.csv"); // Ouverture du fichier
        if (!file.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier measurements.csv" << endl;
            return;
        }
        string line;
        while (getline(file, line)) { // Lecture ligne par ligne
            stringstream ss(line);
            string timestamp, sensorId, attributeId, valueStr;

            getline(ss, timestamp, ';');  // Extraction du timestamp (date)
            getline(ss, sensorId, ';');   // Extraction de l'ID du capteur

            int numericSensorId = 0;
            size_t pos = sensorId.find_first_of("0123456789");
            if (pos != string::npos) {
                numericSensorId = stoi(sensorId.substr(pos)); // Extraction numérique de l'ID capteur
            }
            sensorId = to_string(numericSensorId);

            getline(ss, attributeId, ';'); // Extraction de l'ID de l'attribut
            getline(ss, valueStr, ';');    // Extraction de la valeur mesurée

            float value = stof(valueStr); // Conversion de la valeur en float

            // Recherche du capteur correspondant dans la liste
            auto it = find_if(sensors.begin(), sensors.end(), [&](const Sensor& s){ return s.getId() == stoi(sensorId); });
            Attribut attr;
            attr.setId(attributeId); // Création d'un attribut avec son ID

            if (it != sensors.end()) { // Si le capteur est trouvé
                // Création d'une mesure avec un ID auto-incrémenté, date extraite du timestamp, le capteur, l'attribut et la valeur
                Measurement measurement(
                    measurements.size() + 1,
                    Date(stoi(timestamp.substr(0, 4)), stoi(timestamp.substr(5, 2)), stoi(timestamp.substr(8, 2))),
                    *it,
                    attr,
                    value
                );
                measurements.push_back(measurement); // Ajout de la mesure à la liste
            }
        }
    }

    // Chargement des attributs depuis attributes.csv
    {
        ifstream file("fichiers_csv/attributes.csv");
        if (!file.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier attributes.csv" << endl;
            return;
        }
        string line;
        getline(file, line); // Lecture de l'entête et passage à la ligne suivante
        while (getline(file, line)) { // Lecture ligne par ligne
            stringstream ss(line);
            string attributeId, unit, description;

            getline(ss, attributeId, ';'); // Extraction de l'ID attribut
            getline(ss, unit, ';');        // Extraction de l'unité
            getline(ss, description, ';'); // Extraction de la description

            Attribut attribut;
            attribut.setId(attributeId);
            attribut.setUnit(unit);
            attribut.setDescription(description);

            attributs.push_back(attribut); // Ajout de l'attribut à la liste
        }
    }

    // Association des attributs aux mesures (remplace l'attribut temporaire par celui de la liste)
    for (auto& m : measurements) {
        auto it = find_if(attributs.begin(), attributs.end(), [&](const Attribut& a){ return a.getId() == m.getAttribut().getId(); });
        if (it != attributs.end()) {
            m.setAttribut(*it); // Mise à jour de l'attribut dans la mesure
        }
    }

    // Chargement des nettoyeurs d'air (cleaners.csv)
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
                cleanerId = cleanerId.substr(pos); // Extraction ID numérique
            }
            getline(ss, lat, ';');
            getline(ss, lon, ';');
            getline(ss, start, ';');
            getline(ss, stop, ';');

            // Création d'un AirCleaner avec ID, position et période d'activité
            AirCleaner cleaner(
                stoi(cleanerId),
                lat,
                lon,
                Date(stoi(start.substr(0, 4)), stoi(start.substr(5, 2)), stoi(start.substr(8, 2))),
                Date(stoi(stop.substr(0, 4)), stoi(stop.substr(5, 2)), stoi(stop.substr(8, 2)))
            );
            airCleaners.push_back(cleaner); // Ajout à la liste
        }
    }

    // Chargement des fournisseurs (providers.csv)
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
                providerId = providerId.substr(pos); // Extraction numérique ID fournisseur
            }
            pos = cleanerId.find_first_of("0123456789");
            if (pos != string::npos) {
                cleanerId = cleanerId.substr(pos); // Extraction numérique ID cleaner
            }

            Provider provider;
            provider.setId(stoi(providerId)); // Assignation ID fournisseur

            // Recherche du cleaner correspondant et ajout au fournisseur
            auto itCleaner = find_if(airCleaners.begin(), airCleaners.end(), [&](const AirCleaner& c){ return c.getId() == stoi(cleanerId); });
            if (itCleaner != airCleaners.end()) {
                provider.addAirCleaner(*itCleaner);
            }
            providers.push_back(provider); // Ajout à la liste des fournisseurs
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
                userId = userId.substr(pos); // Extraction ID utilisateur numérique
            }
            pos = sensorId.find_first_of("0123456789");
            if (pos != string::npos) {
                sensorId = sensorId.substr(pos); // Extraction ID capteur numérique
            }

            PrivateIndividual user;
            user.setId(stoi(userId)); // Assignation ID utilisateur

            // Recherche du capteur associé à l'utilisateur et ajout
            auto itSensor = find_if(sensors.begin(), sensors.end(), [&](const Sensor& s){ return s.getId() == stoi(sensorId); });
            if (itSensor != sensors.end()) {
                user.addSensor({*itSensor});
            }
            privateIndividuals.push_back(user); // Ajout utilisateur à la liste
        }
    }
}


// Affiche l'impact des AirCleaners sur la qualité de l'air autour d'eux
pair<float, float> Service::displayImpactCleaners(const AirCleaner& airCleaner) {
    vector<Measurement> beforeData, duringData, afterData;

    // Récupération des infos du nettoyeur : position et période d'activité
    string lat = airCleaner.getLatitude();
    string lon = airCleaner.getLongitude();
    Date start = airCleaner.getStart();
    Date end = airCleaner.getEnd();

    vector<Measurement> nearby;       // Mesures proches du nettoyeur
    set<int> uniqueSensorIds;          // IDs uniques des capteurs autour

    int radius = 50; // Rayon d'influence en km

    // Parcours toutes les mesures pour filtrer celles proches du nettoyeur
    for (const auto& m : measurements) {
        Sensor s = m.getSensor();
        float sensorLat = stof(s.getLatitude());
        float sensorLon = stof(s.getLongitude());
        float centerLat = stof(lat);
        float centerLon = stof(lon);

        if (m.getDate() > end) {
            continue; // Ignore mesures après la fin de période d'activité
        }

        // Calcul de la distance entre capteur et nettoyeur via formule de Haversine
        float dLat = (sensorLat - centerLat) * M_PI / 180.0f;
        float dLon = (sensorLon - centerLon) * M_PI / 180.0f;

        float a = sin(dLat / 2) * sin(dLat / 2) +
                cos(centerLat * M_PI / 180.0f) * cos(sensorLat * M_PI / 180.0f) *
                sin(dLon / 2) * sin(dLon / 2);
        float c = 2 * atan2(sqrt(a), sqrt(1 - a));
        float distance = 6371.0f * c; // Distance en km

        // Si mesure dans le rayon d'influence, on la garde
        if (distance <= radius) {
            nearby.push_back(m);
            uniqueSensorIds.insert(s.getId());
        }
    }

    
    // Classe les mesures autour du nettoyeur avant ou pendant sa période d’activité
    for (const auto& m : nearby) {
        Date d = m.getDate();
        if (d < start) {
            beforeData.push_back(m); // Mesures avant activation
        } else {
            duringData.push_back(m); // Mesures pendant activation
        }
    }

    // Si pas de données avant ou pendant, on affiche un message d'erreur et on retourne 0
    if (beforeData.empty() && duringData.empty()) {
        cerr << "Aucune mesure trouvée dans la zone spécifiée." << endl;
        return {0.0f, 0.0f};
    }

    // Calcul des indices atmosphériques moyens avant et pendant
    float avgBefore = computeAtmoIndex(beforeData);
    float avgDuring = computeAtmoIndex(duringData);

    // Calcul du pourcentage d'amélioration
    float improvement = calculateImprovement(avgBefore, avgDuring);

    // Retourne le rayon (en km) et le % d'amélioration de la qualité de l'air
    return {static_cast<float>(radius), improvement};
}

// Obtient l'indice de qualité de l'air pour une position, date et rayon donnés
float Service::getAirQuality(const string& lat, const string& lon, const Date& date, const int radius) {
    vector<Measurement> all = getMeasurementsByDate(date); // Mesures du jour
    vector<Measurement> valid; // Mesures valides pour la position

    // Filtre mesures avec même latitude et longitude exacte
    for (const auto& m : all) {
        Sensor s = m.getSensor();
        if (s.getLatitude() == lat && s.getLongitude() == lon) {
            valid.push_back(m);
        }
    }
    
    // Si aucune mesure directe trouvée, cherche dans le rayon donné autour
    if (valid.empty()) {
        for (const auto& m : all) {
            Sensor s = m.getSensor();
            float sensorLat = stof(s.getLatitude());
            float sensorLon = stof(s.getLongitude());
            float centerLat = stof(lat);
            float centerLon = stof(lon);

            // Calcul de la distance (formule Haversine)
            float dLat = (sensorLat - centerLat) * M_PI / 180.0f;
            float dLon = (sensorLon - centerLon) * M_PI / 180.0f;

            float a = sin(dLat / 2) * sin(dLat / 2) +
                  cos(centerLat * M_PI / 180.0f) * cos(sensorLat * M_PI / 180.0f) *
                  sin(dLon / 2) * sin(dLon / 2);
            float c = 2 * atan2(sqrt(a), sqrt(1 - a));
            float distance = 6371.0f * c; // Distance en km

            // Ajoute si mesure dans le rayon
            if (distance <= radius) {
                valid.push_back(m);
            }
        }

        // Si toujours rien dans le rayon, message d'erreur et retour 0
        if (valid.empty()) {
            cerr << "Aucune mesure trouvée dans le rayon spécifié." << endl;
            return 0.0f;
        }
    }

    // Calcule et retourne l'indice atmosphérique moyen pour les mesures valides
    float IndexAtmo = computeAtmoIndex(valid);
    return IndexAtmo;
}

// À supprimer, pas utilisé dans le projet
vector<Measurement> Service::getMeasurementsNear(const string& lat, const string& lon) {
    vector<Measurement> result;
    float centerLat = stof(lat);
    float centerLon = stof(lon);

    // Parcourt toutes les mesures pour trouver celles dans 1 km autour de lat/lon
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

// Retourne toutes les mesures prises à une date donnée
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

// Retourne le capteur lié à une mesure donnée
Sensor Service::getSensorByMeasurement(const Measurement& m) {
    return m.getSensor();
}

// Retourne l'attribut lié à une mesure donnée
Attribut Service::getInfoAttribute(const Measurement& m) {
    return m.getAttribut();
}

// Calcule la moyenne des indices de pollution à partir d'un ensemble de mesures
float Service::computeAtmoIndex(const vector<Measurement>& data) {
    if (data.empty()) return 0; // Pas de données => 0

    map<string, float> sumByAttr;    // Somme des valeurs par attribut
    map<string, int> countByAttr;    // Nombre de mesures par attribut

    // Somme des valeurs mesurées pour chaque attribut
    for (const auto& m : data) {
        string attrId = m.getAttribut().getId();
        sumByAttr[attrId] += m.getValue();
        countByAttr[attrId]++;
    }

    map<string, float> sumIndexByAttr;   // Somme des indices ATMO par attribut
    map<string, int> countIndexByAttr;   // Nombre d'indices calculés par attribut

    // Pour chaque mesure, calcule son indice ATMO et le somme (ignore attributs inconnus)
    for (const auto& m : data) {
        string attrId = m.getAttribut().getId();
        int index = getAtmoIndex(attrId, m.getValue());
        if (index > 0) {
            sumIndexByAttr[attrId] += index;
            countIndexByAttr[attrId]++;
        }
    }

    float maxAvgIndex = 0.0f;
    // Cherche la moyenne maximale parmi tous les attributs (indice le plus fort)
    for (const auto& [attr, sum] : sumIndexByAttr) {
        float avgIndex = sum / countIndexByAttr[attr];
        if (avgIndex > maxAvgIndex) {
            maxAvgIndex = avgIndex;
        }
    }
    return maxAvgIndex; // Retourne la valeur maximale moyenne
}

// Retourne l'indice ATMO selon l'attribut et la valeur mesurée (barèmes standards)
int Service::getAtmoIndex(const string& attributeId, float value) {
    if (attributeId == "O3") {
        if (value <= 29) return 1;
        else if (value <= 54) return 2;
        else if (value <= 79) return 3;
        else if (value <= 104) return 4;
        else if (value <= 129) return 5;
        else if (value <= 149) return 6;
        else if (value <= 179) return 7;
        else if (value <= 209) return 8;
        else if (value <= 239) return 9;
        else return 10;
    } else if (attributeId == "NO2") {
        if (value <= 29) return 1;
        else if (value <= 54) return 2;
        else if (value <= 84) return 3;
        else if (value <= 109) return 4;
        else if (value <= 134) return 5;
        else if (value <= 159) return 6;
        else if (value <= 199) return 7;
        else if (value <= 274) return 8;
        else if (value <= 399) return 9;
        else return 10;
    } else if (attributeId == "SO2") {
        if (value <= 39) return 1;
        else if (value <= 79) return 2;
        else if (value <= 119) return 3;
        else if (value <= 159) return 4;
        else if (value <= 199) return 5;
        else if (value <= 249) return 6;
        else if (value <= 299) return 7;
        else if (value <= 399) return 8;
        else if (value <= 499) return 9;
        else return 10;
    } else if (attributeId == "PM10") {
        if (value <= 6) return 1;
        else if (value <= 13) return 2;
        else if (value <= 20) return 3;
        else if (value <= 27) return 4;
        else if (value <= 34) return 5;
        else if (value <= 41) return 6;
        else if (value <= 49) return 7;
        else if (value <= 64) return 8;
        else if (value <= 79) return 9;
        else return 10;
    }

    // Pour tout autre attribut non reconnu, retourne 0 (pas d'indice)
    return 0;
}

// Calcule le pourcentage d'amélioration entre avant et après
float Service::calculateImprovement(float before, float after) {
    if (before == 0) return 0.0f; // Evite division par zéro
    return ((before - after) / before) * 100.0f;
}
