#include "reg.h"
#include "ui_reg.h"
#include "dbdriver.h"
#include <QDebug>
#include <QMessageBox>

Reg::Reg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reg)
{
    ui->setupUi(this);
    setWindowTitle("注册");
}

Reg::~Reg()
{
    delete ui;
}

void Reg::on_yes_clicked()
{
    Database *query(new Database("ManagementSys","127.0.0.1","uzi","vn"));
    if(ui->lineEdit->text().isEmpty()||
            ui->lineEdit_2->text().isEmpty()||
            ui->lineEdit_3->text().isEmpty()||
            ui->lineEdit_2->text()!=ui->lineEdit_3->text()){
        QMessageBox::warning(this,tr("Warning"),tr("输入有误，请重新输入！"),QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit->setFocus();
    }
    else {
        if(!query->insertUserInfo(std::make_pair<QString,QString>(
                              ui->lineEdit->text(),
                              ui->lineEdit_3->text()))){
            QMessageBox::warning(this,tr("Warning"),tr("用户名已存在"),QMessageBox::Yes);
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit->setFocus();
        }else{
            QMessageBox::information(NULL,"恭喜","注册成功！");
            this->close();
        }
    }
    delete query;
}

void Reg::on_no_clicked()
{
    this->close();
}
