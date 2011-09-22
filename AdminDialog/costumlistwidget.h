#ifndef COSTUMLISTWIDGET_H
#define COSTUMLISTWIDGET_H

#include <QListWidgetItem>
template <typename t>
class CostumListWidget : public QListWidgetItem
{
private:
    QSharedPointer<t> citem;
public:
    CostumListWidget(QSharedPointer<t> _citem, QListWidget *parent = 0);
    void setCitem(QSharedPointer<t> _citem) { this->citem = _citem; }
    QSharedPointer<t> getCitem() { return citem; }
};

#endif // COSTUMLISTWIDGET_H
