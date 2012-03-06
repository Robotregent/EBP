#include "costumdeletedialog.h"
#include "ui_costumdeletedialog.h"
#include <QDebug>
CostumDeleteDialog::CostumDeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CostumDeleteDialog)
{
    ui->setupUi(this);
}

CostumDeleteDialog::~CostumDeleteDialog()
{
    delete ui;
}
 Ui::CostumDeleteDialog *CostumDeleteDialog::getUI()
 {
     return ui;
 }

WohngruppenDeleteDialog::WohngruppenDeleteDialog(QList<CostumListWidget<ebp::Wohngruppe> *> _itemList, QWidget *parent) :
    CostumDeleteDialog(parent),itemList(_itemList)
{
    parentAdmin = (AdminDialog *) parent;
    for (int i = 0 ; i<itemList.count();i++)
    {
	this->getUI()->listWidget->insertItem(i,itemList.at(i)->text());
    }

}
void WohngruppenDeleteDialog::setItemList(QList<CostumListWidget<ebp::Wohngruppe> *> _itemList)
{
    foreach (CostumListWidget<ebp::Wohngruppe> *i,this->itemList)
    {
	this->getUI()->listWidget->removeItemWidget(i);
	delete i;
    }
    itemList = _itemList;
    foreach (CostumListWidget<ebp::Wohngruppe> *i,this->itemList)
    {
	this->getUI()->listWidget->addItem(i);
    }
}
QList<CostumListWidget<ebp::Wohngruppe> *> WohngruppenDeleteDialog::getItemList()
{
    return itemList;
}
void WohngruppenDeleteDialog::on_pushButton_2_clicked()
{
    //Löschen der Wohngruppe auslösen.
    if(this->parentAdmin->deleteWohngruppe(this->getUI()->listWidget->currentRow()))
	this->close();
}
void CostumDeleteDialog::on_pushButton_2_clicked()
{
    //Virtual slot for eventhandling
}

void CostumDeleteDialog::on_pushButton_clicked()
{
    this->close();
}
