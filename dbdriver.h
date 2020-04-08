#ifndef DBDRIVER_H
#define DBDRIVER_H

#include <QSqlDatabase>
#include <initializer_list>
#include <utility>
#include "member.h"

class Database
{
public:
    Database(QString dsn,
             QString hostname,
             QString username,
             QString password);
    ~Database();

    bool openDB();
    bool insertUserInfo(std::pair<QString,QString> info);
    bool checkUserInfo(std::pair<QString,QString> info,bool isad);
    void updateLastLogin();
    bool setSignature();
    bool publishMoment(QString context);
    QList<QList<QString>> getUserPublish();
    QList<QList<QString>> getWholeMes();
    bool del(QString time);
    QList<QList<QString>> showAllMember();
    bool changePwd(QString originalPwd,QString newPwd);


private:
    QSqlDatabase db;
};
#endif // DBDRIVER_H
