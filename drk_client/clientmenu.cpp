#include "clientmenu.h"

ClientMenu::ClientMenu(QWidget *parent) :
    QTreeWidget(parent)
{
    this->person = new QTreeWidgetItem(this,2000);
    this->person->setText(0,tr("Person"));
    this->person->setIcon(0,QIcon(":/costumer/person.png"));
    new QTreeWidgetItem(this->person,QStringList()<<tr("Personenbezogene Informationen"),2001);
    new QTreeWidgetItem(this->person,QStringList()<<tr("Betreuung"),2002);
    new QTreeWidgetItem(this->person,QStringList()<<tr("Verfügungen"),2003);
    new QTreeWidgetItem(this->person,QStringList()<<tr("Krankenkasse"),2004);
    new QTreeWidgetItem(this->person,QStringList()<<tr("Kostenträger"),2005);
}
