#ifndef CHOOSEEMPLOYEE_H
#define CHOOSEEMPLOYEE_H

#include <QDialog>
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

private:
    Ui::ChooseEmployee *ui;
    EmployeeTableModel *model;
};

#endif // CHOOSEEMPLOYEE_H
