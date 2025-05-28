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
void test() {
    cout << "\033[48;5;236m"; // Change le background en gris foncé (code 236)
    cout << "\033[1;32mTest function called.\033[0m" << endl;
    cout << "\033[1;34m---------------------\033[0m" << endl;

    cout << "\033[1;33mCreating a Provider object\033[0m" << endl;
    Provider provider(1, "password", "mail", "name");
    cout << "\033[1;36mPrinting the provider details\033[0m" << endl;
    provider.print();

    cout << "\033[1;33m---------------------\033[0m" << endl;

    cout << "\033[1;33mCreating an AirCleaner object\033[0m" << endl;
    AirCleaner airCleaner(1, "lat", "lon", Date(2023, 10, 1), Date(2023, 10, 31));
    cout << "\033[1;36mPrinting the air cleaner details\033[0m" << endl;
    airCleaner.print();

    cout << "\033[1;33m---------------------\033[0m" << endl;

    provider.setAirCleaners({ airCleaner });
    cout << "\033[1;36mPrinting the provider details again\033[0m" << endl;    
    provider.print();

    cout << "\033[1;33m---------------------\033[0m" << endl;

    cout << "\033[1;33mCreating a PrivateIndividual object\033[0m" << endl;
    PrivateIndividual privateIndividual(1, "password", "mail", "firstName", "lastName", "phone", "address");
    cout << "\033[1;36mPrinting the private individual details\033[0m" << endl;
    privateIndividual.print();

    cout << "\033[1;34m---------------------\033[0m" << endl;

    cout << "\033[1;33mCreating a Sensor object\033[0m" << endl;
    Sensor sensor(1, "lat", "lon");
    cout << "\033[1;36mPrinting the sensor details\033[0m" << endl;
    sensor.print();
    cout << "\033[1;34m---------------------\033[0m" << endl;

    cout << "\033[1;33mCreating a Measurement object\033[0m" << endl;
    Measurement measurement(1, Date(2023, 10, 1), sensor, Attribut(1, "unit", "description"), 42.0);
    cout << "\033[1;36mPrinting the measurement details\033[0m" << endl;
    cout << "Measurement ID: " << measurement.getId() << endl;
    cout << "Measurement Date: " << measurement.getDate().year << "-" << measurement.getDate().month << "-" << measurement.getDate().day << endl;
    cout << "Measurement Sensor: " << measurement.getSensor().getId() << endl;
    cout << "Measurement Attribut: " << measurement.getAttribut().getId() << endl;
    cout << "Measurement Value: " << measurement.getValue() << endl;
    cout << "\033[1;34m---------------------\033[0m" << endl;

}

void ConsultQualityOfAir() {
    cout << "Consulting the quality of the air..." << endl;
    Service service;

    

}

void menuAgent(){
    int choix;
    do {
        cout << "\nDear Agent, choose your action :" << endl;
        cout << "1. Consult the quality of the air" << endl;
        cout << "2. Compare a sensor to the other ones" << endl;
        cout << "3. Consult statistics" << endl;
        cout << "4. Consult the impact of air cleaners" << endl;
        cout << "5. Analyse the data of a private individual" << endl;
        cout << "6. Consult the list of the excluded users" << endl;
        cout << "0. Go back" << endl;
        cout << "Choice : ";
        cin >> choix;

        switch (choix) {
            case 1: // On doit faire ca
            break;
            case 2: break;
            case 3: break;
            case 4: // On fait
            break;
            case 5: break;
            case 6: break;
            case 0: return;
            default: cout << "Invalid choice. Please choose again :.\n";
        }
    } while (choix != 0);
}

void menuFournisseur(){
    int choix;
    do {
        cout << "\nDear Provider, choose your action :" << endl;
        cout << "1. Consult the quality of the air" << endl;
        cout << "2. Compare a sensor to the other ones" << endl;
        cout << "3. Consult statistics" << endl;
        cout << "4. Consult the impact of air cleaners" << endl;
        cout << "0. Go back" << endl;
        cout << "Choice : ";
        cin >> choix;

        switch (choix) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 0: return;
            default: cout << "Invalid choice. Please choose again :.\n";
        }
    } while (choix != 0);
    return;
}

void menuUtilisateur(){
    int choix;
    do {
        cout << "\nDear User, choose your action :" << endl;
        cout << "1. Consult the quality of the air" << endl;
        cout << "2. Compare a sensor to the other ones" << endl;
        cout << "3. Consult statistics" << endl;
        cout << "4. Contribute data" << endl;
        cout << "5. Consult my points" << endl;
        cout << "6. Consult the data of my own sensors" << endl;
        cout << "0. Go back" << endl;
        cout << "Choice : ";
        cin >> choix;

        switch (choix) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 0: return;
            default: cout << "Invalid choice. Please choose again :.\n";
        }
    } while (choix != 0);
}

void afficherMenuConnexion(){
    int choix;
    do {
        cout << "\nPlease sign in :" << endl;
        cout << "1. Governmental agency" << endl;
        cout << "2. Providers" << endl;
        cout << "3. Private individuals" << endl;
        cout << "4. Test the app" << endl;
        cout << "0. Leave the app" << endl;
        cout << "Choice : ";
        cin >> choix;

        switch (choix) {
            case 1: menuAgent(); break;
            case 2: menuFournisseur(); break;
            case 3: menuUtilisateur(); break;
            case 4: test(); break;
            case 0: cout << "Goodbye !" << endl; break;
            default: cout << "Invalid choice. Please choose again :.\n";
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