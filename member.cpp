#include "member.h"

Member::Member(bool administrator,QString name,QString lastLogin,QString signature){
    this->administrator = administrator;
    this->name = name;
    this->lastLogin = lastLogin;
    this->signature = signature;
}

Member::Member(){}

Member::~Member(){}

QString Member::getSignature(){
    return this->signature;
}

bool Member::setPwd(QString pwd){
    return true;
}

void Member::setSignature(QString text){
    this->signature = text;
}

QString Member::getName(){
    return this->name;
}

QString Member::getLastLogin(){
    return this->lastLogin;
}

bool Member::isAdministrator(){
    return this->administrator;
}
