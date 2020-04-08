#include "changepwd.h"
#include "ui_changepwd.h"

ChangePwd::ChangePwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePwd)
{
    ui->setupUi(this);
    setWindowTitle("修改密码");
}

ChangePwd::~ChangePwd()
{
    delete ui;
}

void ChangePwd::on_yes_clicked()
{
    Database* query(new Database(dsn,hostname,username,password));
    if(ui->newPwd->text()==ui->newAgain->text()){
        if(query->changePwd(ui->originalPwd->text(),ui->newPwd->text())){
            QMessageBox::information(NULL,"恭喜","密码修改成功！");
            close();
        }else{
            QMessageBox::information(NULL,"警告","密码输入错误！");
        }
    }else{
        QMessageBox::information(NULL,"警告","两次密码输入不一致！");
    }
    delete query;
}

void ChangePwd::on_no_clicked()
{
    close();
}
