#ifndef COSTUMTREEWIDGET_H
#define COSTUMTREEWIDGET_H
#include <QTreeWidgetItem>
template <typename t>
class CostumTreeWidget : public QTreeWidgetItem
{
private:
    QSharedPointer<t> citem;
public:
    inline CostumTreeWidget(QSharedPointer<t> _citem, QTreeWidget *parent = 0) :
	QTreeWidgetItem(parent,5000)

    {
	this->citem=_citem;
	this->setText(0,this->citem->name());
    }


    void setCitem(QSharedPointer<t> _citem) { this->citem = _citem; }
    QSharedPointer<t> getCitem() { return citem; }
};
#endif // COSTUMTREEWIDGET_H
