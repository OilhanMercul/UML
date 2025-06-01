# README - AIRWATCHER : Surveillance de la qualité de l’air en C++

## Description

**AirWatcher** est une application en ligne de commande développée en C++, permettant d’analyser et de surveiller la qualité de l’air à partir de fichiers de données fournis par une agence gouvernementale. L’application prend en charge différents profils utilisateurs (agence, fournisseur, utilisateur particulier) et propose plusieurs fonctionnalités :

- Consultation de la qualité de l’air à un endroit et une date donnés
- Calcul de la qualité moyenne de l’air dans une zone circulaire
- Analyse d’impact des purificateurs d’air
- Détection de capteurs défectueux ou malveillants
- Comparaison de similarité entre capteurs
- Attribution de points aux utilisateurs particuliers

L’ensemble des données (capteurs, mesures, attributs, utilisateurs, purificateurs) est lu à partir de fichiers CSV fournis localement.

## Installation



### Compilation

À la racine du projet, lancez la commande suivante dans un terminal :

``make``

Cela compilera l’exécutable principal `main`.

Pour compiler la version de test, utilisez :

``make test``

Cela compilera l’exécutable secondaire  `test`.

## Nettoyage

Pour supprimer les fichiers objets et les exécutables générés :

``make clean``

## Utilisation

### Lancer l’application

`./main`

Un menu interactif s’affiche, permettant de sélectionner un profil utilisateur :

- **Agence gouvernementale**
- **Fournisseur**
- **Utilisateur individuel**

Les fonctionnalités disponibles varient selon le profil sélectionné.

### Lancer les tests

Pour exécuter les tests unitaires :

`./test`

Les tests couvrent notamment :

- Le parsing des fichiers CSV (sensors, measurements, attributes…)
- Le calcul d’indices de qualité de l’air (basé sur l’indice ATMO)
- L’analyse d’impact des purificateurs d’air

## Fichiers fournis


- Fichiers sources et entêtes (`*.cpp` / `*.h`) organisés par module
   - Measurement
   - Attribut
   - AirCleaner
   - Sensor
   - User
   - Provider
   - PrivateIndividual
   - Service (pour toutes les méthodes)
- `main.cpp` : point d’entrée de l’application
- `main_test.cpp` : contient les cas de tests unitaires
- `Makefile` : script de compilation
- Fichiers CSV d’exemple (ex: `sensors.csv`, `measurements.csv`, etc.)
- `README.md` : ce fichier



## Structure du Code

## Structure du Code

L’architecture d’AirWatcher suit un modèle en couches (Layered Architecture), facilitant la maintenance, les tests et l’évolutivité.

1. Présentation (Presentation Layer)
- Gère l’interface console : affichage des menus, saisie utilisateur. Il y en a également un spécial pour les tests.
- Fichiers : main.cpp/h, main_test.cpp/h

2. Cœur Métier (Domain Layer)
- Définit les entités principales manipulées dans le système (.h/.cpp)
- Classes : Measurement, Sensor, User, PrivateIndividual, Provider, Cleaner, Attribute

3. Données (Data Layer)
- Contient les fichiers de données utilisés par l’application.
- Fichiers CSV : sensors.csv, measurements.csv, users.csv, cleaners.csv, attributes.csv

4. Utilitaires (Utility Layer)
- Fournit des services transversaux : logs, configuration, outils de mesure.
- Fichiers : Service.cpp/h

## Exemples d’utilisation

- Consulter la qualité de l’air dans le petit village de Chamalières-sur-Loire (43) le 5 janvier 2019 : 

./main  
# Choix du profil : Agence  
# → Consulter la qualité de l’air  
# → Saisir position et date : (45.75, 4.85), 2019 01 05


- Analyser les effets et impacts des purificateurs :

./main  
# Choix du profil : Fournisseur  
# → Rechercher les effets des purifications


## Auteurs

Projet réalisé dans le cadre du cours **Software Engineering Labs - POO2**, INSA Lyon - Département Informatique.

- ANTONIETTI Léa
- FRANCU Teodor Matei 
- MERCUL Oilhan
- VERON Loris
- VLAD Andreea Cristiana

Groupes binomiaux : B3125 & B312?

## Remarques

- L’application ne modifie pas les fichiers CSV originaux.
- Elle fonctionne uniquement sur données statiques lues au lancement.
- Toutes les méthodes n'ont pas été codées car le projet se concentrait uniquement sur certains scénarios définis.
- Seules les options affichées en bleu dans le menu principal sont fonctionnelles, conformément aux spécifications du sujet. Les autres fonctionnalités ont été laissées en tant que squelette ou à l’état partiellement implémenté.
