/*************************************************************************
                           Main.cpp  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Main> (fichier User.cpp) ------------

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

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Service service;

void ConsultQualityOfAir() {
    cout << "\033[48;5;25m\033[1;37mConsulting the quality of the air...\033[0m" << endl;
    string latitude, longitude;
    Date date;
    cout << "\033[1;36mEnter latitude: \033[0m";
    cin >> latitude;
    cout << "\033[1;36mEnter longitude: \033[0m";
    cin >> longitude;
    cout << "\033[1;36mEnter date (YYYY MM DD): \033[0m";
    cin >> date.year >> date.month >> date.day;
    char choice;
    float radius = 0.0f;
    cout << "\033[1;36mDo you want to specify a radius? (y/n): \033[0m";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        cout << "\033[1;36mEnter radius (in km): \033[0m";
        cin >> radius;
    }
    else {
        radius = 10; // Default radius
    }
    float index = service.getAirQuality(latitude, longitude, date, radius);
    cout << "\033[1;33mAir quality index at (" << latitude << ", " << longitude 
         << ") on " << date.year << "-" << date.month << "-" << date.day 
         << " is: " << index << "\033[0m" << endl;
}

void ConsultImpactAirCleanner(){
    cout << "\033[48;5;236m\033[1;32mConsulting the impact of air cleaners...\033[0m" << endl;
    vector<AirCleaner> cleaners = service.getAirCleaners();
    if (cleaners.empty()) {
        cout << "\033[1;31mNo air cleaners available.\033[0m" << endl;
        return;
    }
    for (const auto& cleaner : cleaners) {
        cout << "\033[1;34m---------------------\033[0m" << endl;
        cleaner.print();
        pair<float, float> impact = service.displayImpactCleaners(cleaner);
        cout << "\033[1;33mImpact of cleaner ID " << cleaner.getId() 
             << ": \033[1;36mRadius: " << impact.first 
             << " \033[1;32mImprovement: " << impact.second << "% \033[0m" << endl;
    }
    cout << "\033[1;34mImpact consultation completed.\033[0m" << endl;
}

void menuAgent(){
    int choix;
    do {
        cout << "\033[48;5;24m\033[1;37m\nDear Agent, choose your action :\033[0m" << endl;
        cout << "\033[1;36m1. Consult the quality of the air\033[0m" << endl;
        cout << "\033[1;36m2. Compare a sensor to the other ones\033[0m" << endl;
        cout << "\033[1;36m3. Consult statistics\033[0m" << endl;
        cout << "\033[1;36m4. Consult the impact of air cleaners\033[0m" << endl;
        cout << "\033[1;36m5. Analyse the data of a private individual\033[0m" << endl;
        cout << "\033[1;36m6. Consult the list of the excluded users\033[0m" << endl;
        cout << "\033[1;36m0. Go back\033[0m" << endl;
        cout << "\033[1;33mChoice : \033[0m";
        cin >> choix;

        switch (choix) {
            case 1: ConsultQualityOfAir(); break;
            case 2: cout << "\033[1;31mComparing sensors is not implemented yet.\033[0m\n"; break;
            case 3: cout << "\033[1;31mStatistics are not implemented yet.\033[0m\n"; break;
            case 4: ConsultImpactAirCleanner(); break;
            case 5: cout << "\033[1;31mAnalyzing private individual data is not implemented yet.\033[0m\n"; break;
            case 6: cout << "\033[1;31mConsulting the list of excluded users is not implemented yet.\033[0m\n"; break;
            case 0: return;
            default: cout << "\033[1;31mInvalid choice. Please choose again :.\033[0m\n";
        }
    } while (choix != 0);
}

void menuFournisseur(){
    int choix;
    do {
        cout << "\033[48;5;52m\033[1;33m\nDear Provider, choose your action :\033[0m" << endl;
        cout << "\033[1;36m1. Consult the quality of the air\033[0m" << endl;
        cout << "\033[1;36m2. Compare a sensor to the other ones\033[0m" << endl;
        cout << "\033[1;36m3. Consult statistics\033[0m" << endl;
        cout << "\033[1;36m4. Consult the impact of air cleaners\033[0m" << endl;
        cout << "\033[1;36m0. Go back\033[0m" << endl;
        cout << "\033[1;33mChoice : \033[0m";
        cin >> choix;

        switch (choix) {
            case 1: ConsultQualityOfAir(); break;
            case 2: cout << "\033[1;31mComparing sensors is not implemented yet.\033[0m\n"; break;
            case 3: cout << "\033[1;31mStatistics are not implemented yet.\033[0m\n"; break;
            case 4: ConsultImpactAirCleanner(); break;
            case 0: return;
            default: cout << "\033[1;31mInvalid choice. Please choose again :.\033[0m\n";
        }
    } while (choix != 0);
}

void menuUtilisateur(){
    int choix;
    do {
        cout << "\033[48;5;22m\033[1;36m\nDear User, choose your action :\033[0m" << endl;
        cout << "\033[1;33m1. Consult the quality of the air\033[0m" << endl;
        cout << "\033[1;33m2. Compare a sensor to the other ones\033[0m" << endl;
        cout << "\033[1;33m3. Consult statistics\033[0m" << endl;
        cout << "\033[1;33m4. Contribute data\033[0m" << endl;
        cout << "\033[1;33m5. Consult my points\033[0m" << endl;
        cout << "\033[1;33m6. Consult the data of my own sensors\033[0m" << endl;
        cout << "\033[1;33m0. Go back\033[0m" << endl;
        cout << "\033[1;36mChoice : \033[0m";
        cin >> choix;

        switch (choix) {
            case 1: ConsultQualityOfAir(); break;
            case 2: cout << "\033[1;31mComparing sensors is not implemented yet.\033[0m\n"; break;
            case 3: cout << "\033[1;31mStatistics are not implemented yet.\033[0m\n"; break;
            case 4: cout << "\033[1;31mContributing data is not implemented yet.\033[0m\n"; break;
            case 5: cout << "\033[1;31mConsulting points is not implemented yet.\033[0m\n"; break;
            case 6: cout << "\033[1;31mConsulting my own sensors data is not implemented yet.\033[0m\n"; break;
            case 0: return;
            default: cout << "\033[1;31mInvalid choice. Please choose again :.\033[0m\n";
        }
    } while (choix != 0);
}

void afficherMenuConnexion(){
    int choix;
    do {
        cout << "\033[48;5;236m\033[1;35m\nPlease sign in :\033[0m" << endl;
        cout << "\033[1;36m1. Governmental agency\033[0m" << endl;
        cout << "\033[1;36m2. Providers\033[0m" << endl;
        cout << "\033[1;36m3. Private individuals\033[0m" << endl;
        cout << "\033[1;36m0. Leave the app\033[0m" << endl;
        cout << "\033[1;33mChoice : \033[0m";
        cin >> choix;

        switch (choix) {
            case 1: menuAgent(); break;
            case 2: menuFournisseur(); break;
            case 3: menuUtilisateur(); break;
            case 0: cout << "\033[1;32mGoodbye !\033[0m" << endl; break;
            default: cout << "\033[1;31mInvalid choice. Please choose again :.\033[0m\n";
        }
    } while (choix != 0);
}



int main() {
    
    cout << "Welcome to AirWatcher !\n";
    afficherMenuConnexion();
    return 0;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées