#ifndef CUSTUMLISTWIDGETITEM_H
#define CUSTUMLISTWIDGETITEM_H
#include <QListWidgetItem>
template <typename t>
class CustomListWidgetItem : public QListWidgetItem
{
private:
    QSharedPointer<t> citem;
public:
    inline CustomListWidgetItem(QSharedPointer<t> _citem, QListWidget *parent = 0) :
	QListWidgetItem(parent,5000)

    {
	this->citem=_citem;
	this->setText(this->citem->name());
    }


    void setCitem(QSharedPointer<t> _citem) { this->citem = _citem; }
    QSharedPointer<t> getCitem() { return citem; }
};
#endif // CUSTUMLISTWIDGETITEM_H
