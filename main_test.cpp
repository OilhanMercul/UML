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

// Teste que les capteurs sont bien parsés depuis les fichiers
void testServiceSensorParsing_validInput() {
    cout << "[TEST] Vérification du parsing des capteurs depuis les fichiers..." << endl;

    Service service;

    const auto& sensors = service.getSensors(); 

    // Vérifie qu'on a au moins un capteur
    assert(!sensors.empty());

    // Recherche un capteur avec l'ID 42
    auto it = find_if(sensors.begin(), sensors.end(), [](const Sensor& s) { return s.getId() == 42; });

    assert(it != sensors.end());
    assert(it->getLatitude() == "45.6");
    assert(it->getLongitude() == "0.4");

    cout << "✓ Capteur ID 42 trouvé avec latitude 45.6 et longitude 0.4\n" << endl;
}

// Teste le calcul de la qualité de l'air à une position donnée pour une date
void testAirQuality() {
    cout << "[TEST] Qualité de l'air à un point donné..." << endl;

    Service service;
    Date d(2019, 5, 1);

    float result = service.getAirQuality("45.2", "4.0", d);
    cout << "Qualité de l'air pour (45.2, 4.0) le 2019-05-01 : " << result << endl;
    assert(result == 8.0f);

    cout << "✓ Niveau d'ATMO attendu : 8\n" << endl;
}

// Teste que le système retourne 0 lorsqu'aucun capteur n'est à proximité
void testAirQualityRegion_noSensorsInRange() {
    cout << "[TEST] Aucun capteur à proximité, retour attendu : 0..." << endl;

    Service service;
    Date date(2023, 1, 1);

    float airQuality = service.getAirQuality("0.0", "0.0", date);
    cout << "Qualité de l'air pour une zone sans capteur : " << airQuality << endl;

    assert(airQuality == 0.0f);

    cout << "✓ Aucun capteur trouvé dans la zone, retour correct.\n" << endl;
}

// Teste l'impact des purificateurs d'air avec des scénarios haut et bas
void testCleanerEffect_radiusConstraint(){
    cout << "[TEST] Évaluation de l'impact des purificateurs d'air...\n" << endl;

    Service service;

    // Purificateur censé avoir un impact important (>80%)
    cout << " - Test avec Cleaner1 (impact attendu élevé)..." << endl;
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
    cout << "Amélioration mesurée : " << improvement << "%" << endl;
    assert(improvement > 80.0f);
    cout << "✓ Impact élevé détecté (>80%)\n" << endl;

    // Purificateur avec un impact supposé faible (<5%)
    cout << " - Test avec Cleaner0 (impact attendu faible)..." << endl;
    AirCleaner c0(0, "45.333333", "1.333333", Date(2019, 2, 1), Date(2019, 3, 1));
    for (const auto& cleaner : cleaners) {
        if (cleaner.getId() == 0) {
            c0 = cleaner;
            break;
        }
    }

    result = service.displayImpactCleaners(c0);
    improvement = result.second;
    cout << "Amélioration mesurée : " << improvement << "%" << endl;
    assert(improvement < 5.0f);
    cout << "✓ Faible impact détecté (<5%)\n" << endl;
}

// Point d'entrée des tests
int main() {
    cout << "==========================" << endl;
    cout << "=== Lancement des tests ===" << endl;
    cout << "==========================\n" << endl;

    cout << "--- Étape 1 : Parsing des données ---" << endl;
    testServiceSensorParsing_validInput();

    cout << "--- Étape 2 : Calcul de la qualité de l'air ---" << endl;
    testAirQuality();
    testAirQualityRegion_noSensorsInRange();

    cout << "--- Étape 3 : Analyse de l'impact des purificateurs ---" << endl;
    testCleanerEffect_radiusConstraint();

    cout << "\n===========================" << endl;
    cout << "=== Tous les tests OK ! ===" << endl;
    cout << "===========================\n" << endl;

    return 0;
}
