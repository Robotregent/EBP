#include "sidemenu.h"
#include <QPushButton>
//#include <QDebug>

SideMenu::SideMenu(QWidget *parent) :
    QTabWidget(parent)
{
    this->Client = new ClientMenu(this);
    //this->Client->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    this->Group = new GroupMenu(this);
    //this->Group->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    //Add Widgets to tabs
    this->addTab(this->Client,tr("Bewohner"));
    this->addTab(this->Group,tr("Wohngruppe"));

    this->setMaximumWidth(280);
    //this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
    //this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);


}
SideMenu::~SideMenu()
{
    delete this->Client;
    delete this->Group;
}
