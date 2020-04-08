#ifndef CHANGEPWD_H
#define CHANGEPWD_H

#include <QDialog>
#include "dbdriver.h"
#include <QMessageBox>
#include "global.h"

namespace Ui {
class ChangePwd;
}

class ChangePwd : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePwd(QWidget *parent = 0);
    ~ChangePwd();

private slots:
    void on_yes_clicked();

    void on_no_clicked();

private:
    Ui::ChangePwd *ui;
};

#endif // CHANGEPWD_H
