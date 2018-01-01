#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include "JailHouseCell.h"
#include "JailHouseCellList.h"
#include "import.h"
#include "transfer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void get_cell_data(JailHouseCellList &jlist) ;
    void get_mem_data (JailHouseCell &j) ;
    void get_pci_data (JailHouseCell &j) ;
    void get_irq_data (JailHouseCell &j) ;

    ~MainWindow();

private slots:
    void on_pushButton_Create_Config_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Mem_Config_Add_clicked();

    void on_pushButton_Mem_config_Delete_clicked();

    void on_pushButton_IRQ_Chips_Add_clicked();

    void on_pushButton_IRQ_Chips_Delete_clicked();

    void on_pushButton_PCI_Devices_Add_clicked();

    void on_pushButton_PCI_Devices_Delete_clicked();

    void on_pushButton_Bootfile_clicked();

    void on_lineEdit_HM_size_editingFinished();

//    void on_lineEdit_HM_size_returnPressed();

    void on_lineEdit_Size_DC_editingFinished();

//    void on_lineEdit_Size_DC_returnPressed();

    void on_pushButton_View_Configuration_clicked();

    void on_pushButton_Create_clicked();

//    void on_lineEdit_NO_CELLS_editingFinished();

    void on_comboBox_CellList_activated(QString index);

    void on_pushButton_Update_clicked();

    void on_pushButton_Destroy_clicked();

//    void on_lineEdit_NO_CELLS_textChanged(const QString &arg1) ;
    void on_lineEdit_NO_CELLS_returnPressed();

    void on_pushButton_GenerateConfigFile_clicked();

//    void on_lineEdit_HM_size_textChanged(const QString &arg1);

    void on_pushButton_import_clicked();

    void slot_load_cell_dropdownlist();

    void on_pushButton_Transfer_To_Target_clicked();

    void uncheck_import() ;

    void reset_highlight();

    void on_comboBox_Board_list_currentTextChanged(const QString &arg1);

    void on_checkBox_Selact_All_toggled(bool checked);

    void on_checkBox_select_all_memConfig_toggled(bool checked);

    void on_checkBox_select_all_RQchips_toggled(bool checked);

private:
    //Create_Config *cc ;
    Ui::MainWindow *ui;
    Import *imp ;
    Transfer *t ;
    QTableView *view = new QTableView;

   // QStandardItemModel *model; = new QStandardItemModel(25,5,this); //
    JailHouseCell create_cell () ;
    RootCell create_root_cell() ;
    void add_mem(JailHouseCell &j) ;
    void add_irq(JailHouseCell &j) ;
    void add_pci(JailHouseCell &j) ;
    void load_cell(int index) ;
    void load_cell(std::string) ;
    void load_Empty_cell() ;
    void load_mem(JailHouseCell &j) ;
    void load_irq(JailHouseCell &j) ;
    void load_pci(JailHouseCell &j) ;
    void Enable_Root_Tabs() ;
    void Disable_Root_Tabs() ;
    void Enable_LS_Buttons() ;
    void Disable_LS_Buttons() ;
    void clear_cpu_config() ;
    void load_cell_dropdownlist () ;
    void load_cell_dropdownlist (std::string) ;
    void add_Hypervisor_Memory(RootCell &r);
    void add_Debug_Console(RootCell &r) ;
    void add_Platform_Info(RootCell &r) ;
    void load_Hypervisor_Memory(RootCell &r) ;
    void load_Debug_Console(RootCell &r) ;
    void load_Platform_Info(RootCell &r) ;
    void set_highlight(const QString &search) ;
    void init_create_config() ;

};

#endif // MAINWINDOW_H
