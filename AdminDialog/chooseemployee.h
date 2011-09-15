#ifndef CHOOSEEMPLOYEE_H
#define CHOOSEEMPLOYEE_H

#include <QDialog>

namespace Ui {
    class ChooseEmployee;
}

class ChooseEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseEmployee(QWidget *parent = 0);
    ~ChooseEmployee();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ChooseEmployee *ui;
};

#endif // CHOOSEEMPLOYEE_H
