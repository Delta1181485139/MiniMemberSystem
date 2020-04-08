#ifndef PERSON_H
#define PERSON_H
#include<QDialog>

class Person
{
protected:
    bool administrator;
    QString name;
    QString lastLogin;
public:
    Person();
    ~Person();
    bool isAdministrator();
    QString getName();
    QString getLastLogin();
    virtual bool setPwd(QString pwd) = 0;
};

#endif // PERSON_H
