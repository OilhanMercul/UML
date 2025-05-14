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
#include  <array>

//------------------------------------------------------ Include personnel
#include "User.h"
#include "AirCleaner.h"
#include "Provider.h"
#include "Attribut.h"
#include "Sensor.h"
#include "PrivateIndividual.h"
#include "Measurement.h"
#include "Service.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void menuAgent(){
    int choix;
    do {
        std::cout << "\nDear Agent, choose your action :" << std::endl;
        std::cout << "1. Consult the quality of the air" << std::endl;
        std::cout << "2. Compare a sensor to the other ones" << std::endl;
        std::cout << "3. Consult statistics" << std::endl;
        std::cout << "4. Consult the impact of air cleaners" << std::endl;
        std::cout << "5. Analyse the data of a private individual" << std::endl;
        std::cout << "6. Consult the list of the excluded users" << std::endl;
        std::cout << "0. Go back" << std::endl;
        std::cout << "Choice : ";
        std::cin >> choix;

        switch (choix) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 0: return;
            default: std::cout << "Invalid choice. Please choose again :.\n";
        }
    } while (choix != 0);
}

void menuFournisseur(){
    int choix;
    do {
        std::cout << "\nDear Provider, choose your action :" << std::endl;
        std::cout << "1. Consult the quality of the air" << std::endl;
        std::cout << "2. Compare a sensor to the other ones" << std::endl;
        std::cout << "3. Consult statistics" << std::endl;
        std::cout << "4. Consult the impact of air cleaners" << std::endl;
        std::cout << "0. Go back" << std::endl;
        std::cout << "Choice : ";
        std::cin >> choix;

        switch (choix) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 0: return;
            default: std::cout << "Invalid choice. Please choose again :.\n";
        }
    } while (choix != 0);
    return;
}

void menuUtilisateur(){
    int choix;
    do {
        std::cout << "\nDear User, choose your action :" << std::endl;
        std::cout << "1. Consult the quality of the air" << std::endl;
        std::cout << "2. Compare a sensor to the other ones" << std::endl;
        std::cout << "3. Consult statistics" << std::endl;
        std::cout << "4. Contribute data" << std::endl;
        std::cout << "5. Consult my points" << std::endl;
        std::cout << "6. Consult the data of my own sensors" << std::endl;
        std::cout << "0. Go back" << std::endl;
        std::cout << "Choice : ";
        std::cin >> choix;

        switch (choix) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 0: return;
            default: std::cout << "Invalid choice. Please choose again :.\n";
        }
    } while (choix != 0);
}

void afficherMenuConnexion(){
    int choix;
    do {
        std::cout << "\nPlease sign in :" << std::endl;
        std::cout << "1. Governmental agency" << std::endl;
        std::cout << "2. Providers" << std::endl;
        std::cout << "3. Private individuals" << std::endl;
        std::cout << "0. Leave the app" << std::endl;
        std::cout << "Choice : ";
        std::cin >> choix;

        switch (choix) {
            case 1: menuAgent(); break;
            case 2: menuFournisseur(); break;
            case 3: menuUtilisateur(); break;
            case 0: std::cout << "Goodbye !" << std::endl; break;
            default: std::cout << "Invalid choice. Please choose again :.\n";
        }
    } while (choix != 0);
}

int main() {
    std::cout << "Welcome to AirWatcher !\n";
    afficherMenuConnexion();
    return 0;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées