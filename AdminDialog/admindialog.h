#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>

#include "../drkv/connection.hxx"
#include "oelistwidgetitem.h"
#include "employeelistmodel.h"
#include "costumlistwidget.h"
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
    //QList<OEListWidgetItem *> OEWidgets;
    QList< CostumListWidget < Wohngruppe > *> WohngruppenItems;
    QList< CostumListWidget < Bewohner > *> BewohnerItems;
    bool isPasswordValid();
    Mitarbeiter::Berechtigungen setBerechtigung();

};

#endif // ADMINDIALOG_H
