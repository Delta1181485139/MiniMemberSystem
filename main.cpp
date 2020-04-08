#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "login.h"
#include "reg.h"
#include "member.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login log;
    if(log.exec()==QDialog::Accepted){
        MainWindow win;
        win.show();
        return a.exec();
    }
    return 0;
}
