/*
 * This module is for EULA Acceptance
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include "eula.h"
#include "ui_eula.h"
#include "mainwindow.h"

Eula::Eula(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Eula)
{
    ui->setupUi(this);
    QFont font("Plastique",10);
//    font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);
}

Eula::~Eula()
{
    delete ui;
}



void Eula::on_pushButton_Accept_clicked()
{
    w = new MainWindow ;
    w->show();
    this->close() ;
}

void Eula::on_pushButton_Do_not_accept_clicked()
{
    this->close() ;
}
