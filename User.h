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

    //Getters and Setters
    void setId(int id);
    void setPassword(const string& password);
    void setEmail(const string& email);
    int getId() const;
    string getPassword() const;
    string getEmail() const;

    //Constructors and Destructor
    User(int id, const string& password, const string& email);
    User(const User& user);
    ~User();

};