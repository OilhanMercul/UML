#include "Service.h"
using namespace std;


// Constructor
Service::Service() {
}


// Getters
vector<Provider>& Service::getProviders() const {
    return providers;
}

vector<PrivateIndividual>& Service::getPrivateIndividuals() const {
    return privateIndividuals;
}

vector<AirCleaner>& Service::getAirCleaners() const {
    return airCleaners;
}

vector<Sensor>& Service::getSensors() const {
    return sensors;
}

vector<Measurement>& Service::getMeasurements() const {
    return measurements;
}

vector<Attribut>& Service::getAttributs() const {
    return attributs;
}

// Setters
void Service::setProviders(const std::vector<Provider>& providers) {
    this->providers = providers;
}

void Service::setPrivateIndividuals(const std::vector<PrivateIndividual>& privateIndividuals) {
    this->privateIndividuals = privateIndividuals;
}

void Service::setAirCleaners(const std::vector<AirCleaner>& airCleaners) {
    this->airCleaners = airCleaners;
}

void Service::setSensors(const std::vector<Sensor>& sensors) {
    this->sensors = sensors;
}

void Service::setMeasurements(const std::vector<Measurement>& measurements) {
    this->measurements = measurements;
}

void Service::setAttributs(const std::vector<Attribut>& attributs) {
    this->attributs = attributs;
}


// Account Management
User Service::createAccount(int id, const string& password, const string& email) {
    return User();
}

User Service::connect(int id, const string& password, const string& email) {
    return User();
}

bool Service::disconnect(const User& user) {
    return true;
}

// Data Loading
bool Service::loadFile() {
    return true;
}

// Cleaners & Sensors
pair<float, float> Service::displayImpactCleaners(const AirCleaner& airCleaner) {
    return {0.0f, 0.0f}; // Placeholder for radius and improvement
}

float Service::displayAirQuality(double latitude, double longitude, const string& date) {
    return 0.0f;
}

bool Service::analyseDataIndividual(const PrivateIndividual& individual) {
    return true;
}

vector<pair<Sensor, int>> Service::compareSensor(const Sensor& sensor, const string& start, const string& end) {
    return {};
}

// Statistical Measures
float Service::displayMeansAirQuality(double lat, double lon, const string& start, const string& end) {
    return 0.0f;
}

pair<float, float> Service::displayMinMaxAirQuality(double lat, double lon, const string& start, const string& end) {
    return {0.0f, 0.0f}; // min, max
}

vector<Measurement> Service::displayEvolutionAirQuality(double lat, double lon, const string& start, const string& end) {
    return {};
}

// Data Contribution & Consultation
bool Service::contributeData(const string& filePath) {
    return true;
}

vector<Measurement> Service::consultData(const User& user) {
    return {};
}

vector<PrivateIndividual> Service::consultExcluded() {
    return {};
}


