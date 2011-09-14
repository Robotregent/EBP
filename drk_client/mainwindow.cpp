#include "mainwindow.h"
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->showMaximized();
    this->create_sidemenu();
    person *tmp= new person(this);
    tmp->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    this->setCentralWidget(tmp);

}

void MainWindow::create_sidemenu()
{
    this->setDockOptions(QMainWindow::AnimatedDocks|QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);
    this->setCorner(Qt::TopLeftCorner,Qt::TopDockWidgetArea);
    this->setCorner(Qt::TopRightCorner,Qt::TopDockWidgetArea);
    this->dock_side_menu = new QDockWidget("&Seitenmenü",this);
    this->dock_side_menu->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->side_menu= new SideMenu(this);
    this->dock_side_menu->setWidget(this->side_menu);
    this->addDockWidget(Qt::LeftDockWidgetArea,this->dock_side_menu);

}
