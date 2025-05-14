/*************************************************************************
                           Service.h  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Service> (fichier Service.h) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>
#include <map>
#include "Provider.h"
#include "PrivateIndividual.h"
#include "AirCleaner.h"
#include "Sensor.h"
#include "Measurement.h"
#include "Attribut.h"
#include "User.h"

using namespace std;

class Service {
private:
    vector<Provider> providers;
    vector<PrivateIndividual> privateIndividuals;
    vector<AirCleaner> airCleaners;
    vector<Sensor> sensors;
    vector<Measurement> measurements;
    vector<Attribut> attributs;

public:
    // Constructor
    Service();

    // Account Management
    User createAccount(int id, const string& password, const string& email);
    User connect(int id, const string& password, const string& email);
    bool disconnect(const User& user);

    // Data Loading
    bool loadFile();

    // Cleaners & Sensors
    pair<float, float> displayImpactCleaners(const AirCleaner& airCleaner); // radius, improvement
    float displayAirQuality(double latitude, double longitude, const string& date);
    bool analyseDataIndividual(const PrivateIndividual& individual);
    vector<pair<Sensor, int>> compareSensor(const Sensor& sensor, const string& start, const string& end);

    // Statistical Measures
    float displayMeansAirQuality(double lat, double lon, const string& start, const string& end);
    pair<float, float> displayMinMaxAirQuality(double lat, double lon, const string& start, const string& end);
    vector<Measurement> displayEvolutionAirQuality(double lat, double lon, const string& start, const string& end);

    // Data Contribution & Consultation
    bool contributeData(const string& filePath);
    vector<Measurement> consultData(const User& user);
    vector<PrivateIndividual> consultExcluded();
};

#endif // SERVICE_H