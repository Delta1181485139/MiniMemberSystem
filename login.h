#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:

    void on_exit_clicked();

    void on_reg_clicked();

    void on_login_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::Login *ui;
    bool IsAd;
};

#endif // LOGIN_H
