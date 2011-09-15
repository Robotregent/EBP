#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>

#include "../drkv/database.hxx"
#include "employeelistmodel.h"
using namespace drkv;

namespace Ui {
    class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = 0);
    ~AdminDialog();

private slots:
    void on_button_MA_suchen_clicked();

private:
    Ui::AdminDialog *ui;
    void init();
    database *db;
    QSharedPointer<database> PointerToDB;
    EmployeeTableModel *model;

};

#endif // ADMINDIALOG_H
