#ifndef CUSTUMLISTWIDGETITEM_H
#define CUSTUMLISTWIDGETITEM_H
#include <QListWidgetItem>
/**
  * \brief Templateklasse, die jedes Objekt aus der EBPdb Biblitohek
  * aufnehemen kann, sofern es das Attribut "Name" besitzt.
  * Dient zum einfachen Anzeigen in einem QListWidget, wenn eine Model-View Darstellung zu komplex wäre.
  */
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
