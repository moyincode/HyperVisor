/*
 * Module for importing files into GUI
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include "import.h"
#include "ui_import.h"
#include <QFileDialog>
#include <QMessageBox>
#include "JailHouseCellList.h"
#include "readfromdump/ReadDmp.h"
#include "mainwindow.h"
#include <iostream>


Import::Import(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);
    QFont font("Plastique",10);
    //    font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);

}

Import::~Import()
{

    delete ui;
}

// Getting .info file path
void Import::on_pushButton_import_config_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Import file"), "/home","Config_Files(*.info)") ;
    ui->lineEdit_config_File->setText(filepath);
}

// Getting .dump file path
void Import::on_pushButton_import_dump_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Import file"), "/home","Dump_Files(*.dmp)") ;
    ui->lineEdit_Dump_File->setText(filepath);
}

// on event clicked create button(from import config dialog), will create a jailHousecell instance, and add to the jailHouse cellList
void Import::on_pushButton_create_imported_config_clicked()
{
    try{
        std::string info_file = ui->lineEdit_config_File->text().toStdString() ;
        std::string dump_file = ui->lineEdit_Dump_File->text().toStdString() ;
        JailHouseCellList &  JL = JailHouseCellList::getJailHouseCellList();
        ReadDmp jt(info_file,dump_file);
        JailHouseCell * jc = jt.get_cell();
        if( RootCell * j = dynamic_cast<RootCell * >(jc) )
            JL.add_rootcell_no_validation(*j);
        else
            JL.add_cell_no_validation(*jc);
    }
    catch(JailHouseCell_error & e)
    {
        std::string s = e.what();
        QMessageBox::warning(this,"Wrong input",e.what()) ;
    }
    catch(std::exception & e)
    {
        std::string s = e.what();
        QMessageBox::warning(this,"Wrong input",e.what()) ;
    }
    catch(...)
    {
        QMessageBox::warning(this,"unknownerror","unknownerror");
    }
    emit after_import();
    close_import();

}

//void Import::after_import() {
//  std::cout << "calling load_dropdownList() function" << std::endl ;
//}

// To close import dialog
void Import::close_import() {
    emit uncheck() ;
    this->close();
}

void Import::on_pushButton_4_clicked()
{
    emit uncheck() ;
    this->close();
}

void Import::closeEvent(QCloseEvent *event){
    emit uncheck();

}
