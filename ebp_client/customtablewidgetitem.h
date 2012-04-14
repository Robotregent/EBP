#ifndef CUSTOMTABLEWIDGETITEM_H
#define CUSTOMTABLEWIDGETITEM_H
#include <QTableWidgetItem>
template <typename t>
class CustomTableWidgetItem : public QTableWidgetItem
{
private:
    QSharedPointer<t> citem;
public:
    inline CustomTableWidgetItem(QSharedPointer<t> _citem) :
	QTableWidgetItem(5001)

    {
	this->citem=_citem;
	this->setText(this->citem->name());
    }


    void setCitem(QSharedPointer<t> _citem) { this->citem = _citem; }
    QSharedPointer<t> getCitem() { return citem; }
};
#endif // CUSTOMTABLEWIDGETITEM_H
