#include "clientmenu.h"

ClientMenu::ClientMenu(QWidget *parent) :
    QTreeWidget(parent)
{
    ///Initialize person
    this->person = new QTreeWidgetItem(this,2000);
    this->person->setText(0,tr("Person"));
    this->person->setIcon(0,QIcon(":/costumer/person.png"));
    new QTreeWidgetItem(this->person,QStringList()<<tr("Betreuung"),2001);
    new QTreeWidgetItem(this->person,QStringList()<<tr("Verfügungen"),2002);
    new QTreeWidgetItem(this->person,QStringList()<<tr("Krankenkasse"),2003);
    new QTreeWidgetItem(this->person,QStringList()<<tr("Kostenträger"),2004);

    ///Initialize project
    this->project = new QTreeWidgetItem(this,2010);
    this->project->setText(0,tr("Projekt"));
    this->project->setIcon(0,QIcon(":/costumer/project.jpg"));

    ///Initialize protocol
    this->protocol= new QTreeWidgetItem(this,2020);
    this->protocol->setText(0,tr("Protokoll"));
    this->protocol->setIcon(0,QIcon(":/costumer/protokoll.gif"));

    ///Initialize documentation
    this->documentation = new QTreeWidgetItem(this,2030);
    this->documentation->setText(0,tr("Betreuungsdokumentation"));
    this->documentation->setIcon(0,QIcon(":/costumer/documentation.png"));
}
