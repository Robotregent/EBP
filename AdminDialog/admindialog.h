#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <EBPdb/connection.hxx>
#include "employeelistmodel.h"
#include "costumlistwidget.h"
#include "costumtreewidget.h"

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
    bool deleteWohngruppe(int index);
    bool deleteBewohner(int index);

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

    void on_button_O_eingabeloeschen_clicked();


    void on_button_O_waehlen_clicked();

    void on_button_B_waelen_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AdminDialog *ui;
    void init();
    QSharedPointer<ebp::connection> PointerToConnection;
    EmployeeTableModel *model;
    void setLogin();
    void setContent();
    void clearLogin();
    void setOEWidget();
    void setBWidget();
    void setMitarbiterVerwalten();
    void setBewohnerVerwalten();
    //void setOEVerwalten();
    void createWohngruppe();

    //QList<QFormLayout *> OE_Formlayouts;
    QList< CostumListWidget < ebp::Wohngruppe > *> WohngruppenItems;
    QList< CostumListWidget < ebp::Bewohner > *> BewohnerItems;
    QList< CostumListWidget < ebp::Wohngruppe > *> WohngruppeTreeItems;
    bool isPasswordValid();
    ebp::Mitarbeiter::Berechtigungen setBerechtigung();
    void loadData();

};

#endif // ADMINDIALOG_H
