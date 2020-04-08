#ifndef MEMBER_H
#define MEMBER_H
#include "person.h"

class Member:public Person
{
private:
    QString signature;
public:
    Member(bool administrator,QString name,QString lastLogin,QString signature);
    Member();
    ~Member();
    QString getSignature();
    void setSignature(QString text);
    bool setPwd(QString pwd);
    bool isAdministrator();
    QString getName();
    QString getLastLogin();
};

#endif // MEMBER_H
