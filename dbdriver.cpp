#include <QApplication>
#include <QSql>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <dbdriver.h>
#include "global.h"
#include <QDateTime>

/**
 * @brief :a class to access database.
 * @param dsn :name of data source.
 * @param hostname :host address.
 * @param username :as the name suggests.
 * @param password :as the name suggests.
 *
 */
Database::Database(QString dsn,
                    QString hostname,
                    QString username,
                    QString password)
{
    db = QSqlDatabase::addDatabase("QODBC");
    qDebug()<<"ODBC driver?"<<db.isValid();
    db.setHostName(hostname);
    db.setDatabaseName(dsn);
    db.setUserName(username);
    db.setPassword(password);
}

Database::~Database(){
    qDebug()<<"success to delete a object";
}

bool Database::openDB(){
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
        return false;
    }else{
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        query.exec("SELECT * FROM UserInfo");
        while(query.next()){
            qDebug()<<query.value(0).toString()<<query.value(1).toString()<<query.value(2).toString()
                   <<query.value(3).toString()<<query.value(4).toString()<<query.value(5).toString();
        }
    }
    return true;
}

bool Database::insertUserInfo(std::pair<QString,QString> info){
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
        return false;
    }else{
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        QString str;
        str = "INSERT INTO UserInfo (UserName,Pwd,Since,IsAd) VALUES ('"+info.first+"','"+info.second+"',GETDATE(),0)";
        query.prepare(str);
        if(!query.exec())return false;
    }
    return true;
}

bool Database::checkUserInfo(std::pair<QString, QString> info,bool isad){
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }else{
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        if(isad)
            query.exec("SELECT * FROM UserInfo WHERE UserName='"+info.first+"' AND Pwd='"+info.second+"'AND IsAd=1");
        else
            query.exec("SELECT * FROM UserInfo WHERE UserName='"+info.first+"' AND Pwd='"+info.second+"'AND IsAd=0");
        if(query.next()){
            me = new Member(query.value(5).toBool(),
                                   query.value(0).toString(),
                                   query.value(3).toString(),
                                   query.value(4).toString());
            return true;
        }
    }
    return false;
}

void Database::updateLastLogin(){
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }else{
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        query.exec("UPDATE UserInfo SET LastLogin=GETDATE() WHERE UserName='"+me->getName()+"'");
    }
}

bool Database::setSignature(){
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }else{
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        query.exec("UPDATE UserInfo SET Signature='"+me->getSignature()+"' WHERE UserName='"+me->getName()+"'");
        return true;
    }
    return false;
}

bool Database::publishMoment(QString context){
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }else{
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        if(query.exec("INSERT INTO Moment VALUES('"+me->getName()+"',GETDATE(),'"+context+"',0)")){
            return true;
        }else{
            QMessageBox::information(NULL,"警告","您的发布过于频繁，请稍后再试");
        }
    }
    return false;
}

QList<QList<QString>> Database::getUserPublish(){
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }else{
        QList<QList<QString>> res;
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        query.exec("SELECT * FROM Moment WHERE UserName='"+me->getName()+"'");
        while(query.next()){
            QList<QString> tmp;
            for(int i(0);i<4;i++)
                tmp.append(query.value(i).toString());
            res.append(tmp);
        }
        return res;
    }
    return {};
}

QList<QList<QString>> Database::getWholeMes(){
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }else{
        QList<QList<QString>> res;
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        query.exec("SELECT * FROM Moment WHERE IsReview=1");
        while(query.next()){
            QList<QString> tmp;
            for(int i(0);i<4;i++)
                tmp.append(query.value(i).toString());
            res.append(tmp);
        }
        return res;
    }
    return {};
}

bool Database::del(QString time){
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }else{
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        time.replace(10,1," ");
        qDebug()<<time;
        query.exec("DELETE FROM Moment WHERE PublicDate='"+time+"'");
        return true;
    }
    return false;
}

QList<QList<QString>> Database::showAllMember(){
    QList<QList<QString>> res;
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }else{
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        query.exec("SELECT * FROM UserInfo WHERE IsAd=0");
        while(query.next()){
            res.append({query.value(0).toString(),query.value(2).toString(),query.value(3).toString(),
                       query.value(4).toString()});
        }
    }
    return res;
}

bool Database::changePwd(QString originalPwd,QString newPwd){
    QList<QList<QString>> res;
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }else{
        qDebug()<<"Database open success!";
        QSqlQuery query(db);
        query.exec("SELECT Pwd FROM UserInfo WHERE UserName='"+me->getName()+"'");
        if(query.next()){
            if(query.value(0).toString()==originalPwd){
                query.exec("UPDATE UserInfo SET Pwd='"+newPwd+"' WHERE UserName='"+me->getName()+"'");
                return true;
            }
        }
    }
    return false;
}
