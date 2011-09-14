#include "sidemenu.h"
#include <QPushButton>

SideMenu::SideMenu(QWidget *parent) :
    QTabWidget(parent)
{
    this->Client = new ClientMenu(this);
    this->Client->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);

    this->Group = new GroupMenu(this);
    this->Group->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);

    //Add Widgets to tabs
    this->addTab(this->Client,tr("Bewohner"));
    this->addTab(this->Group,tr("Wohngruppe"));


}
SideMenu::~SideMenu()
{
    delete this->Client;
    delete this->Group;
}
