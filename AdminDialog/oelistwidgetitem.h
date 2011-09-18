#ifndef OELISTWIDGETITEM_H
#define OELISTWIDGETITEM_H

#include <QListWidgetItem>
#include "../drkv/Wohngruppe.hxx"

using namespace drkv;

class OEListWidgetItem : public QListWidgetItem
{
    //Q_OBJECT
private:
    QSharedPointer<Wohngruppe> wg;
public:
    explicit OEListWidgetItem(QSharedPointer<Wohngruppe> item,QListWidget *parent = 0);
    QSharedPointer<Wohngruppe> getWG() { return this->wg; }
signals:

public slots:

};

#endif // OELISTWIDGETITEM_H
