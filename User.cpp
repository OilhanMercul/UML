
using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include  <array>

#include "User.h"

User::User(int id, const string& password, const string& email){
    this->id = id;
    this->password = password;
    this->email = email;
}

User::User(const User& user) {
    this->password = user.password;
    this->email = user.email;
    this->id = user.id;
}

void User::setPassword(const string& password) {
    this->password = password;
}

string User::getPassword() const {
    return this->password;
}

void User::setEmail(const string& email) {
    this->email = email;
}

string User::getEmail() const {
    return this->email;
}

void User::setId(int id) {
    this->id = id;
}

int User::getId() const {
    return this->id;
}
