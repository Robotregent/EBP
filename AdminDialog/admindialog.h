#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>

#include "../drkv/connection.hxx"
#include "employeelistmodel.h"
#include "costumlistwidget.h"
#include "costumtreewidget.h"
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
    void on_ButtonAusloggen_clicked();

    void on_passwortLineEdit_returnPressed();

    void on_button_O_speichern_clicked();

    void on_button_B_speichern_clicked();

private:
    Ui::AdminDialog *ui;
    void init();
    QSharedPointer<connection> PointerToConnection;
    EmployeeTableModel *model;
    void setLogin();
    void setContent();
    void clearLogin();
    void setOEWidget();
    void setBWidget();
    void setMitarbiterVerwalten();
    void setBewohnerVerwalten();

    QList< CostumListWidget < Wohngruppe > *> WohngruppenItems;
    QList< CostumListWidget < Bewohner > *> BewohnerItems;
    QList< CostumTreeWidget < Wohngruppe > *> WohngruppeTreeItems;
    bool isPasswordValid();
    Mitarbeiter::Berechtigungen setBerechtigung();
    void loadData();

};

#endif // ADMINDIALOG_H
