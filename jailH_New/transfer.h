#ifndef TRANSFER_H
#define TRANSFER_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class Transfer;
}

class Transfer : public QDialog
{
    Q_OBJECT

public:

    QString convertEnumToQString(QProcess::ProcessError type) ;
    explicit Transfer(QWidget *parent = 0);
    ~Transfer();

private slots:
    void on_pushButton_Go_clicked();

    void on_pushButton_choosefile_transferTotarget_clicked();

    void on_pushButton_Std_output_clear_clicked();

    void on_checkBox_Show_Password_clicked(bool checked);

    void readOutput() ;

signals:
   void uncheck_transfer() ;

private:
    Ui::Transfer *ui;
    QProcess proc ;

protected:
   void closeEvent(QCloseEvent *event) ;


};

#endif // TRANSFER_H
