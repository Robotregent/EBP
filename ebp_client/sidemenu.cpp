#include "sidemenu.h"
#include <QPushButton>
//#include <QDebug>

SideMenu::SideMenu(QWidget *parent) :
    QTabWidget(parent)
{
    this->Client = new ClientMenu(this);

    this->Group = new GroupMenu(this);

    //Add Widgets to tabs
    this->addTab(this->Client,tr("Bewohner"));
    this->addTab(this->Group,tr("Wohngruppe"));

    this->setMaximumWidth(280);
}
SideMenu::~SideMenu()
{
    delete this->Client;
    delete this->Group;
}

