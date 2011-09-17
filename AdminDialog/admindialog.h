#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>

#include "../drkv/connection.hxx"
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
    QSharedPointer<connection> dbPointer() { return this->PointerToConnection; }
    ~AdminDialog();

private slots:
    void on_button_MA_suchen_clicked();

    void on_button_MA_speichern_clicked();

    void on_button_abbrechen_clicked();

    void on_ButtonLogin_clicked();

    void on_button_MA_eingabeloeschen_clicked();

private:
    Ui::AdminDialog *ui;
    void init();
    connection *con;
    QSharedPointer<connection> PointerToConnection;
    EmployeeTableModel *model;
    void setLogin();
    void setContent();
    void clearLogin();
    void removeTabWidgets();
    QList<int> TabPages;
    bool isPasswordValid();

};

#endif // ADMINDIALOG_H
