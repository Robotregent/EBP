#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>

#include "../EBPdb/connection.hxx"
#include "employeelistmodel.h"
#include "costumlistwidget.h"
#include "costumtreewidget.h"
using namespace ebp;
namespace Ui {
    class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = 0);
    QSharedPointer<ebp::connection> dbPointer() { return this->PointerToConnection; }
    ~AdminDialog();

private slots:

    void on_button_abbrechen_clicked();
    void on_ButtonLogin_clicked();
    void on_ButtonAusloggen_clicked();

    void on_passwortLineEdit_returnPressed();


private:
    Ui::AdminDialog *ui;
    void init();

    QSharedPointer<connection> PointerToConnection;
    void setLogin();
    void setContent();
    void clearLogin();

};

#endif // ADMINDIALOG_H
