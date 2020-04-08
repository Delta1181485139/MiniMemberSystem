#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "dbdriver.h"
#include "edittext.h"
#include <QDebug>
#include <QMessageBox>
#include <QLayout>
#include "global.h"
#include "deltext.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include "login.h"
#include "changepwd.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_signatureEdit_clicked();

    void on_publish_clicked();

    void on_mypublish_clicked();

    void on_plainTextEdit_textChanged();

    void on_explore_clicked();

    void on_del_clicked();

    void on_manage_clicked();

    //void del();// this is a public slots function

    void on_deleteUser_clicked();

    void on_yes_clicked();

    void on_no_clicked();

    void on_find_clicked();

    void on_reviewed_clicked();

    void on_deleteReviewed_clicked();

    void on_review_clicked();

    void on_pass_clicked();

    void on_changePwd_clicked();

private:
    Ui::MainWindow *ui;
    const int MAXTEXTSIZE = 200;
    QList<QPlainTextEdit*> list;
    QSqlTableModel *manageMember;

};

#endif // MAINWINDOW_H
