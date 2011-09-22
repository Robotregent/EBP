#include "costumlistwidget.h"
template <typename t>
CostumListWidget<t>::CostumListWidget(QSharedPointer<t> _citem, QListWidget *parent) :
    QListWidgetItem(parent,5000)
{
    this->citem=_citem;
    this->setText(this->citem->name());
}
