#include "clientmenu.h"

ClientMenu::ClientMenu(QWidget *parent) :
    QTreeWidget(parent)
{
    QTreeWidgetItem *tmp, *tmp2;
    ///Initialize person
    this->person = new QTreeWidgetItem(this,2000);
    this->person->setText(0,tr("Person"));
    this->person->setIcon(0,QIcon(":/costumer/person.png"));
    //new QTreeWidgetItem(this->person,QStringList()<<tr("Betreuung"),2001);
    new QTreeWidgetItem(this->person,QStringList()<<tr("Verfügungen"),2002);
    new QTreeWidgetItem(this->person,QStringList()<<tr("Leistungsträger"),2003);

    ///Initialize project
    this->project = new QTreeWidgetItem(this,2010);
    this->project->setText(0,tr("Projekt"));
    this->project->setIcon(0,QIcon(":/costumer/project.png"));

    ///Initialize protocol
    this->protocol= new QTreeWidgetItem(this,2020);
    this->protocol->setText(0,tr("Protokoll"));
    this->protocol->setIcon(0,QIcon(":/costumer/protokoll.gif"));

    ///Initialize documentation
    this->documentation = new QTreeWidgetItem(this,2300);
    this->documentation->setText(0,tr("Betreuungsdokumentation"));
    this->documentation->setIcon(0,QIcon(":/costumer/documentation.png"));
    tmp = new QTreeWidgetItem(this->documentation,QStringList()<<tr("Lebensführung"),2310);
    tmp->setToolTip(0,tr("Alltägliche Lebensführungn"));
    tmp2 = new QTreeWidgetItem(tmp,QStringList()<<tr("Einkaufen"),2311);
    tmp2->setToolTip(0,tr("Einkaufen"));
    tmp2 = new QTreeWidgetItem(tmp,QStringList()<<tr("Wäschepflege"),2312);
    tmp2->setToolTip(0,tr("Wäschepflege"));

    tmp = new QTreeWidgetItem(this->documentation,QStringList()<<tr("Basisversorgung"),2320);
    tmp->setToolTip(0,tr("Individuelle Basisversorgung"));
    tmp2 =new QTreeWidgetItem(tmp,QStringList()<<tr("Körperpflege"),2321);
    tmp2->setToolTip(0,tr("Körperpflege"));
    tmp2 =new QTreeWidgetItem(tmp,QStringList()<<tr("Aufstehen / zu Bett gehen"),2322);
    tmp2->setToolTip(0,tr("Aufstehen / zu Bett gehen"));

    tmp = new QTreeWidgetItem(this->documentation,QStringList()<<tr("Soziale Beziehungen"),2330);
    tmp->setToolTip(0,tr("Gestaltung sozialer Beziehungen"));
    tmp2 =new QTreeWidgetItem(tmp,QStringList()<<tr("In Partnerschaften"),2331);
    tmp2->setToolTip(0,tr("In Partnerschaften"));
    tmp2 =new QTreeWidgetItem(tmp,QStringList()<<tr("In Freundschaften"),2332);
    tmp2->setToolTip(0,tr("In Freundschaften / Peergroup"));
    //Hide Header
    this->setHeaderHidden(true);

    this->setWordWrap(false);
}
ClientMenu::~ClientMenu()
{
    delete person;
    delete project;
    delete protocol;
    delete documentation;
}
