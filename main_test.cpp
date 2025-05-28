using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

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

    const auto& sensors = service.getSensors(); // ou service.getSensorList(), selon ta méthode

    assert(!sensors.empty());

    auto it = find_if(sensors.begin(), sensors.end(),
                      [](const Sensor& s) { return s.getId() == "Sensor42"; });

    assert(it != sensors.end());
    assert(abs(it->getLatitude() - 48.858844) < 1e-6);
    assert(abs(it->getLongitude() - 2.294351) < 1e-6);

    cout << "✓ Passed\n" << endl;
}



void testServiceMeasurementParsing_missingValues() {
    cout << "testServiceMeasurementParsing_missingValues" << endl;

    // Prépare un Service avec un fichier csv invalide pour les mesures
    // Par exemple : modifier temporairement le fichier "measurement.csv"
    // ou simuler cela avec un fichier de test (recommandé)

    try {
        Service service("sensors.csv", "bad_measurements.csv", "attributes.csv", ...);

        // Selon ton implémentation :
        // - soit les lignes incorrectes sont ignorées => vérifie leur absence
        // - soit une exception est levée => le test échoue s'il n'y en a pas

        assert(false && "Expected exception not thrown for malformed CSV");
    } catch (const ParseException& e) {
        cout << "✓ Exception capturée : " << e.what() << endl;
    } catch (...) {
        assert(false && "Wrong exception type");
    }

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


void testSensorSimilarity_identicalReadings() {
    cout << "testSensorSimilarity_identicalReadings" << endl;

    Sensor s1("S1", "48.85", "2.29");
    Sensor s2("S2", "48.85", "2.29");
    Service service;

    float sim = service.calculateSensorSimilarity(s1, s2);
    assert(sim == 1.0f);  // Identiques

    cout << "✓ Passed\n" << endl;
}

void testSensorSimilarity_partialOverlap() {
    cout << "testSensorSimilarity_partialOverlap" << endl;

    Sensor s1("S1", "48.85", "2.29");
    Sensor s2("S2", "48.85", "2.30");
    Service service;

    float sim = service.calculateSensorSimilarity(s1, s2);
    assert(sim >= 0.0f && sim <= 1.0f);  // Similitude partielle

    cout << "✓ Passed\n" << endl;
}

void testUserPointIncrement() {
    cout << "testUserPointIncrement" << endl;

    Service service;

    string userId = "U1";
    int before = service.getUserPoints(userId);
    service.awardPointsToUser(userId, 10);
    int after = service.getUserPoints(userId);
    assert(after == before + 10);

    cout << "✓ Passed\n" << endl;
}

void testMaliciousUserExclusion() {
    cout << "testMaliciousUserExclusion" << endl;

    Service service;
    string userId = "MaliciousUser";

    service.flagUserAsMalicious(userId);
    assert(service.isUserExcluded(userId));

    cout << "✓ Passed\n" << endl;
}

void testCleanerEffect_radiusConstraint() {
    cout << "testCleanerEffect_radiusConstraint" << endl;

    Service service;
    AirCleaner cleaner;

    cleaner.setLatitude("48.85");
    cleaner.setLongitude("2.29");
    cleaner.setStart(Date(2023, 4, 1));
    cleaner.setEnd(Date(2023, 4, 30));

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
    testSensorCsvParser_validInput();
    testMeasurementCsvParser_missingValues();

    cout << "=== Tests Air Quality Aggregation ===" << endl;
    testMeanO3Calculation_singleSensor();
    testAirQualityRegion_noSensorsInRange();

    cout << "=== Tests Sensor Similarity ===" << endl;
    testSensorSimilarity_identicalReadings();
    testSensorSimilarity_partialOverlap();

    cout << "=== Tests Incentive Engine ===" << endl;
    testUserPointIncrement();
    testMaliciousUserExclusion();

    cout << "=== Tests Air Cleaner Impact Analysis ===" << endl;
    testCleanerEffect_radiusConstraint();

    return 0;
}
