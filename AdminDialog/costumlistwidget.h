#ifndef COSTUMLISTWIDGET_H
#define COSTUMLISTWIDGET_H

#include <QListWidgetItem>
template <typename t>
class CostumListWidget : public QListWidgetItem
{
private:
    QSharedPointer<t> item;
public:
    CostumListWidget(QSharedPointer<t> _item, QListWidget *parent = 0);
    void setItem(QSharedPointer<t> _item) { this->item = _item; }
    QSharedPointer<t> getItem() { return item; }
};

#endif // COSTUMLISTWIDGET_H
