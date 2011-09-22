#include "costumlistwidget.h"

CostumListWidget::CostumListWidget(QSharedPointer<t> _citem, QListWidget *parent) :
    QListWidgetItem(parent,5000)
{
    this->citem=_citem;
    this->setText(this->citem->name());
}
