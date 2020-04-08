#include "person.h"

Person::Person(){}

Person::~Person(){}

bool inline Person::isAdministrator(){
    return this->administrator;
}

QString inline Person::getName(){
    return this->name;
}

QString inline Person::getLastLogin(){
    return this->lastLogin;
}
