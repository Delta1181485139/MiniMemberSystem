#include "edittext.h"
#include "ui_edittext.h"
#include "global.h"
#include "dbdriver.h"
#include <QDebug>
#include <QMessageBox>

editText::editText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editText)
{
    ui->setupUi(this);
    ui->label->setText("0/"+QString::number(MAXTEXTSIZE));
    setWindowTitle("编辑签名");
}

editText::~editText()
{
    delete ui;
}

void editText::on_no_clicked()
{
    close();
}

void editText::on_yes_clicked()
{
    if(ui->plainTextEdit->toPlainText().count()>MAXTEXTSIZE){
        QMessageBox::information(NULL,"警告","字数超过最大限制");
    }else{
        QString str = ui->plainTextEdit->toPlainText();
        me->setSignature(str);
        Database *query(new Database(dsn,hostname,username,password));
        query->setSignature();
        delete query;
        accept();
        close();
    }
}

void editText::on_plainTextEdit_textChanged()
{
    ui->label->setText(QString::number(ui->plainTextEdit->toPlainText().count())
                       +"/"+
                       QString::number(MAXTEXTSIZE));
}
