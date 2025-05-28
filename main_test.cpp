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

    const auto& sensors = service.getSensors(); 

    assert(!sensors.empty());

    auto it = find_if(sensors.begin(), sensors.end(),
                      [](const Sensor& s) { return s.getId() == 42; });

    assert(it != sensors.end());
    assert(it->getLatitude() == "45.6");
    assert(it->getLongitude() == "0.4");

    cout << "✓ Passed\n" << endl;
}

void testMeanO3Calculation_singleSensor() {
    cout << "testMeanO3Calculation_singleSensor" << endl;

    Service service;
    Date d(2019, 5, 1);

    float result = service.getAirQuality("45.6", "0.4", d);
    cout << result << endl;
    assert(result == 8);  

    cout << "✓ Passed\n" << endl;
}

void testAirQualityRegion_noSensorsInRange() {
    cout << "testAirQualityRegion_noSensorsInRange" << endl;

    Service service; // Charge les données
    Date date(2023, 1, 1);

    // Un point éloigné où aucun capteur n'est proche
    float airQuality = service.getAirQuality("0.0", "0.0", date);

    assert(airQuality == 0.0f);

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
