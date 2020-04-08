#include "deltext.h"
#include "ui_deltext.h"

Deltext::Deltext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deltext)
{
    ui->setupUi(this);
    setWindowTitle("删除");
}

Deltext::~Deltext()
{
    delete ui;
}

void Deltext::on_no_clicked()
{
    close();
}

void Deltext::on_yes_clicked()
{
    QString time = ui->lineEdit->text();
    Database* query(new Database(dsn,hostname,username,password));
    if(query->del(time)){
        qDebug()<<"success delete!";
    }
    delete query;
    close();
}
