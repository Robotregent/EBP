#ifndef CUSTOMTABLEWIDGETITEM_H
#define CUSTOMTABLEWIDGETITEM_H
#include <QTableWidgetItem>
/**
  * \brief Templateklasse, die jedes Objekt aus der EBPdb Biblitohek
  * aufnehemen kann, sofern es das Attribut "Name" besitzt.
  * Dient zum einfachen Anzeigen in einem QTableWidget, wenn eine Model-View Darstellung zu komplex wäre.
  */
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
