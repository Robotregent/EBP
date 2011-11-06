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

    ///Initialize Meldeliste
    this->meldeliste = new QTreeWidgetItem(this,3001);
    this->meldeliste->setText(0,tr("Meldeliste"));
    this->meldeliste->setIcon(0,QIcon(":/group/taskList.png"));

}
