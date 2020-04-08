#ifndef DELTEXT_H
#define DELTEXT_H

#include <QDialog>
#include "dbdriver.h"
#include "global.h"
#include <QDebug>

namespace Ui {
class Deltext;
}

class Deltext : public QDialog
{
    Q_OBJECT

public:
    explicit Deltext(QWidget *parent = 0);
    ~Deltext();

private slots:
    void on_no_clicked();

    void on_yes_clicked();

private:
    Ui::Deltext *ui;
};

#endif // DELTEXT_H
