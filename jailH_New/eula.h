#ifndef EULA_H
#define EULA_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class Eula;
}

class Eula : public QDialog
{
    Q_OBJECT

public:
    explicit Eula(QWidget *parent = 0);
    ~Eula();

private slots:

    void on_pushButton_Accept_clicked();

    void on_pushButton_Do_not_accept_clicked();

private:
    Ui::Eula *ui;
    MainWindow *w ;
};

#endif // EULA_H
