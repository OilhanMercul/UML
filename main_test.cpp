#include <iostream>
#include "Sensor.h"
#include "Measurement.h"
using namespace std;

void testSensorCsvParser_validInput() {
    cout << "testSensorCsvParser_validInput" << endl;

}

void testMeasurementCsvParser_missingValues() {
    cout << "testMeasurementCsvParser_missingValues" << endl;

}

void testMeanO3Calculation_singleSensor(){
    cout << "testMeanO3Calculation_singleSensor" << endl;

}

void testAirQualityRegion_noSensorsInRange(){
    cout << "testAirQualityRegion_noSensorsInRange" << endl;

}

void testSensorSimilarity_identicalReadings(){
    cout << "testSensorSimilarity_identicalReadings" << endl;

}

void testSensorSimilarity_partialOverlap(){
    cout << "testSensorSimilarity_partialOverlap" << endl;

}

void testUserPointIncrement(){
    cout << "testUserPointIncrement" << endl;

}

void testMaliciousUserExclusion(){
    cout << "testMaliciousUserExclusion" << endl;

}

void testCleanerEffect_radiusConstraint(){
    cout << "testCleanerEffect_radiusConstraint" << endl;

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
