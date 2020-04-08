#ifndef REG_H
#define REG_H

#include <QDialog>

namespace Ui {
class Reg;
}

class Reg : public QDialog
{
    Q_OBJECT

public:
    explicit Reg(QWidget *parent = 0);
    ~Reg();

private slots:

    void on_yes_clicked();

    void on_no_clicked();

private:
    Ui::Reg *ui;
};

#endif // REG_H
