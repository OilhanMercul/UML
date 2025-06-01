/*************************************************************************
                           Main.cpp  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Main> (fichier Main.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

//------------------------------------------------------ Include personnel
#include "Provider.h"
#include "AirCleaner.h"
#include "PrivateIndividual.h"
#include "Measurement.h"
#include "Attribut.h"
#include "Service.h"
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- GLOBAL

Service service; // Instance globale du service, utilisée par les différentes fonctions

//----------------------------------------------------------------- FONCTIONS

void afficherCapteursDisponibles();


//--- Fonction permettant de consulter la qualité de l'air en un point donné
void ConsultQualityOfAir() {
    cout << "\n\033[48;5;25m\033[1;37m[ Consultation de la qualité de l'air ]\033[0m\n";
    
    string latitude, longitude;
    Date date;

    cout << "\033[1;36mEntrez la latitude : \033[0m";
    cin >> latitude;

    cout << "\033[1;36mEntrez la longitude : \033[0m";
    cin >> longitude;

    cout << "\033[1;36mEntrez la date (AAAA MM JJ) : \033[0m";
    cin >> date.year >> date.month >> date.day;

    char choice;
    float radius = 0.0f;

    cout << "\033[1;36mSouhaitez-vous spécifier un rayon ? (y/n) : \033[0m";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        cout << "\033[1;36mEntrez le rayon (en km) : \033[0m";
        cin >> radius;
    } else {
        radius = 10; // Rayon par défaut
    }

    float index = service.getAirQuality(latitude, longitude, date, radius);
    
    cout << "\n\033[1;33mIndice de qualité de l'air à (" << latitude << ", " << longitude 
         << ") le " << date.year << "-" << date.month << "-" << date.day 
         << " : " << index << "\033[0m\n";
}

//--- Fonction affichant l'impact des purificateurs d'air disponibles
void ConsultImpactAirCleanner(){
    cout << "\n\033[48;5;236m\033[1;32m[ Analyse de l'effet des purificateurs d'air ]\033[0m\n";

    vector<AirCleaner> cleaners = service.getAirCleaners();

    if (cleaners.empty()) {
        cout << "\033[1;31mAucun purificateur d'air disponible.\033[0m\n";
        return;
    }

    for (const auto& cleaner : cleaners) {
        cout << "\n\033[1;34m---------------------\033[0m\n";
        cleaner.print(); // Affichage des infos du purificateur

        pair<float, float> impact = service.displayImpactCleaners(cleaner); // Rayon + amélioration

        cout << "\033[1;33mImpact du purificateur ID " << cleaner.getId() 
             << " : \033[1;36mRayon : " << impact.first 
             << " km \033[1;32mAmélioration : " << impact.second << "% \033[0m\n";
    }

    cout << "\n\033[1;34mFin de l'analyse.\033[0m\n";
}

//--- Menu pour un agent gouvernemental
void menuAgent(){
    int choix;
    do {
        cout << "\n\033[48;5;24m\033[1;37mMenu Agent - Choisissez une action :\033[0m\n";
        cout << "\033[1;36m1. Consulter la qualité de l'air\033[0m\n";
        cout << "2. Comparer un capteur (non implémenté)\n";
        cout << "3. Consulter des statistiques (non implémenté)\n";
        cout << "\033[1;36m4. Voir l'effet des purificateurs\033[0m\n";
        cout << "5. Analyser un utilisateur (non implémenté)\n";
        cout << "6. Voir la liste des utilisateurs exclus (non implémenté)\n";
        cout << "\033[1;36m7. Voir la liste des capteurs\033[0m\n";
        cout << "0. Retour\n";
        cout << "\033[1;33mVotre choix : \033[0m";
        cin >> choix;

        switch (choix) {
            case 1: ConsultQualityOfAir(); break;
            case 4: ConsultImpactAirCleanner(); break;
            case 7: afficherCapteursDisponibles(); break;
            case 0: return;
            default: cout << "\033[1;31mFonction non disponible ou choix invalide.\033[0m\n";
        }
    } while (choix != 0);
}

//--- Menu pour un fournisseur de purificateurs
void menuFournisseur(){
    int choix;
    do {
        cout << "\n\033[48;5;52m\033[1;33mMenu Fournisseur - Choisissez une action :\033[0m\n";
        cout << "\033[1;36m1. Consulter la qualité de l'air\033[0m\n";
        cout << "2. Comparer un capteur (non implémenté)\n";
        cout << "3. Statistiques (non implémenté)\n";
        cout << "\033[1;36m4. Effet des purificateurs\033[0m\n";
        cout << "0. Retour\n";
        cout << "\033[1;33mVotre choix : \033[0m";
        cin >> choix;

        switch (choix) {
            case 1: ConsultQualityOfAir(); break;
            case 4: ConsultImpactAirCleanner(); break;
            case 0: return;
            default: cout << "\033[1;31mChoix invalide.\033[0m\n";
        }
    } while (choix != 0);
}

//--- Fonction affichant la liste des capteurs
void afficherCapteursDisponibles() {
    cout << "\n\033[48;5;237m\033[1;36m[ Liste des capteurs disponibles ]\033[0m\n";

    const vector<Sensor>& sensors = service.getSensors();

    if (sensors.empty()) {
        cout << "\033[1;31mAucun capteur trouvé dans les données.\033[0m\n";
        return;
    }

    for (const Sensor& s : sensors) {
        cout << "\033[1;34mID: \033[0m" << s.getId()
             << " \033[1;34m| Latitude: \033[0m" << s.getLatitude()
             << " \033[1;34m| Longitude: \033[0m" << s.getLongitude()
             << endl;
    }

    cout << "\n\033[1;32mTotal: " << sensors.size() << " capteurs.\033[0m\n";
}


//--- Menu pour un utilisateur individuel
void menuUtilisateur(){
    int choix;
    do {
        cout << "\n\033[48;5;22m\033[1;36mMenu Utilisateur - Choisissez une action :\033[0m\n";
        cout << "1. Consulter la qualité de l'air\n";
        cout << "2. Comparer un capteur (non implémenté)\n";
        cout << "3. Statistiques (non implémenté)\n";
        cout << "4. Contribuer des données (non implémenté)\n";
        cout << "5. Voir mes points (non implémenté)\n";
        cout << "6. Voir les données de mes capteurs (non implémenté)\n";
        cout << "0. Retour\n";
        cout << "\033[1;36mVotre choix : \033[0m";
        cin >> choix;

        switch (choix) {
            case 1: ConsultQualityOfAir(); break;
            case 0: return;
            default: cout << "\033[1;31mFonction non disponible ou choix invalide.\033[0m\n";
        }
    } while (choix != 0);
}

//--- Menu principal de connexion selon le type d'utilisateur
void afficherMenuConnexion(){
    int choix;
    do {
        cout << "\n\033[48;5;236m\033[1;35mConnexion - Qui êtes-vous ?\033[0m\n";
        cout << "1. Agence gouvernementale\n";
        cout << "2. Fournisseur\n";
        cout << "3. Utilisateur individuel\n";
        cout << "0. Quitter l'application\n";
        cout << "\033[1;33mVotre choix : \033[0m";
        cin >> choix;

        switch (choix) {
            case 1: menuAgent(); break;
            case 2: menuFournisseur(); break;
            case 3: menuUtilisateur(); break;
            case 0: cout << "\033[1;32mMerci d’avoir utilisé AirWatcher. À bientôt !\033[0m\n"; break;
            default: cout << "\033[1;31mChoix invalide.\033[0m\n";
        }
    } while (choix != 0);
}



//--- Point d'entrée du programme
int main() {
    cout << "\n\033[1;32mBienvenue dans l'application AirWatcher 🌿\033[0m\n";
    afficherMenuConnexion();
    return 0;
}
