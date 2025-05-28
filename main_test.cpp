using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>
#include <cassert>

#include "Provider.h"
#include "AirCleaner.h"
#include "PrivateIndividual.h"
#include "Measurement.h"
#include "Attribut.h"
#include "Service.h"
#include "Sensor.h"

using namespace std;

void testServiceSensorParsing_validInput() {
    cout << "testServiceSensorParsing_validInput" << endl;

    Service service;

    const auto& sensors = service.getSensors(); // À définir dans Service si ce n’est pas encore fait

    assert(!sensors.empty());

    auto it = find_if(sensors.begin(), sensors.end(),
                      [](const Sensor& s) { return s.getId() == 42; });

    assert(it != sensors.end());
    assert(it->getLatitude() == "48.858844");
    assert(it->getLongitude() == "2.294351");

    cout << "✓ Passed\n" << endl;
}

void testMeanO3Calculation_singleSensor() {
    cout << "testMeanO3Calculation_singleSensor" << endl;

    Service service;
    Date d(2023, 5, 1);

    auto result = service.getAirQuality("48.858844", "2.294351", d);
    assert(result.first > 0);  // Valeur moyenne mesurée

    cout << "✓ Passed\n" << endl;
}

void testAirQualityRegion_noSensorsInRange() {
    cout << "testAirQualityRegion_noSensorsInRange" << endl;

    Service service; // Charge les données
    Date date(2023, 1, 1);

    // Un point éloigné où aucun capteur n'est proche
    auto [airQuality, mean] = service.getAirQuality("0.0", "0.0", date);

    // Si aucun capteur proche, la qualité doit être 0 (ou une valeur par défaut que tu définis)
    assert(airQuality == 0.0f);
    assert(mean == 0.0f);

    cout << "✓ Passed\n" << endl;
}

void testCleanerEffect_radiusConstraint() {
    cout << "testCleanerEffect_radiusConstraint" << endl;

    Service service;
    AirCleaner cleaner(288, "48.85", "2.29", Date(2023, 4, 1), Date(2023, 4, 30));

    auto result = service.displayImpactCleaners(cleaner);
    float radius = result.first;
    float improvement = result.second;

    assert(radius >= 0.0f);
    assert(improvement >= -100.0f && improvement <= 100.0f);
    
    cout << "✓ Passed\n" << endl;
}


int main() {
    cout << "=== Tests unitaires ===\n\n" << endl;

    cout << "=== Tests Data Parsing ===" << endl;
    testServiceSensorParsing_validInput();

    cout << "=== Tests Air Quality Aggregation ===" << endl;
    testMeanO3Calculation_singleSensor();
    testAirQualityRegion_noSensorsInRange();

    cout << "=== Tests Air Cleaner Impact Analysis ===" << endl;
    testCleanerEffect_radiusConstraint();

    return 0;
}
