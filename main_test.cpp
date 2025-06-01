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

void testAirQuality() {
    cout << "testAirQuality" << endl;

    Service service;
    Date d(2019, 5, 1);

    /* 
    Sensor : Sensor47;45.6;3.9;

    Measurements : 
    2019-05-01 12:00:00;Sensor47;O3;45.08;
    2019-05-01 12:00:00;Sensor47;NO2;52.36;
    2019-05-01 12:00:00;Sensor47;SO2;56.65;
    2019-05-01 12:00:00;Sensor47;PM10;45.09;

    atmo à 7

    Sensor : Sensor37;45.2;3.9;

    2019-01-20 12:00:00;Sensor37;O3;66.2;
    2019-01-20 12:00:00;Sensor37;NO2;48.78;
    2019-01-20 12:00:00;Sensor37;SO2;44.26;
    2019-01-20 12:00:00;Sensor37;PM10;52.77;

    atmo à 8
    */

    float result = service.getAirQuality("45.2", "4.0", d);
    cout << result << endl;
    assert(result == 8.0f);

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

void testCleanerEffect_radiusConstraint(){
    cout << "testCleanerEffect_highImprovement" << endl;

    Service service;
    // Cleaner1 is expected to have a high improvement (>80%)
    AirCleaner c1(1, "46.666667", "3.666667", Date(2019, 2, 1), Date(2019, 3, 1));
    vector<AirCleaner> cleaners = service.getAirCleaners();
    for (const auto& cleaner : cleaners) {
        if (cleaner.getId() == 1) {
            c1 = cleaner;
            break;
        }
    }
    auto result = service.displayImpactCleaners(c1);
    float improvement = result.second;
    cout << "Improvement for Cleaner1: " << improvement << "%" << endl;
    assert(improvement > 80.0f);
    cout << "✓ Passed\n" << endl;

    cout << "testCleanerEffect_lowImprovement" << endl;

    AirCleaner c0(0, "45.333333", "1.333333", Date(2019, 2, 1), Date(2019, 3, 1));
    for (const auto& cleaner : cleaners) {
        if (cleaner.getId() == 0) {
            c0 = cleaner;
            break;
        }
    }
    result = service.displayImpactCleaners(c0);
    improvement = result.second;
    cout << "Improvement for Cleaner0: " << improvement << "%" << endl;
    assert(improvement < 5.0f);
    cout << "✓ Passed\n" << endl;
}


int main() {
    cout << "=== Tests unitaires ===\n\n" << endl;

    cout << "=== Tests Data Parsing ===" << endl;
    testServiceSensorParsing_validInput();

    cout << "=== Tests Air Quality Aggregation ===" << endl;
    testAirQuality();
    testAirQualityRegion_noSensorsInRange();

    cout << "=== Tests Air Cleaner Impact Analysis ===" << endl;
    testCleanerEffect_radiusConstraint();

    return 0;
}
