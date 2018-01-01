#ifndef IMPORT_H
#define IMPORT_H

#include <QDialog>

namespace Ui {
class Import;
}

class Import : public QDialog
{
    Q_OBJECT

public:
    explicit Import(QWidget *parent = 0);

    void close_import() ;

    ~Import();

private slots:
    void on_pushButton_import_config_clicked();

    void on_pushButton_import_dump_clicked();

    void on_pushButton_create_imported_config_clicked();

    void on_pushButton_4_clicked();

signals:
    void after_import();

    void uncheck() ;

private:
    Ui::Import *ui;

protected:
    void closeEvent(QCloseEvent *event) ;

};

#endif // IMPORT_H
