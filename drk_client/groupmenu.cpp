#include "groupmenu.h"

GroupMenu::GroupMenu(QWidget *parent) :
    QTreeWidget(parent)
{

    //Hide Header
    this->setHeaderHidden(true);

    ///Initalize Ereignisse
    this->gruppenbuch = new QTreeWidgetItem(this,3000);
    this->gruppenbuch->setText(0,tr("Gruppenbuch"));
    this->gruppenbuch->setIcon(0,QIcon(":/group/gruppenbuch.png"));
    //new QTreeWidgetItem(this->gruppenbuch,QStringList()<<tr("Eignisse"),3001);
    new QTreeWidgetItem(this->gruppenbuch,QStringList()<<tr("Aufgaben"),3002);

    ///Initialize Meldeliste
    this->meldeliste = new QTreeWidgetItem(this,3010);
    this->meldeliste->setText(0,tr("Meldeliste"));
    this->meldeliste->setIcon(0,QIcon(":/group/taskList.png"));

}
GroupMenu::~GroupMenu()
{
    delete gruppenbuch;
    delete meldeliste;
}
