#ifndef COSTUMDELETEDIALOG_H
#define COSTUMDELETEDIALOG_H

#include <QDialog>
#include <costumlistwidget.h>
#include <EBPdb/Wohngruppe.hxx>
#include "admindialog.h"

namespace Ui {
    class CostumDeleteDialog;
}

class  CostumDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CostumDeleteDialog(QWidget *parent = 0);
    ~CostumDeleteDialog();
    //Ui::CostumDeleteDialog *getUI();
private slots:
    void on_pushButton_clicked();
    virtual void on_pushButton_2_clicked();

protected:
    Ui::CostumDeleteDialog *ui;
};
class WohngruppenDeleteDialog : public CostumDeleteDialog
{
    Q_OBJECT

public:
    explicit WohngruppenDeleteDialog(QList< CostumListWidget < ebp::Wohngruppe > *> _itemList,QWidget *parent = 0);
    QList< CostumListWidget < ebp::Wohngruppe > *> getItemList();
    void setItemList(QList< CostumListWidget < ebp::Wohngruppe > *> _itemList);
private:
    QList< CostumListWidget < ebp::Wohngruppe > *> itemList;
    AdminDialog *parentAdmin;

private slots:
    void on_pushButton_2_clicked();
};


class BewohnerDeleteDialog : public CostumDeleteDialog
{
    Q_OBJECT

public:
    explicit BewohnerDeleteDialog(QList< CostumListWidget < ebp::Bewohner > *> _itemList,QWidget *parent = 0);
    QList< CostumListWidget < ebp::Bewohner > *> getItemList();
    void setItemList(QList< CostumListWidget < ebp::Bewohner > *> _itemList);
private:
    QList< CostumListWidget < ebp::Bewohner > *> itemList;
    AdminDialog *parentAdmin;

private slots:
    void on_pushButton_2_clicked();
};

#endif // COSTUMDELETEDIALOG_H
