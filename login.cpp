#include "login.h"
#include "ui_login.h"
#include "reg.h"
#include "dbdriver.h"
#include "member.h"
#include "global.h"
#include <QMessageBox>
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("欢迎光临！");
    IsAd = false;
}

Login::~Login()
{
    delete ui;
}

void Login::on_exit_clicked()
{
    this->close();
}

void Login::on_login_clicked()
{
    if(ui->userInput->text().isEmpty()||
            ui->passwordInput->text().isEmpty()){
        QMessageBox::warning(this,tr("Warning"),tr("用户名或密码错误！"),QMessageBox::Yes);
        ui->userInput->clear();
        ui->passwordInput->clear();
        ui->userInput->setFocus();
    }else{
        Database *query(new Database(dsn,hostname,username,password));
        if(!query->checkUserInfo(std::make_pair<QString,QString>(
                                     ui->userInput->text(),
                                     ui->passwordInput->text()),
                                     this->IsAd
                                 )){
            QMessageBox::warning(this,tr("Warning"),tr("用户名或密码错误！"),QMessageBox::Yes);
            ui->userInput->clear();
            ui->passwordInput->clear();
            ui->userInput->setFocus();
        }else{
            QMessageBox::information(NULL,"你好","登录成功！");
            accept();
        }
        delete query;
    }

}

void Login::on_reg_clicked()
{
    Reg reg;
    reg.exec();
}

void Login::on_checkBox_stateChanged(int argv)
{
    this->IsAd = !this->IsAd;
}
