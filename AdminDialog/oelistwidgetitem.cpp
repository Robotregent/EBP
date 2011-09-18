#include "oelistwidgetitem.h"

OEListWidgetItem::OEListWidgetItem(QSharedPointer<Wohngruppe> item, QListWidget *parent) :
    QListWidgetItem(parent,5000)
{
    //this->setFlags(this->flags() & Qt::ItemIsUserCheckable);
    this->wg=item;
    this->setText(this->wg->name());
}
