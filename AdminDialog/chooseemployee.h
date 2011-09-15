#ifndef CHOOSEEMPLOYEE_H
#define CHOOSEEMPLOYEE_H

#include <QDialog>
#include "admindialog.h"
#include "employeelistmodel.h"
namespace Ui {
    class ChooseEmployee;
}

class ChooseEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseEmployee(EmployeeTableModel *_model, QWidget *parent = 0);
    ~ChooseEmployee();

private slots:

    void on_ButtonAbort_clicked();

    void on_ButtonErase_clicked();

private:
    Ui::ChooseEmployee *ui;
    EmployeeTableModel *model;
    AdminDialog *parent_;
};

#endif // CHOOSEEMPLOYEE_H
