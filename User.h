#ifndef USER_H
#define USER_H

using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include  <array>

class User {
protected:
    //Atributes
    int id;
    string password;
    string email;

public:
    //Getters and Setters
    void setId(int id);
    void setPassword(const string& password);
    void setEmail(const string& email);
    int getId() const;
    string getPassword() const;
    string getEmail() const;
    virtual void print() const = 0; // Pure virtual function

    //Constructors and Destructor
    User(int id, const string& password, const string& email);
    User() : id(0), password(""), email("") {};
    User(const User& user);

};

#endif