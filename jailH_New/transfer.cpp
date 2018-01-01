/*
 * Module for transfering config.c files to the target
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include "transfer.h"
#include "ui_transfer.h"
#include <sstream>
#include <QProcess>
#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <QtWidgets>
#include "mainwindow.h"


Transfer::Transfer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transfer)
{
    ui->setupUi(this);
}

Transfer::~Transfer()
{
    delete ui;
}

// on event clicked Go button, To transfer the config.c file from host to target
void Transfer::on_pushButton_Go_clicked()
{
    //proc = new QProcess() ;
    QString command = "scp" ;
    QString ip = ui->lineEdit_IP_Address->text() ;
    QString username = ui->lineEdit_SSH_username->text() ;
    QString password = ui->lineEdit_SSH_password->text() ;
    QString dest_path = ui->lineEdit_TransferToTarget_DestinationFolder->text() ;
    QString source_path = ui->lineEdit_TransferToTarget_SourcePath->text() ;
    std::stringstream s ;
    s << username.toStdString() << "@" << ip.toStdString() << ":" << dest_path.toStdString();
    std::cout << s.str() << std::endl ;
    QStringList params ;
    params.append("-p");
    params.append(password);
    params.append(command);
    params.append(source_path) ;
    params.append(QString::fromStdString(s.str())) ;
    qDebug() << params ;
    //    params.append("/home/span51/Desktop/readme.txt");
    //    params.append("spanidea@192.168.1.26:/home/spanidea/test" );
    qDebug() << connect(&proc, SIGNAL(readyReadStandardError()), this, SLOT(readOutput()));
    qDebug() << connect(&proc, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    //    connect(&proc, SIGNAL(errorOccurred(QProcess::ProcessError error)), this, SLOT(readErr()));
    proc.start("sshpass",params) ;

}

// To get the path for a config.c file
void Transfer::on_pushButton_choosefile_transferTotarget_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Transfer file"), "/home","Config_Files(*.c)") ;
    ui->lineEdit_TransferToTarget_SourcePath->setText(filepath);
}

void Transfer::on_pushButton_Std_output_clear_clicked()
{
    ui->textEdit_Standard_output->clear() ;
}

// To show password
void Transfer::on_checkBox_Show_Password_clicked(bool checked)
{
    if (checked)
        ui->lineEdit_SSH_password->setEchoMode(QLineEdit::Normal);
    else
        ui->lineEdit_SSH_password->setEchoMode(QLineEdit::Password);
}

// To redirect stdout and stdError to GUI text screen
void Transfer::readOutput()
{
    std::cout << "i'm in readoutput now" << std::endl ;
    QString StdOut = proc.readAllStandardOutput();  //Reads standard output
    QString StdError = proc.readAllStandardError(); // Reads standard error
    qDebug() << StdOut ;
    qDebug() << StdError ;

    //    ui->textEdit_Standard_output->setText(StdOut);
    //   ui->textEdit_Standard_output->setText(StdError);
    ui->textEdit_Standard_output->setText(ui->textEdit_Standard_output->toPlainText() + StdOut + StdError);

}

void Transfer::closeEvent(QCloseEvent *event) {
    emit uncheck_transfer() ;
}


