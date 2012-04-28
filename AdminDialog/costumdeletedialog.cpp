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


void CostumDeleteDialog::on_pushButton_2_clicked()
{
    //Virtual slot for eventhandling
}

void CostumDeleteDialog::on_pushButton_clicked()
{
    this->close();
}

/////////Ableitung für löschen der Wohngruppe/////////////
WohngruppenDeleteDialog::WohngruppenDeleteDialog(QList<CostumListWidget<ebp::Wohngruppe> *> _itemList, QWidget *parent) :
    CostumDeleteDialog(parent),itemList(_itemList)
{
    this->setWindowTitle(tr("Wohngruppe löschen"));
    this->ui->label->setText(tr("Folgende Wohngruppe aus der Datenbank löschen:"));
    parentAdmin = (AdminDialog *) parent;
    for (int i = 0 ; i<itemList.count();i++)
    {
        this->ui->listWidget->insertItem(i,itemList.at(i)->text());
    }

}
/**
  * \brief Ersetzt die angezeigten Wohngruppen, durch eine neue Liste
  */
void WohngruppenDeleteDialog::setItemList(QList<CostumListWidget<ebp::Wohngruppe> *> _itemList)
{
    foreach (CostumListWidget<ebp::Wohngruppe> *i,this->itemList)
    {
        this->ui->listWidget->removeItemWidget(i);
        delete i;
    }
    itemList = _itemList;
    foreach (CostumListWidget<ebp::Wohngruppe> *i,this->itemList)
    {
        this->ui->listWidget->addItem(i);
    }
}
/**
  * \brief Gibt die Liste an angezeigten Wohngruppen zurück
  */
QList<CostumListWidget<ebp::Wohngruppe> *> WohngruppenDeleteDialog::getItemList()
{
    return itemList;
}
/**
  * \brief Löscht die ausgewählte Wohngruppe
  */
void WohngruppenDeleteDialog::on_pushButton_2_clicked()
{
    if(this->ui->listWidget->currentIndex().isValid())
    {
        //Löschen der Wohngruppe auslösen.
        if(this->parentAdmin->deleteWohngruppe(this->ui->listWidget->currentRow()))
            this->close();
    }
}
///////////////Ableitung für löschen eines Bewohners/////////////
BewohnerDeleteDialog::BewohnerDeleteDialog(QList<CostumListWidget<ebp::Bewohner> *> _itemList, QWidget *parent) :
    CostumDeleteDialog(parent),itemList(_itemList)
{
    this->setWindowTitle(tr("Bewohner löschen"));
    this->ui->label->setText(tr("Folgenden Bewoner aus der Datenbank löschen:"));
    parentAdmin = (AdminDialog *) parent;
    for (int i = 0 ; i<itemList.count();i++)
    {
        this->ui->listWidget->insertItem(i,itemList.at(i)->text());
    }

}
/**
  * \brief Ersetzt die angezeigten Bewohner, durch eine neue Liste
  */
void BewohnerDeleteDialog::setItemList(QList<CostumListWidget<ebp::Bewohner> *> _itemList)
{
    foreach (CostumListWidget<ebp::Bewohner> *i,this->itemList)
    {
        this->ui->listWidget->removeItemWidget(i);
        delete i;
    }
    itemList = _itemList;
    foreach (CostumListWidget<ebp::Bewohner> *i,this->itemList)
    {
        this->ui->listWidget->addItem(i);
    }
}
/**
  * \brief Gibt die Liste an angezeigten Bewohnern zurück
  */
QList<CostumListWidget<ebp::Bewohner> *> BewohnerDeleteDialog::getItemList()
{
    return itemList;
}
/**
  * \brief Löscht den ausgewählten Bewohner
  */
void BewohnerDeleteDialog::on_pushButton_2_clicked()
{
    if(this->ui->listWidget->currentIndex().isValid())
    {
        //Löschen der Bewohner auslösen.
        if(this->parentAdmin->deleteBewohner(this->ui->listWidget->currentRow()))
            this->close();
    }
}
