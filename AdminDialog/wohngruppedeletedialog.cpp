#include "wohngruppedeletedialog.h"


//WohngruppenDeleteDialog::WohngruppenDeleteDialog(QList<CostumListWidget<ebp::Wohngruppe> *> _itemList, QWidget *parent) :
//    CostumDeleteDialog(parent),itemList(_itemList)
//{
//    parentAdmin = (AdminDialog *) parent;
//    for (int i = 0 ; i<itemList.count();i++)
//    {
//	this->ui->listWidget->insertItem(i,itemList.at(i)->text());
//    }

//}
//void WohngruppenDeleteDialog::setItemList(QList<CostumListWidget<ebp::Wohngruppe> *> _itemList)
//{
//    foreach (CostumListWidget<ebp::Wohngruppe> *i,this->itemList)
//    {
//	this->ui->listWidget->removeItemWidget(i);
//	delete i;
//    }
//    itemList = _itemList;
//    foreach (CostumListWidget<ebp::Wohngruppe> *i,this->itemList)
//    {
//	this->ui->listWidget->addItem(i);
//    }
//}
//QList<CostumListWidget<ebp::Wohngruppe> *> WohngruppenDeleteDialog::getItemList()
//{
//    return itemList;
//}
//void WohngruppenDeleteDialog::on_pushButton_2_clicked()
//{
//    //Löschen der Wohngruppe auslösen.
//    if(this->parentAdmin->deleteWohngruppe(this->ui->listWidget->currentRow()))
//	this->close();
//}
