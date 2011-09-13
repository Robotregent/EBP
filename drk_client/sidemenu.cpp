#include "sidemenu.h"
#include <QPushButton>

SideMenu::SideMenu(QWidget *parent) :
    QTabWidget(parent)
{
    QPushButton *tmp;

    //Build Gruppe Widget
    this->group = new QWidget(this);
    this->groupLay = new QVBoxLayout(this);

    this->groupBG = new QHBoxLayout(this);
    tmp=new QPushButton(QIcon(":/group/arrow-left.png"),"");
    tmp->setToolTip("Vorherige Wohngruppe");
    this->groupBG->addWidget(tmp);

    tmp=new QPushButton(QIcon(":/group/arrow-right.png"),"");
    tmp->setToolTip("Nächste Wohngruppe");
    this->groupBG->addWidget(tmp);

    tmp=new QPushButton(QIcon(":/group/lupe.png"),"");
    tmp->setToolTip("Suche Wohngruppe");
    this->groupBG->addWidget(tmp);
    this->groupBG->setSpacing(0);
    this->groupMenu= new GroupMenu(this->group);

    this->groupMenu->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
    //this->groupMenu->setSpacing(5);

    this->groupLay->addLayout(this->groupBG);
    this->groupLay->addWidget(this->groupMenu);
    this->group->setLayout(this->groupLay);


    //Build Kunde Widget
    this->client = new QWidget(this);
    this->clientLay = new QVBoxLayout(this);

    this->clientBG = new QHBoxLayout(this);

    tmp=new QPushButton(QIcon(":/costumer/arrow-left.png"),"");
    tmp->setToolTip("Vorheriger Kunde");
    this->clientBG->addWidget(tmp);

    tmp=new QPushButton(QIcon(":/costumer/arrow-right.png"),"");
    tmp->setToolTip("Nächster Kunde");
    this->clientBG->addWidget(tmp);

    tmp=new QPushButton(QIcon(":/costumer/lupe.png"),"");
    tmp->setToolTip("Suche Kunde");
    this->clientBG->addWidget(tmp);
    this->clientBG->setSpacing(0);

    this->clientMenu= new ClientMenu(this->client);

    this->clientMenu->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
    //this->clientMenu->setSpacing(5);

    this->clientLay->addLayout(this->clientBG);
    this->clientLay->addWidget(this->clientMenu);
    this->client->setLayout(this->clientLay);

    //Add Widgets to tabs
    this->addTab(this->client,"Kunde");
    this->addTab(this->group,"Gruppe");


}
