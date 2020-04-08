#ifndef EDITTEXT_H
#define EDITTEXT_H

#include <QDialog>

namespace Ui {
class editText;
}

class editText : public QDialog
{
    Q_OBJECT

public:
    explicit editText(QWidget *parent = 0);
    ~editText();

private slots:
    void on_no_clicked();
    void on_yes_clicked();

    void on_plainTextEdit_textChanged();

private:
    Ui::editText *ui;
    const int MAXTEXTSIZE = 32;
};

#endif // EDITTEXT_H
