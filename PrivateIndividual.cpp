#include "PrivateIndividual.h"

PrivateIndividual::PrivateIndividual(int id, const string& password, const string& email, const string& firstName, const string& lastName, const string& phone, const string& address)
    : User(id, password, email), points(0), address(address), firstName(firstName), lastName(lastName), phone(phone), reliable(false) {
}

PrivateIndividual::PrivateIndividual(const PrivateIndividual& privateIndividual)
    : User(privateIndividual), points(privateIndividual.points), address(privateIndividual.address),firstName(privateIndividual.firstName), lastName(privateIndividual.lastName), phone(privateIndividual.phone), sensors(privateIndividual.sensors), reliable(privateIndividual.reliable) {

}

void PrivateIndividual::setFirstName(const string& firstName) {
    this->firstName = firstName;
}

string PrivateIndividual::getFirstName() const {
    return this->firstName;
}

void PrivateIndividual::setLastName(const string& lastName) {
    this->lastName = lastName;
}

string PrivateIndividual::getLastName() const {
    return this->lastName;
}

void PrivateIndividual::setPhone(const string& phone) {
    this->phone = phone;
}

string PrivateIndividual::getPhone() const {
    return this->phone;
}

void PrivateIndividual::setAddress(const string& address) {
    this->address = address;
}

string PrivateIndividual::getAddress() const {
    return this->address;
}

void PrivateIndividual::setSensors(const list<Sensor>& sensors) {
    this->sensors = sensors;
}

/*************  ✨ Windsurf Command ⭐  *************/
/**
 * @brief Get the list of sensors associated with this private individual.
 *
 * @return A list of Sensor objects representing the sensors associated with
 *         this private individual.
 */
/*******  15853ca7-430a-4078-bd4f-bd3e6d636115  *******/list<Sensor> PrivateIndividual::getSensors() const {
    return this->sensors;
}

void PrivateIndividual::setPoints(int points) {
    this->points = points;
}

int PrivateIndividual::getPoints() const {
    return this->points;
}

int PrivateIndividual::consultPoints() {
    return this->points;
}

void PrivateIndividual::print() const {
    cout << "Private Individual ID: " << id << endl; // Assuming id is inherited from User
    cout << "Private Individual Password: " << password << endl; // Assuming password is inherited from User
    cout << "Private Individual Email: " << email << endl; // Assuming email is inherited from User
    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Phone: " << phone << endl;
    cout << "Address: " << address << endl;
    cout << "Points: " << points << endl;
    cout << "Reliable: " << (reliable ? "Yes" : "No") << endl;
    cout << "Sensors: " << endl;
    for (const auto& sensor : sensors) {
        sensor.print(); // Assuming Sensor has a print method
    }
}

void PrivateIndividual::setReliable(bool reliable) {
    this->reliable = reliable;
}

bool PrivateIndividual::getReliable() const {
    return this->reliable;
}

