/*
 * Module consisting of Definations for all ui and non-ui actions performing on MainWindow
 * Mainwindow is the default window, when GUI starts.
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QCheckBox>
#include <iostream>
#include "MemRegion.h"
#include <sstream>
#include "PciDevice.h"
#include "IrqChip.h"
#include <stdlib.h>
#include <QStandardItemModel>
#include <QTableView>
#include "JailHouseCell.h"
#include "JailHouseCellList.h"
#include <QDebug>
#include "util.h"
#include <QMessageBox>
#include "GenConfig.h"
#include <map>
#include "Header.h"
#include <QtCore/QtCore>
using namespace std ;
int CORE ;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QFont font("Plastique",10);
    //    font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);
    ui->tabWidget_Main->setHidden(false);
    ui->tabWidget_CELL_CONFIG->setHidden(true);
    ui->tableWidget_cell_config_2->setColumnWidth(5,250);
    Disable_Root_Tabs();
    Disable_LS_Buttons();
    init_create_config();
    //    Import *temp = new Import() ;
    //    connect(temp, SIGNAL(after_import()),this, SLOT(slot_load_cell_dropdownlist()));
    imp = new Import(this) ;
    t = new Transfer(this) ;
    std::cout << "just before connect" << std::endl;
    qDebug() << connect(imp, SIGNAL(after_import()),this, SLOT(slot_load_cell_dropdownlist()));
    qDebug() << connect(imp, SIGNAL(uncheck()),this, SLOT(reset_highlight())) ;
    qDebug() << connect(t, SIGNAL(uncheck_transfer()),this, SLOT(reset_highlight())) ;

    std::cout << "just after connect" << std::endl;

}

MainWindow::~MainWindow()
{
    delete ui;

}

// on event clicked Create_config button from Main page,
// currently not in use
void MainWindow::on_pushButton_Create_Config_clicked()
{
    // cc = new Create_Config();
    //  cc->setAttribute(Qt::WA_DeleteOnClose,true);
    //  ui->widget_main->show(cc->show());
    //  cc->show();
    //      ui->pushButton_Create_Config->setStyleSheet(": tangent") ;
    //Enable_LS_Buttons();
    //ui->tabWidget_Main->setHidden(false);
    reset_highlight();
}


void MainWindow::init_create_config() {
    ui->lineEdit_NO_CELLS->setText(QString::number(2));
    load_cell_dropdownlist();
}

// on event clicked Exit button from Main page, will ask the user to close the application
void MainWindow::on_pushButton_Exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Closing Application" , "Do You want to close this Application",
                                  QMessageBox::Yes|QMessageBox::No) ;
    if (reply == QMessageBox::Yes) {
        this->close() ;
    }
}

// on event clicked Add button from Mem_config tab, will add a empty row to the Mem_config table
void MainWindow::on_pushButton_Mem_Config_Add_clicked()
{
    int rowcount = ui->lineEdit_No_Mem_Reg_2->text().toInt();
    ui->tableWidget_cell_config_2->insertRow(rowcount);
    ui->tableWidget_cell_config_2->setRowHeight(rowcount,35);

    QTableWidgetItem *itm = new QTableWidgetItem();
    itm->data(Qt::CheckStateRole);
    itm->setCheckState(Qt::Unchecked);
    ui->tableWidget_cell_config_2->setItem(rowcount,0,itm);
    QLineEdit *name = new QLineEdit(ui->tableWidget_cell_config_2) ;
    ui->tableWidget_cell_config_2->setCellWidget(rowcount,1,name);
    QLineEdit *phy_start = new QLineEdit(ui->tableWidget_cell_config_2) ;
    ui->tableWidget_cell_config_2->setCellWidget(rowcount,2,phy_start);
    QLineEdit *virt_start = new QLineEdit(ui->tableWidget_cell_config_2) ;
    ui->tableWidget_cell_config_2->setCellWidget(rowcount,3,virt_start);
    QLineEdit *size = new QLineEdit(ui->tableWidget_cell_config_2) ;
    ui->tableWidget_cell_config_2->setCellWidget(rowcount,4,size);
    QHBoxLayout *l = new QHBoxLayout();
    for (auto i : Mem_Flags) {
        QCheckBox *c = new QCheckBox(QString::fromStdString(i.first)) ;
        c->setChecked(true);
        l->addWidget (c) ;
    }
    //       l->addWidget (new QCheckBox("WR"));
    //       l->addWidget (new QCheckBox("IO"));
    //       l->addWidget (new QCheckBox("EX"));


    QWidget *w = new QWidget();
    w->setLayout(l);
    ui->tableWidget_cell_config_2->setCellWidget(rowcount,5, w);
    ++rowcount ;
    ui->lineEdit_No_Mem_Reg_2->setText(QString::number(rowcount));

}


// on event Delete button clicked from Mem_Confiq tab, will remove a last row from the Mem_Config table
void MainWindow::on_pushButton_Mem_config_Delete_clicked()
{
    int rowcount = ui->lineEdit_No_Mem_Reg_2->text().toInt() - 1 ;
    for ( int row=rowcount; row >= 0; row--) {
        std::cout << row << std::endl ;
        if (ui->tableWidget_cell_config_2->item(row,0)->checkState() == Qt::Checked)
            ui->tableWidget_cell_config_2->removeRow(row);
    }

    ui->lineEdit_No_Mem_Reg_2->setText(QString::number(ui->tableWidget_cell_config_2->rowCount()));

}


// on event Add button clicked from IRQ_chips tab, will add a empty row to the IRQ_chips table
void MainWindow::on_pushButton_IRQ_Chips_Add_clicked()
{
    int rowcount = ui->lineEdit_NO_IRQ_CHIPS_2->text().toInt() ;
    ui->tableWidget_IRQ_Chips->insertRow(rowcount);

    QTableWidgetItem *itm = new QTableWidgetItem();
    itm->data(Qt::CheckStateRole);
    itm->setCheckState(Qt::Unchecked);
    ui->tableWidget_IRQ_Chips->setItem(rowcount,0,itm);
    QLineEdit *name = new QLineEdit(ui->tableWidget_IRQ_Chips) ;
    ui->tableWidget_IRQ_Chips->setCellWidget(rowcount,1,name);
    QLineEdit *address = new QLineEdit(ui->tableWidget_IRQ_Chips) ;
    ui->tableWidget_IRQ_Chips->setCellWidget(rowcount,2,address);
    QLineEdit *pin_base = new QLineEdit(ui->tableWidget_IRQ_Chips) ;
    ui->tableWidget_IRQ_Chips->setCellWidget(rowcount,3,pin_base);
    QLineEdit *pin_bitmap = new QLineEdit(ui->tableWidget_IRQ_Chips);
    ui->tableWidget_IRQ_Chips->setCellWidget(rowcount,4,pin_bitmap);
    ++rowcount ;
    ui->lineEdit_NO_IRQ_CHIPS_2->setText(QString::number(rowcount));

}

// on event clicked Delete button, from IRQ_chips tab, will remove a last row from the IRQ_chips table
void MainWindow::on_pushButton_IRQ_Chips_Delete_clicked()
{
    int rowcount = ui->lineEdit_NO_IRQ_CHIPS_2->text().toInt() - 1 ;
    for ( int row=rowcount; row >= 0; row--) {
        std::cout << row << std::endl ;
        if (ui->tableWidget_IRQ_Chips->item(row,0)->checkState() == Qt::Checked)
            ui->tableWidget_IRQ_Chips->removeRow(row);
    }

    ui->lineEdit_NO_IRQ_CHIPS_2->setText(QString::number(ui->tableWidget_IRQ_Chips->rowCount()));
}



// on event clicked Add button from PCI_devices tab, will add a empty row to the PCI_device table
void MainWindow::on_pushButton_PCI_Devices_Add_clicked()
{
    int rowcount = ui->lineEdit_NO_OF_PCI_DEV_2->text().toInt() ;
    ui->tableWidget_PCI_Devices->insertRow(rowcount);

    QTableWidgetItem *itm = new QTableWidgetItem();
    itm->data(Qt::CheckStateRole);
    itm->setCheckState(Qt::Unchecked);
    ui->tableWidget_PCI_Devices->setItem(rowcount,0,itm);
    QLineEdit *name = new QLineEdit(ui->tableWidget_PCI_Devices) ;
    ui->tableWidget_PCI_Devices->setCellWidget(rowcount,1,name);
    QLineEdit *type = new QLineEdit(ui->tableWidget_PCI_Devices) ;
    ui->tableWidget_PCI_Devices->setCellWidget(rowcount,2,type);
    QLineEdit *bdf = new QLineEdit(ui->tableWidget_PCI_Devices) ;
    ui->tableWidget_PCI_Devices->setCellWidget(rowcount,3,bdf);
    QLineEdit *bar_mask = new QLineEdit(ui->tableWidget_PCI_Devices) ;
    ui->tableWidget_PCI_Devices->setCellWidget(rowcount,4,bar_mask);
    QLineEdit *shm_region = new QLineEdit(ui->tableWidget_PCI_Devices) ;
    ui->tableWidget_PCI_Devices->setCellWidget(rowcount,5,shm_region);
    QLineEdit *shm_protocol = new QLineEdit(ui->tableWidget_PCI_Devices) ;
    ui->tableWidget_PCI_Devices->setCellWidget(rowcount,6,shm_protocol);
    ++rowcount ;
    ui->lineEdit_NO_OF_PCI_DEV_2->setText(QString::number(rowcount));

}


// on event clicked Delete button fromm PCI_devices tab, will remove a last row from the pci device table
void MainWindow::on_pushButton_PCI_Devices_Delete_clicked()
{
//        int rowcount = ui->lineEdit_NO_OF_PCI_DEV_2->text().toInt() ;
//        if (rowcount > 0) {
//            --rowcount ;
//            ui->tableWidget_PCI_Devices->removeRow(rowcount);
//            ui->lineEdit_NO_OF_PCI_DEV_2->setText(QString::number(rowcount));
    //        }
    std::cout << "pci devices rows:" << std::endl ;
    int rowcount = ui->lineEdit_NO_OF_PCI_DEV_2->text().toInt() - 1 ;
    for ( int row=rowcount; row >= 0; row--) {
        std::cout << row << std::endl ;
        if (ui->tableWidget_PCI_Devices->item(row,0)->checkState() == Qt::Checked)
            ui->tableWidget_PCI_Devices->removeRow(row);
    }

    ui->lineEdit_NO_OF_PCI_DEV_2->setText(QString::number(ui->tableWidget_PCI_Devices->rowCount()));

}



// on event clicked Bootfile button from Cell_config tab, will open a filedialog to read file path
void MainWindow::on_pushButton_Bootfile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Boot file"), "/home","ALL Files(*.*)") ;
    ui->lineEdit_Bootfil_Path->setText(filepath);
}


//  on event editing finished HyperVisor memory size, To get size in hex
void MainWindow::on_lineEdit_HM_size_editingFinished()
{
    unsigned long  value = ui->lineEdit_HM_size->text().toULong();
    QString result = "0x" + QString::number(value, 16);
    ui->lineEdit_Size_Hex_Value_HM->setText(result);
}


/*
void MainWindow::on_lineEdit_HM_size_returnPressed()
{
    unsigned long  value = ui->lineEdit_HM_size->text().toULong();
    QString result = "0x" + QString::number(value, 16);
    ui->lineEdit_Size_Hex_Value_HM->setText(result);
}
*/

//  on event editing finished Debug_Console size, To get size in hex
void MainWindow::on_lineEdit_Size_DC_editingFinished()
{
    unsigned long  value = ui->lineEdit_Size_DC->text().toULong();
    QString result = "0x" + QString::number(value, 16);
    ui->lineEdit_Size_Hex_value_DC->setText(result);
}


/*
void MainWindow::on_lineEdit_Size_DC_returnPressed()
{
    unsigned long  value = ui->lineEdit_Size_DC->text().toULong();
    QString result = "0x" + QString::number(value, 16);
    ui->lineEdit_Size_Hex_value_DC->setText(result);
}
*/


// on event clicked View_Configuration button, allow user to view current configurations.
void MainWindow::on_pushButton_View_Configuration_clicked()
{
    int rowcount = 50 ;
    //    int rowcount = ui->lineEdit_No_Mem_Reg_2->text().toInt() ;
    set_highlight(ui->pushButton_View_Configuration->text());
    QStandardItemModel *model = new QStandardItemModel(rowcount,5,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("CELL")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("CPU")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("MEM REGIONS")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("PCI DEVICES")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("IRQ CHIPS")));
    //model->horizontalHeaderItem(2)->setText("Apple");
    view->setModel(model);
    QRect rect = QRect(20,20,800,600) ;
    view->setGeometry(rect);

    for (int i = 0; i < 5; i++)
        view->setColumnWidth(i,200);

    JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
    int cellcount = JL.get_number_of_cells() + 1;

    if (cellcount != 0) {
        //   for (int i = 0; i < cellcount; i++) ;
        //  QLineEdit *temp ;
        //   temp = qobject_cast<QLineEdit*>(ui->tableWidget_cell_config_2->cellWidget(0,0));
        //   string s =  temp->text().toUtf8().constData();

        int cell_row=0 , cpu_row=0 , mem_row=0, pci_row = 0, irq_row = 0;
        //  QString color[3] = {"red" , "green", "blue"} ;
        // JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
        std::vector<Qt::GlobalColor> color = {Qt::red, Qt::gray, Qt::cyan, Qt::green, Qt::yellow, Qt::blue};
        auto cell_itr = JL.get_JailHouseCellItr_begin() ;
        int root_done = 0;

        while(cell_itr != JL.get_JailHouseCellItr_end() || (root_done == 0) )
        {
            JailHouseCell cell;
            if(root_done == 0)
            {
                cell = JL.get_rootcell();
                root_done = 1;
            }
            else
            {
                cell = cell_itr->second;
                ++cell_itr;
            }
            auto cell_name = cell.get_name();
            QString q = QString::fromLocal8Bit(cell_name.c_str());
            cout << cell_name ;
            //      cout << q ;
            //autget_cpuIdso cell_info = (cell_itr->second);

            auto item = new QStandardItem(q);
            item->setTextAlignment(Qt::AlignCenter);

            //         item->setForeground(Qt::red);

            item->setBackground(color[cell_row]);
            model->setItem(cell_row,0,item);

            auto cpu_ids =  cell.get_cpuIds();
            int cpu_id = 0;
            for(auto val : cpu_ids )
            {
                if (val)
                {
                    QString qcpuid = QString::number(cpu_id) ;
                    auto item = new QStandardItem(qcpuid);
                    item->setTextAlignment(Qt::AlignCenter);
                    //         item->setForeground(Qt::red);
                    item->setBackground(color[cell_row]);
                    model->setItem(cpu_row,1,item);
                    ++cpu_row ;
                }
                ++cpu_id;
            }
            /*
         for(auto & cpu_id : cpu_ids)
         {
             QString qcpuid = QString::number(cpu_id) ;

             auto item = new QStandardItem(qcpuid);
             item->setTextAlignment(Qt::AlignCenter);

             //         item->setForeground(Qt::red);

             item->setBackground(color[cell_row]);
             model->setItem(cpu_row,1,item);
             ++cpu_row ;
         }
       */
            for( auto mem_itr = cell.get_memRegionItr_begin();
                 mem_itr != cell.get_memRegionItr_end();
                 ++mem_itr,++mem_row)
            {

                auto mem_name = (mem_itr->second).get_name();
                QString q = QString::fromLocal8Bit(mem_name.c_str());
                ;
                auto item = new QStandardItem(q);
                item->setTextAlignment(Qt::AlignCenter);

                // item->setForeground(Qt::red);

                item->setBackground(color[cell_row]);
                model->setItem(mem_row,2,item);

            }

            for( auto pci_itr = cell.get_pciDeviceItr_begin();
                 pci_itr != cell.get_pciDeviceItr_end();
                 ++pci_itr,++pci_row)
            {
                auto mem_name = (pci_itr->second).get_name();
                QString q = QString::fromLocal8Bit(mem_name.c_str());

                auto item = new QStandardItem(q);
                item->setTextAlignment(Qt::AlignCenter);

                //         item->setForeground(Qt::red);

                item->setBackground(color[cell_row]);
                model->setItem(pci_row,3,item);


            for( auto irq_itr = cell.get_irqChipItr_begin();
                 irq_itr != cell.get_irqChipItr_end();
                 ++irq_itr,++irq_row)
            {

                auto mem_name = (irq_itr->second).get_name();
                QString q = QString::fromLocal8Bit(mem_name.c_str());

                auto item = new QStandardItem(q);
                item->setTextAlignment(Qt::AlignCenter);

                //         item->setForeground(Qt::red);

                item->setBackground(color[cell_row]);
                model->setItem(irq_row,4,item);


            }
            ++cell_row;
        }
        view->show();
    }
    }
    else {
        QMessageBox::warning(this,"View Configurations", "Configured Cell List is empty") ;
    }
}

// creating a Non-root JailHousecell instance
JailHouseCell MainWindow::create_cell()
{
    QString cell_name = ui->lineEdit_CellName->text() ;
    QString signature = ui->lineEdit_Signature->text() ;
    QString revision = ui->lineEdit_Revision->text() ;
    int vpci_irq_base = ui->lineEdit_Vpci_irq_base->text().toInt() ;
    JailHouseCell j1(cell_name.toStdString() );

    //int cpucount = ui->lineEdit_No_Of_CPU->text().toInt() ;

    QList<QCheckBox *> allButtons = ui->groupBox_CPU_Allocation->findChildren<QCheckBox *>();
    qDebug() << allButtons.size();
    vector<bool> cpuid_vec(CORE);
    for(int i = 0; i < CORE; ++i)
    {
        if(ui->listWidget_CPUs->item(i)->checkState() == Qt::Checked)
            cpuid_vec[i]=true;
        else
            cpuid_vec[i]=false;
    }

    QList<QCheckBox *> temp_flags = ui->groupBox_Flags_NonRootCell->findChildren<QCheckBox *>();
    qDebug() <<temp_flags.size();
    vector<std::string> cell_flags;
    for(int i = 0; i < temp_flags.size(); ++i)
    {
        if(temp_flags.at(i)->isChecked())
            cell_flags.push_back(Cell_Desc_Flags[i]);

    }


    j1.set_cpuIds(cpuid_vec);
    j1.set_signature(signature.toStdString());
    j1.set_revision(revision.toStdString());
    j1.set_vpci_irq_base(vpci_irq_base);
    j1.set_flags(cell_flags);

    return j1;

}

// creating a Root cell instance
RootCell MainWindow::create_root_cell ()
{
    QString cell_name = ui->lineEdit_CellName->text() ;
    QString signature = ui->lineEdit_Signature->text() ;
    QString revision = ui->lineEdit_Revision->text() ;
    int vpci_irq_base = ui->lineEdit_Vpci_irq_base->text().toInt() ;
    RootCell j1(cell_name.toStdString() );

    //int cpucount = ui->lineEdit_No_Of_CPU->text().toInt() ;

    qDebug() << CORE;
    vector<bool> cpuid_vec(CORE);
    for(int i = 0; i < CORE; ++i)
    {
        if(ui->listWidget_CPUs->item(i)->checkState() == Qt::Checked)
            cpuid_vec[i]=true;
        else
            cpuid_vec[i]=false;
    }

    j1.set_cpuIds(cpuid_vec);
    j1.set_signature(signature.toStdString());
    j1.set_revision(revision.toStdString());
    j1.set_vpci_irq_base(vpci_irq_base);

    // read other tabs and save in RootCell
    return j1;

}


//  on event clicked Create button, To create a cell and add to the cell list.
void MainWindow::on_pushButton_Create_clicked()
{

    try{
        QString name = ui->comboBox_CellList->currentText() ;
        if(name != "root_cell")
        {
            JailHouseCell j = create_cell();
            add_mem(j);
            add_irq(j);
            add_pci(j);
            JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
            try
            {
                JL.add_cell(j);
                //               JailHouseCellList &JL = JailHouseCellList::getJailHouseCellList() ;
                if (JL.Is_In_List(j.get_name())) {
                    //                   ui->tabWidget_CELL_CONFIG->setHidden(false);
                    ui->pushButton_Create->setEnabled(false);
                    ui->pushButton_Update->setEnabled(true);
                    ui->pushButton_Destroy->setEnabled(true);
                }
                load_cell(j.get_name());
                load_cell_dropdownlist(j.get_name());
            }
            catch(J_error & e)
            {
                string s = e.what();
                QMessageBox::warning(this,"Wrong input",e.what()) ;
                throw;
            }
        }
        else
        {
            RootCell r = create_root_cell();
            add_Hypervisor_Memory(r);
            add_Debug_Console(r);
            add_Platform_Info(r);
            add_mem(r);
            add_irq(r);
            add_pci(r);
            JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
            try
            {
                JL.add_rootcell(r);
                ui->pushButton_Update->setEnabled(true);
                ui->pushButton_Destroy->setEnabled(true);
                load_cell("root_cell") ;
                //        load_cell(r.get_name());
                //        load_cell_dropdownlist();
            }
            catch(J_error & e)
            {
                string s = e.what();
                QMessageBox::warning(this,"Wrong input",e.what()) ;
                throw;
            }

        }
    }
    catch (...)
    {
        std::cout << "exception happned at  MainWindow::on_pushButton_Create_clicked() \ns";
    }

}


// To Add memory regions to the cell
void MainWindow::add_mem(JailHouseCell &j)
{
    try {
        //   std::vector<string> FLAGS = {"JAILHOUSE_MEM_READ","JAILHOUSE_MEM_WRITE","JAILHOUSE_MEM_IO","JAILHOUSE_MEM_EXECUTE"} ;
        int memcount = ui->lineEdit_No_Mem_Reg_2->text().toInt();
        for ( int i =0; i < memcount; i++ ){
            QLineEdit *temp ;
            temp = qobject_cast<QLineEdit*>(ui->tableWidget_cell_config_2->cellWidget(i,1));
            string name =  temp->text().toUtf8().constData();
            temp = qobject_cast<QLineEdit*>(ui->tableWidget_cell_config_2->cellWidget(i,2));
            string phy_start =  temp->text().toUtf8().constData();
            temp = qobject_cast<QLineEdit*>(ui->tableWidget_cell_config_2->cellWidget(i,3));
            string virt_start =  temp->text().toUtf8().constData();
            temp = qobject_cast<QLineEdit*>(ui->tableWidget_cell_config_2->cellWidget(i,4));
            string size =  temp->text().toUtf8().constData();
            QWidget *item = ( ui->tableWidget_cell_config_2->cellWidget(i,5));
            // Taking the widget from the layout and cast it to QCheckBox
            std::vector<string> flags ;
            for (int j = 0; j < 4; j++ ) {
                QCheckBox *checkB = qobject_cast <QCheckBox*> (item->layout()->itemAt(j)->widget());
                if(checkB->isChecked()){
                    flags.push_back(Mem_Flags[(checkB->text()).toStdString()]);
                }
            }

            MemRegion m (name,strtoull(phy_start.c_str(),NULL,0),strtoll(virt_start.c_str(),NULL,0),
                         strtoull(size.c_str(),NULL,0), flags) ;

            cout << name << endl << phy_start << endl << virt_start << endl << size << endl ;//<< flags << endl ;
            j.add_memRegion(m);

        }
    }
    catch (J_error &e)
    {
        string s = e.what();
        QMessageBox::warning(this,"Wrong input",e.what()) ;
        throw;
    }
}


// To add irq_chips to the cell
void MainWindow::add_irq(JailHouseCell &j)
{
    try {

        int irqcount = ui->lineEdit_NO_IRQ_CHIPS_2->text().toInt() ;

        for (int i = 0; i < irqcount; i++) {

            QLineEdit *temp ;
            temp = qobject_cast<QLineEdit*>(ui->tableWidget_IRQ_Chips->cellWidget(i,1));
            string name =  temp->text().toUtf8().constData();


            temp = qobject_cast<QLineEdit*>(ui->tableWidget_IRQ_Chips->cellWidget(i,2));
            string address =  temp->text().toUtf8().constData();


            temp = qobject_cast<QLineEdit*>(ui->tableWidget_IRQ_Chips->cellWidget(i,3));
            string pin_base =  temp->text().toUtf8().constData();

            temp = qobject_cast<QLineEdit*>(ui->tableWidget_IRQ_Chips->cellWidget(i,4));
            string pin_bitmap =  temp->text().toUtf8().constData();

            IrqChip irq (name, strtoull(address.c_str(),NULL,0),strtoull(pin_base.c_str(),NULL,0),
                         strToUllvec(pin_bitmap) ) ;
            j.add_irqChip(irq);


        }
    }
    catch (J_error &e)
    {
        string s = e.what();
        QMessageBox::warning(this,"Wrong input",e.what()) ;
        throw;
    }

}

// To add PCI_devices to the cell
void MainWindow::add_pci(JailHouseCell &j)
{
    try {

        int pcicount = ui->lineEdit_NO_OF_PCI_DEV_2->text().toInt() ;

        for (int i = 0; i < pcicount; i++) {
            QLineEdit *temp ;
            temp = qobject_cast<QLineEdit*>(ui->tableWidget_PCI_Devices->cellWidget(i,1));
            string name =  temp->text().toUtf8().constData();

            temp = qobject_cast<QLineEdit*>(ui->tableWidget_PCI_Devices->cellWidget(i,2));
            string type =  temp->text().toUtf8().constData();

            temp = qobject_cast<QLineEdit*>(ui->tableWidget_PCI_Devices->cellWidget(i,3));
            string bdf =  temp->text().toUtf8().constData();

            temp = qobject_cast<QLineEdit*>(ui->tableWidget_PCI_Devices->cellWidget(i,4));
            string bar_mask =  temp->text().toUtf8().constData();

            temp = qobject_cast<QLineEdit*>(ui->tableWidget_PCI_Devices->cellWidget(i,5));
            string shm_reg =  temp->text().toUtf8().constData();

            temp = qobject_cast<QLineEdit*>(ui->tableWidget_PCI_Devices->cellWidget(i,6));
            string shm_protocol =  temp->text().toUtf8().constData();

            PciDevice pci(name,type,(unsigned int)strtoul(bdf.c_str(),NULL,0),strToUllvec(bar_mask),
                          atoi(shm_reg.c_str()),shm_protocol) ;

            j.add_pci(pci);


        }

    }
    catch (J_error &e)
    {
        string s = e.what();
        QMessageBox::warning(this,"Wrong input",e.what()) ;
        throw;
    }

}

/*
void MainWindow::on_lineEdit_NO_CELLS_editingFinished()
{
    ui->comboBox_CellList->clear();
    int cellcount = ui->lineEdit_NO_CELLS->text().toInt() ;
    ui->comboBox_CellList->addItem("Root");
    for (int i = i; i < cellcount; i++)
        ui->comboBox_CellList->addItem("CELL" + QString::number(i));
}
*/


// on event pressed enter button on editing No. of cells from Cell_config tab, To load cell dropdown list
void MainWindow::on_lineEdit_NO_CELLS_returnPressed()
{
    JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
    ui->comboBox_CellList->clear();
    int cellcount = ui->lineEdit_NO_CELLS->text().toInt() ;
    if (cellcount > JL.get_number_of_cells())
        load_cell_dropdownlist();
    else {
        QMessageBox::warning(this, "Wrong Input", "No. of cells should be more than no. of allocated cells") ;
        ui->lineEdit_NO_CELLS->setText(QString::number(JL.get_number_of_cells() + 1));
    }
}


// on event selecting a cell from Cell list, To load particular cell configuration choosen from cell dropdown list
void MainWindow::on_comboBox_CellList_activated(QString index)
{
    Enable_LS_Buttons();
    JailHouseCellList &JL = JailHouseCellList::getJailHouseCellList() ;
    if (index != "root_cell") {
        Disable_Root_Tabs();
        if (JL.Is_In_List(index.toStdString())) {
            ui->tabWidget_CELL_CONFIG->setHidden(false);
            ui->pushButton_Create->setEnabled(false);
            ui->pushButton_Update->setEnabled(true);
            ui->pushButton_Destroy->setEnabled(true);

            //     JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
            load_cell(index.toStdString());
        }
        else {
            ui->tabWidget_CELL_CONFIG->setHidden(false) ;
            ui->pushButton_Create->setEnabled(true);
            ui->pushButton_Update->setEnabled(false);
            ui->pushButton_Destroy->setEnabled(false);
            load_Empty_cell();

        }
    }
    else {
        Enable_Root_Tabs();
        ui->tabWidget_CELL_CONFIG->setHidden(false) ;
        ui->pushButton_Create->setEnabled(false);
        ui->pushButton_Update->setEnabled(true);
        load_cell("root_cell") ;
    }


}


// To Load a cell_Configuration into GUI by taking cell name as reference
void MainWindow::load_cell(std::string cell_name)
{

    JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();

    if(cell_name == "root_cell")
    {
        auto cell = JL.get_rootcell();
        ui->lineEdit_CellName->setText(cell.get_name().c_str());
        ui->lineEdit_Signature->setText(cell.get_signature().c_str());
        ui->lineEdit_Revision->setText(cell.get_revision().c_str());
        ui->lineEdit_Vpci_irq_base->setText(QString::number(cell.get_vpci_irq_base()));
        auto cpu_alloc = cell.get_cpuIds() ;
        //        int size = cpu_alloc.size() ;
        QList<QCheckBox *> allButtons = ui->groupBox_CPU_Allocation->findChildren<QCheckBox *>();
        ui->listWidget_CPUs->item(0)->setCheckState(Qt::Checked);
        ui->listWidget_CPUs->item(0)->setHidden(false);
        for(int i = 1; i < CORE; ++i)
        {
            if(cpu_alloc[i])
                ui->listWidget_CPUs->item(i)->setCheckState(Qt::Checked);
            else
                ui->listWidget_CPUs->item(i)->setCheckState(Qt::Unchecked);
        }

        load_Hypervisor_Memory(cell);
        load_Debug_Console(cell);
        load_Platform_Info(cell);
        load_mem(cell);
        load_irq(cell);
        load_pci(cell);
        return;
    }
    else
    {
        for(auto cell_itr = JL.get_JailHouseCellItr_begin();
            cell_itr != JL.get_JailHouseCellItr_end(); ++cell_itr)
        {
            if(cell_name == cell_itr->first)
            {
                JailHouseCell cell = (cell_itr)->second;
                ui->lineEdit_CellName->setText(cell.get_name().c_str());
                ui->lineEdit_Signature->setText(cell.get_signature().c_str());
                ui->lineEdit_Revision->setText(cell.get_revision().c_str());
                ui->lineEdit_Vpci_irq_base->setText(QString::number(cell.get_vpci_irq_base()));
                auto cpu_alloc = cell.get_cpuIds() ;
                QList<QCheckBox *> allButtons = ui->groupBox_CPU_Allocation->findChildren<QCheckBox *>();
                ui->listWidget_CPUs->item(0)->setCheckState(Qt::Unchecked);
                ui->listWidget_CPUs->item(0)->setHidden(true);
                for(int i = 1; i < CORE; ++i)
                {
                    if(cpu_alloc[i])
                        ui->listWidget_CPUs->item(i)->setCheckState(Qt::Checked);
                    else
                        ui->listWidget_CPUs->item(i)->setCheckState(Qt::Unchecked);
                }


                auto flags = cell.get_flags() ;
                QList<QCheckBox *> temp_flags = ui->groupBox_Flags_NonRootCell->findChildren<QCheckBox *>();
                for(int i = 0; i < temp_flags.size(); ++i)
                {
                    if( std::find(flags.begin(), flags.end(), Cell_Desc_Flags[i]) != flags.end() )

                        //               allButtons.at(i)->setChecked(true);
                        ui->groupBox_Flags_NonRootCell->findChildren<QCheckBox *>().at(i)->setChecked(true);
                    else
                        //               allButtons.at(i)->setChecked(false);
                        ui->groupBox_Flags_NonRootCell->findChildren<QCheckBox *>().at(i)->setChecked(false);
                }


                load_mem(cell);
                load_irq(cell);
                load_pci(cell);
                return;
            }
        }
    }
    //load default values

}


//  To Load a cell_Configuration into GUI by taking cell index as reference
void MainWindow::load_cell(int index)
{
    ui->pushButton_Create->setDisabled(true);
    //   clear_cpu_config() ;
    JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
    auto JList_itr = JL.get_JailHouseCellItr_begin();
    std::advance(JList_itr , index) ;
    JailHouseCell cell = (JList_itr)->second;
    ui->lineEdit_CellName->setText(cell.get_name().c_str());
    load_mem(cell);
    //   load_irq(cell);
    //   load_pci(cell);

}

void MainWindow::load_Empty_cell() {

    ui->lineEdit_CellName->setText("");
    ui->lineEdit_Signature->setText("");
    ui->lineEdit_Revision->setText("");
    ui->lineEdit_Vpci_irq_base->setText("");
    ui->listWidget_CPUs->item(0)->setHidden(true);
    for(int i = 1; i < CORE; ++i)
    {
        ui->listWidget_CPUs->item(i)->setCheckState(Qt::Unchecked);
    }
    ui->tableWidget_cell_config_2->setRowCount(0);
    ui->lineEdit_No_Mem_Reg_2->setText(QString::number(ui->tableWidget_cell_config_2->rowCount()));
    ui->tableWidget_IRQ_Chips->setRowCount(0);
    ui->lineEdit_NO_IRQ_CHIPS_2->setText(QString::number(ui->tableWidget_IRQ_Chips->rowCount()));
    ui->tableWidget_PCI_Devices->setRowCount(0);
    ui->lineEdit_NO_OF_PCI_DEV_2->setText(QString::number(ui->tableWidget_PCI_Devices->rowCount()));

}


// To upload memory regions into GUI,by taking cell as reference
void MainWindow::load_mem(JailHouseCell &j) {

    int rowcount = j.get_mem_Regioncount() ;                     //uploading memory regions to mem_config table
    ui->lineEdit_No_Mem_Reg_2->setText(QString::number(rowcount));
    ui->tableWidget_cell_config_2->setRowCount(rowcount);
    int row = 0;
    for ( auto mem_itr = j.get_memRegionItr_begin();
          mem_itr != j.get_memRegionItr_end(); ++mem_itr, ++row)
    {
        MemRegion memRegion = mem_itr->second;
        QTableWidgetItem *itm = new QTableWidgetItem();
        itm->data(Qt::CheckStateRole);
        itm->setCheckState(Qt::Unchecked);
        ui->tableWidget_cell_config_2->setItem(row,0,itm);
        QLineEdit *name = new QLineEdit(ui->tableWidget_cell_config_2) ;
        name->setText(memRegion.get_name().c_str());
        ui->tableWidget_cell_config_2->setCellWidget(row,1,name);
        QLineEdit *phy_start = new QLineEdit(ui->tableWidget_cell_config_2) ;
        std::stringstream stream;
        stream << std::hex << memRegion.get_phys_start();
        //        QString li = QString::number(memRegion.get_phys_start(),16) ;
        //        phy_start->setText(li);
        //        phy_start->setText(stream.str().c_str());
        QString s = stream.str().c_str() ;
        phy_start->setText("0x" + s) ;

        ui->tableWidget_cell_config_2->setCellWidget(row,2,phy_start);
        QLineEdit *virt_start = new QLineEdit(ui->tableWidget_cell_config_2) ;
        std::stringstream stream1 ;
        stream1 << std::hex << memRegion.get_virt_start();
        s = stream1.str().c_str() ;

        virt_start->setText("0x" + s);

        ui->tableWidget_cell_config_2->setCellWidget(row,3,virt_start);
        // QCheckBox *flag = new QCheckBox(ui->tableWidget_cell_config_2);
        //   ui->tableWidget_cell_config_2->setCellWidget(row,3,flag);

        QLineEdit *size = new QLineEdit(ui->tableWidget_cell_config_2) ;
        std::stringstream stream2 ;
        stream2 << std::hex << memRegion.get_size();
        s = stream2.str().c_str() ;
        size->setText("0x" + s);
        ui->tableWidget_cell_config_2->setCellWidget(row,4,size);

        //  for (int i =0; i<2; i++) {
        auto mem_flags = memRegion.get_flags();
        QHBoxLayout *l = new QHBoxLayout();
        for (auto i : Mem_Flags) {
            QCheckBox *cb = new QCheckBox( QString::fromStdString(i.first) ) ;
            if( std::find(mem_flags.begin(), mem_flags.end(), i.second) != mem_flags.end() )
            {
                cb->setChecked(true);
            }
            else
            {
                cb->setChecked(false);
            }
            // std::string find (&Mem_Flags ,)

            l->addWidget (cb);

        }
        QWidget *w = new QWidget();

        w->setLayout(l);

        ui->tableWidget_cell_config_2->setCellWidget(row,5, w);
        //  }

        /*            for (int i = 0; i< 2; i++) {
            cout << "inside for loop" << endl ;
            QCheckBox *flag = new QCheckBox(ui->tableWidget_cell_config_2);

            QRect rect = QRect(360*i,130,21,22) ;
            flag->setGeometry(rect);

            ui->tableWidget_cell_config_2->setCellWidget(row,3,flag);

            //flag->setGeometry(360+i*10,130+i*10,21,22);

        }
*/
        // ui->tableWidget_cell_config_2->insertRow(1);
    }


}


// To upload IRQ_chips into GUI, by taking cell as reference
void MainWindow::load_irq(JailHouseCell &j) {

    int rowcount = j.get_irqcount() ;                     // uploading IRQ_chips to IRQ_chips table
    ui->lineEdit_NO_IRQ_CHIPS_2->setText(QString::number(rowcount));
    ui->tableWidget_IRQ_Chips->setRowCount(rowcount);
    int row = 0;
    for ( auto irq_itr = j.get_irqChipItr_begin();
          irq_itr != j.get_irqChipItr_end(); ++irq_itr,++row)
    {
        IrqChip irqchip = irq_itr->second ;
        QTableWidgetItem *itm = new QTableWidgetItem();
        itm->data(Qt::CheckStateRole);
        itm->setCheckState(Qt::Unchecked);
        ui->tableWidget_IRQ_Chips->setItem(row,0,itm);
        QLineEdit *name = new QLineEdit(ui->tableWidget_IRQ_Chips) ;
        name->setText(irqchip.get_name().c_str());
        ui->tableWidget_IRQ_Chips->setCellWidget(row,1,name);
        QLineEdit *address = new QLineEdit(ui->tableWidget_IRQ_Chips) ;
        stringstream s1 ;
        s1 << std::hex << irqchip.get_address();
        QString xx  = s1.str().c_str();
        //        xx = QString::number((irqchip.get_address() ), 16) ;
        address->setText(xx);
        ui->tableWidget_IRQ_Chips->setCellWidget(row,2,address);
        QLineEdit *pin_base = new QLineEdit(ui->tableWidget_IRQ_Chips) ;
        stringstream s2 ;
        s2 << std::hex << irqchip.get_pin_base() ;
        //        xx = QString::number((irqchip.get_pin_base() ), 16) ;
        xx = s2.str().c_str() ;
        pin_base->setText(xx);
        ui->tableWidget_IRQ_Chips->setCellWidget(row,3,pin_base);
        QLineEdit *pin_bitmap = new QLineEdit(ui->tableWidget_IRQ_Chips);
        auto bm_vector = irqchip.get_pin_bitmap();
        auto bm_str = string_from_long_vec(bm_vector,",");
        QString c = QString::fromLocal8Bit(bm_str.c_str());
        pin_bitmap->setText(c);
        ui->tableWidget_IRQ_Chips->setCellWidget(row,4,pin_bitmap);
    }

}


// uploading pci_devices to pci_device table
void MainWindow::load_pci(JailHouseCell &j) {

    int rowcount = j.get_pcicount() ;
    ui->lineEdit_NO_OF_PCI_DEV_2->setText(QString::number(rowcount));
    ui->tableWidget_PCI_Devices->setRowCount(rowcount);
    //  for (int row = 0; row < rowcount; row++) {
    int row = 0;
    for ( auto pci_itr = j.get_pciDeviceItr_begin();
          pci_itr != j.get_pciDeviceItr_end(); ++pci_itr, ++row)  {
        PciDevice pci = pci_itr->second ;
        QTableWidgetItem *itm = new QTableWidgetItem();
        itm->data(Qt::CheckStateRole);
        itm->setCheckState(Qt::Unchecked);
        ui->tableWidget_PCI_Devices->setItem(row,0,itm);
        QLineEdit *name = new QLineEdit(ui->tableWidget_PCI_Devices) ;
        name->setText(pci.get_name().c_str());
        ui->tableWidget_PCI_Devices->setCellWidget(row,1,name);
        QLineEdit *type = new QLineEdit(ui->tableWidget_PCI_Devices) ;
        type->setText(pci.get_type().c_str());
        ui->tableWidget_PCI_Devices->setCellWidget(row,2,type);
        QLineEdit *bdf = new QLineEdit(ui->tableWidget_PCI_Devices) ;
        stringstream buff ;
        //buff = QString::number(pci_vec[row].get_bdf() , 10) ;
        buff << "0x" << std::hex << pci.get_bdf() ;
        bdf->setText(buff.str().c_str());
        ui->tableWidget_PCI_Devices->setCellWidget(row,3,bdf);
        QLineEdit *bar_mask = new QLineEdit(ui->tableWidget_PCI_Devices) ;
        auto bm_vector = pci.get_bar_mask();
        /* auto bm_str = std::accumulate(std::next(bm_vector.begin()), bm_vector.end(),
                                      std::to_string(bm_vector[0]),
                                      [](std::string a, unsigned long long b)
                                        { return a +','+ std::to_string(b);});
        */
        auto bm_str = string_from_long_vec(bm_vector,",");
        cout << '\n' << bm_str<< '\n';
        QString c = QString::fromLocal8Bit(bm_str.c_str()); ;
        //cout << '\n' << c << '\n';


        bar_mask->setText(c);
        ui->tableWidget_PCI_Devices->setCellWidget(row,4,bar_mask);
        QLineEdit *shm_region = new QLineEdit(ui->tableWidget_PCI_Devices) ;
        //             buff << std::uint64_t << pci_vec[row].get_shmem_region() ;
        stringstream s ;
        s <<  pci.get_shmem_region() ;
        QString xx = s.str().c_str(); ;
        //        xx = QString::number((pci.get_shmem_region() ), 16) ;
        shm_region->setText(xx);
        ui->tableWidget_PCI_Devices->setCellWidget(row,5,shm_region);
        QLineEdit *shm_protocol = new QLineEdit(ui->tableWidget_PCI_Devices) ;
        shm_protocol->setText(pci.get_shmem_protocol().c_str());
        ui->tableWidget_PCI_Devices->setCellWidget(row,6,shm_protocol);
    }
}


// on event clicked update button.
void MainWindow::on_pushButton_Update_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Updating New Changes" , "This will Make Changes to Cell " + ui->comboBox_CellList->currentText(),
                                  QMessageBox::Yes|QMessageBox::No) ;
    if (reply == QMessageBox::Yes) {
        JailHouseCellList &JL = JailHouseCellList::getJailHouseCellList() ;
        QString name = ui->comboBox_CellList->currentText() ;
        if  ( name != "root_cell") {

            try{
                JailHouseCell j = create_cell();
                add_irq(j);
                add_mem(j);
                add_pci(j);
                // validation is needed will add later
                JL.validate_cell(j);
                JL.delete_cell(name.toStdString());
                JL.add_cell(j);
                load_cell(j.get_name());
                load_cell_dropdownlist(j.get_name());

            }
            catch(J_error & e)
            {
                string s = e.what();
                QMessageBox::warning(this,"Wrong input",e.what()) ;
                throw;
            }
        }
        else {
            try{
                RootCell j = create_root_cell();
                add_Hypervisor_Memory(j);
                add_Debug_Console(j);
                add_Platform_Info(j);
                add_irq(j);
                add_mem(j);
                add_pci(j);
                // validation is needed will add later
                JL.validate_cell(j);
                JL.add_cell(j);
                load_cell("root_cell");
                //               load_cell_dropdownlist(j.get_name());

            }
            catch(J_error & e)
            {
                string s = e.what();
                QMessageBox::warning(this,"Wrong input",e.what()) ;
            }
        }
    }
}


// on event clicke Destroy button
void MainWindow::on_pushButton_Destroy_clicked()
{
    JailHouseCellList &JL = JailHouseCellList::getJailHouseCellList() ;
    QString name = ui->comboBox_CellList->currentText() ;

    if ( name == "root_cell") {
        QMessageBox::warning(this , "Destroying a root_cell" , "Cannot Destroy a root_cell") ;
    } else {

        JL.delete_cell(name.toStdString());
//        int index = ui->comboBox_CellList->currentIndex() ;
//        ui->comboBox_CellList->removeItem(index);
        //    int newcell_count = ui->lineEdit_NO_CELLS->text().toInt() - 1 ;
        //    ui->lineEdit_NO_CELLS->setText(QString::number(newcell_count));
        load_cell_dropdownlist();
    }
}

// Enabling Root tabs
void MainWindow::Enable_Root_Tabs() {
    for (int i = 1; i < 4; i++)
        ui->tabWidget_Main->setTabEnabled(i,true);

}

// Disabling Root tabs
void MainWindow::Disable_Root_Tabs() {

    for (int i = 1; i < 4; i++)
        ui->tabWidget_Main->setTabEnabled(i , false);
}

// To clear content of Cell config tab
void MainWindow::clear_cpu_config() {
    ui->lineEdit_CellName->clear();
    ui->tableWidget_cell_config_2->clearContents();
    ui->lineEdit_No_Mem_Reg_2->clear();
    ui->tableWidget_IRQ_Chips->clearContents();
    ui->lineEdit_NO_IRQ_CHIPS_2->clear();
    ui->tableWidget_PCI_Devices->clearContents();
    ui->lineEdit_NO_OF_PCI_DEV_2->clear();
}


// To load the cell dropdown list with the latest configurations with no arguments
void MainWindow::load_cell_dropdownlist () {

    JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
    auto itr_cell = JL.get_JailHouseCellItr_begin();
    auto itr_cell_end = JL.get_JailHouseCellItr_end() ;
    ui->comboBox_CellList->clear();
    int cellcount = ui->lineEdit_NO_CELLS->text().toInt() ;
    ui->comboBox_CellList->addItem("--Select--");
    ui->comboBox_CellList->addItem("root_cell");
    int i = JL.get_number_of_cells() ;
    for (; itr_cell!= itr_cell_end; ++itr_cell)
        ui->comboBox_CellList->addItem(QString::fromStdString(itr_cell->first));

    while ( ++i < cellcount ) {
        ui->comboBox_CellList->addItem("Cell" + QString::number(i));
    }

}


// To load the cell dropdown list with the latest configurations by taking cell name as argument
void MainWindow::load_cell_dropdownlist (std::string cell_name) {
//    JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
//    auto itr_cell = JL.get_JailHouseCellItr_begin();
//    auto itr_cell_end = JL.get_JailHouseCellItr_end() ;
//    ui->comboBox_CellList->clear();
//    int cellcount = ui->lineEdit_NO_CELLS->text().toInt() ;
//    ui->comboBox_CellList->addItem("root_cell");
//    int i = JL.get_number_of_cells() ;
//    for (; itr_cell!= itr_cell_end; ++itr_cell)
//        ui->comboBox_CellList->addItem(QString::fromStdString(itr_cell->first));

//    while ( ++i < cellcount ) {
//        ui->comboBox_CellList->addItem("Cell" + QString::number(i));
//    }
    load_cell_dropdownlist();
    QString textToFind = QString::fromStdString(cell_name);
    int index = ui->comboBox_CellList->findText(textToFind) ;
    ui->comboBox_CellList->setCurrentIndex(index);


}


// To Get HyperVisor memory info from GUI and Adding to the root cell
void MainWindow::add_Hypervisor_Memory(RootCell &r) {

    std::string phys_start = ui->lineEdit_HM_Phy->text().toUtf8().constData() ;
    std::string size = ui->lineEdit_Size_Hex_Value_HM->text().toUtf8().constData();

    Hypervisor_Memory h = {strtoull(phys_start.c_str(),NULL,0), strtoull(size.c_str(),NULL,0) } ;
    r.set_Hypervisor_Memory(h);

}

// To Get Debug console info from GUI and Adding to the root cell
void MainWindow::add_Debug_Console(RootCell &r) {

    std::string address = ui->lineEdit_Address_DebugConsole->text().toUtf8().constData() ;
    std::string siz = ui->lineEdit_Size_Hex_value_DC->text().toUtf8().constData() ;

    QList<QCheckBox *> allButtons = ui->groupBox_Flags_DebugConsole->findChildren<QCheckBox *>();
    qDebug() <<allButtons.size();
    vector<std::string> DC_Flags ;
    for(int i = 0; i < allButtons.size(); ++i)
    {
        if(allButtons.at(i)->isChecked())
            DC_Flags.push_back(Debug_Console_Flags[i]);

    }

    Debug_Console d = {strtoull(address.c_str(),NULL,0) , strtoull(siz.c_str(),NULL,0), DC_Flags } ;
    r.set_Debug_Console(d);

}

// To Get Platform info from GUI and Adding to the root cell
void MainWindow::add_Platform_Info(RootCell &r) {

    std::string pci_mmconfig_base = ui->lineEdit_PCI_MMCONFIG_BASE->text().toUtf8().constData() ;
    int pci_mmconfig_end_bus = ui->lineEdit_PCI_MMCONFIG_END_BUS->text().toInt() ;
    int pci_is_virtual = ui->lineEdit_PCI_IS_VIRTUAL->text().toInt() ;
    int gic_version = ui->lineEdit_GIC_VERSION->text().toInt() ;
    std::string gicd_base = ui->lineEdit_GICD_BASE->text().toUtf8().constData() ;
    std::string gicc_base = ui->lineEdit_GICC_BASE->text().toUtf8().constData() ;
    std::string gich_base = ui->lineEdit_GICH_BASE->text().toUtf8().constData() ;
    std::string gicv_base = ui->lineEdit_GICV_BASE->text().toUtf8().constData() ;
    int maintenance_irq = ui->lineEdit_Maintenance_IRQ->text().toInt() ;

    Platform_Info p = { strtoull(pci_mmconfig_base.c_str(),NULL,0),pci_mmconfig_end_bus,pci_is_virtual,gic_version,
                        strtoull(gicd_base.c_str(),NULL,0),strtoull(gicc_base.c_str(),NULL,0),
                        strtoull(gich_base.c_str(),NULL,0),strtoull(gicv_base.c_str(),NULL,0),maintenance_irq } ;

    r.set_Platform_Info(p);


}



// on event generate config clicked, it will generate config.c file for each configured cell.
void MainWindow::on_pushButton_GenerateConfigFile_clicked()
{

    JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList() ;
    auto itr_cell = JL.get_JailHouseCellItr_begin();
    auto itr_cell_end = JL.get_JailHouseCellItr_end() ;

    for (; itr_cell!= itr_cell_end; ++itr_cell)
    {
        GenConfig confile(itr_cell->second);
    }
    RootCell rc = JL.get_rootcell();
    GenConfig rootconfig(rc);
}

// Loading HyperVisor memory info into GUI
void MainWindow::load_Hypervisor_Memory(RootCell &r) {
    auto hm = r.get_Hypervisor_Memory() ;
    std::stringstream stream ;
    stream << std::hex << hm.phys_start;
    QString s = stream.str().c_str() ;
    ui->lineEdit_HM_Phy->setText("0x" + s);

    std::stringstream stream1 ;
    stream1 << std::dec << hm.size;
    s = stream1.str().c_str() ;
    ui->lineEdit_HM_size->setText(s);
}

// Loading Debug console info into GUI
void MainWindow::load_Debug_Console(RootCell &r) {

    auto dc = r.get_Debug_Console() ;
    std::stringstream stream ;
    stream << std::hex << dc.address ;
    QString s = stream.str().c_str() ;
    ui->lineEdit_Address_DebugConsole->setText("0x" + s);

    std::stringstream stream1 ;
    stream1 << std::dec << dc.size ;
    s = stream1.str().c_str() ;
    ui->lineEdit_Size_DC->setText(s);

    auto debug_flags = dc.flags ;
    QList<QCheckBox *> allButtons = ui->groupBox_Flags_DebugConsole->findChildren<QCheckBox *>();
    for(int i = 0; i < allButtons.size(); ++i)
    {
        if( std::find(debug_flags.begin(), debug_flags.end(), Debug_Console_Flags[i]) != debug_flags.end() )

            //               allButtons.at(i)->setChecked(true);
            ui->groupBox_Flags_DebugConsole->findChildren<QCheckBox *>().at(i)->setChecked(true);
        else
            //               allButtons.at(i)->setChecked(false);
            ui->groupBox_Flags_DebugConsole->findChildren<QCheckBox *>().at(i)->setChecked(false);
    }



}

// Loading Platform info into GUI
void MainWindow::load_Platform_Info(RootCell &r) {

    auto pinfo = r.get_Platform_Info() ;
    std::stringstream stream ;
    stream << std::hex << pinfo.pci_mmconfig_base ;
    QString s = stream.str().c_str() ;
    ui->lineEdit_PCI_MMCONFIG_BASE->setText("0x" + s);
    ui->lineEdit_PCI_MMCONFIG_END_BUS->setText(QString::number(pinfo.pci_mmconfig_end_bus));
    ui->lineEdit_PCI_IS_VIRTUAL->setText(QString::number(pinfo.pci_is_virtual));
    ui->lineEdit_GIC_VERSION->setText(QString::number(pinfo.gic_version));

    std::stringstream stream1;
    stream1 << std::hex << pinfo.gicd_base ;
    s = stream1.str().c_str() ;
    ui->lineEdit_GICD_BASE->setText("0x" + s);

    std::stringstream stream2;
    stream2 << std::hex << pinfo.gicc_base ;
    s = stream2.str().c_str() ;
    ui->lineEdit_GICC_BASE->setText("0x" + s);

    std::stringstream stream3;
    stream3 << std::hex << pinfo.gich_base ;
    s = stream3.str().c_str() ;
    ui->lineEdit_GICH_BASE->setText("0x" + s);

    std::stringstream stream4;
    stream4 << std::hex << pinfo.gicv_base ;
    s = stream1.str().c_str() ;
    ui->lineEdit_GICV_BASE->setText("0x" + s);

    ui->lineEdit_Maintenance_IRQ->setText(QString::number(pinfo.maintenance_irq));

}


// on event clicked import button, To open a dialog which allows user to import config.c files into GUI
void MainWindow::on_pushButton_import_clicked()
{
    set_highlight(ui->pushButton_import->text());
    JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList() ;
    if (( ui->lineEdit_NO_CELLS->text().toInt() - JL.get_number_of_cells()  ) >= 1) {
        //        imp = new Import(this) ;
        imp->show();
    } else
    {
        QMessageBox::warning(this, "Importing files" , "Add more no. cells to allocate") ;
    }
}

void MainWindow::uncheck_import()  {
    ui->pushButton_import->setChecked(false);
}


// Making import and create_config buttons active of Actions section
void MainWindow::Disable_LS_Buttons () {

    ui->pushButton_import->setEnabled(true);
    ui->pushButton_View_Configuration->setEnabled(false) ;
    ui->pushButton_View_ConfigFiles->setEnabled(false);
    ui->pushButton_GenerateConfigFile->setEnabled(false);
}

// Enabling all buttons of Actions sections
void MainWindow::Enable_LS_Buttons () {

    ui->pushButton_import->setEnabled(true);
    ui->pushButton_View_Configuration->setEnabled(true) ;
    ui->pushButton_View_ConfigFiles->setEnabled(true);
    ui->pushButton_GenerateConfigFile->setEnabled(true);
}

// slot will called whenever cell dropdown list need to reload with latest configurations
void MainWindow::slot_load_cell_dropdownlist() {
    JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList();
    auto itr_cell = JL.get_JailHouseCellItr_begin();
    auto itr_cell_end = JL.get_JailHouseCellItr_end() ;
    ui->comboBox_CellList->clear();
    int cellcount = ui->lineEdit_NO_CELLS->text().toInt() ;
    ui->comboBox_CellList->addItem("root_cell");
    int i = JL.get_number_of_cells() ;
    for (; itr_cell!= itr_cell_end; ++itr_cell)
        ui->comboBox_CellList->addItem(QString::fromStdString(itr_cell->first));

    while ( ++i < cellcount ) {
        ui->comboBox_CellList->addItem("Cell" + QString::number(i));
    }

}


// on event clicked Transfer_To_Target button, will open a dialog which allow user to do ssh login and file transfer.
void MainWindow::on_pushButton_Transfer_To_Target_clicked()
{
    set_highlight(ui->pushButton_Transfer_To_Target->text());
//   t = new Transfer() ;
    t->show();
}

// To indicate which activity is going on, by highlighting specific button
void MainWindow::set_highlight(const QString &search) {
    QList<QPushButton *> allButtons = ui->groupBox_Actions->findChildren<QPushButton *>();     // this would be your list of QPushButtons
    qDebug() <<allButtons.size();

    foreach (QPushButton *b, allButtons)
    {
        if (b->text().contains(search, Qt::CaseInsensitive))
            b->setChecked(true);
        else
            b->setChecked(false);
    }

}

// To Make Create_config button highlighted by default
void MainWindow::reset_highlight()
{
    QList<QPushButton *> allButtons = ui->groupBox_Actions->findChildren<QPushButton *>();
    qDebug() <<allButtons.size();
    foreach (QPushButton *b, allButtons)
    {
        if (b->text().contains(ui->pushButton_Create_Config->text(), Qt::CaseInsensitive))
            b->setChecked(true);
        else
            b->setChecked(false);
    }
}


void MainWindow::on_comboBox_Board_list_currentTextChanged(const QString &arg1)
{
    if (ui->comboBox_CellList->isEnabled()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Board selection" , "Do You want to Erase current configuarations",
                                      QMessageBox::Yes|QMessageBox::No) ;
        if (reply == QMessageBox::Yes) {
            JailHouseCellList & JL = JailHouseCellList::getJailHouseCellList() ;
            JL.delete_all(JL);
            load_cell_dropdownlist();
            ui->lineEdit_No_Of_CPU->setText(QString::number(CPU_id[arg1.toStdString()]));
            ui->listWidget_CPUs->clear();
            for (int i = 0; i < CPU_id[arg1.toStdString()]; i++) {
                QListWidgetItem* item = new QListWidgetItem("CPU"+QString::number(i), ui->listWidget_CPUs);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
                item->setCheckState(Qt::Unchecked); // AND initialize check state
            }
           CORE = ui->listWidget_CPUs->count() ;
        }
    }
    else
    {
        ui->comboBox_CellList->setEnabled(true);
        ui->lineEdit_No_Of_CPU->setText(QString::number(CPU_id[arg1.toStdString()]));
        ui->listWidget_CPUs->clear();
        for (int i = 0; i < CPU_id[arg1.toStdString()]; i++) {
            QListWidgetItem* item = new QListWidgetItem("CPU"+QString::number(i), ui->listWidget_CPUs);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
            item->setCheckState(Qt::Unchecked); // AND initialize check state
        }
       CORE = ui->listWidget_CPUs->count() ;
    }
}

void MainWindow::on_checkBox_Selact_All_toggled(bool checked)
{
    if (checked) {
    for (int row = 0; row < ui->tableWidget_PCI_Devices->rowCount(); row++)
        ui->tableWidget_PCI_Devices->item(row,0)->setCheckState(Qt::Checked);
    }
    else
    {
        for (int row = 0; row < ui->tableWidget_PCI_Devices->rowCount(); row++)
            ui->tableWidget_PCI_Devices->item(row,0)->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_select_all_memConfig_toggled(bool checked)
{
    if (checked) {
    for (int row = 0; row < ui->tableWidget_cell_config_2->rowCount(); row++)
        ui->tableWidget_cell_config_2->item(row,0)->setCheckState(Qt::Checked);
    }
    else
    {
        for (int row = 0; row < ui->tableWidget_cell_config_2->rowCount(); row++)
            ui->tableWidget_cell_config_2->item(row,0)->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_select_all_RQchips_toggled(bool checked)
{
    if (checked) {
    for (int row = 0; row < ui->tableWidget_IRQ_Chips->rowCount(); row++)
        ui->tableWidget_IRQ_Chips->item(row,0)->setCheckState(Qt::Checked);
    }
    else
    {
        for (int row = 0; row < ui->tableWidget_IRQ_Chips->rowCount(); row++)
            ui->tableWidget_IRQ_Chips->item(row,0)->setCheckState(Qt::Unchecked);
    }
}
