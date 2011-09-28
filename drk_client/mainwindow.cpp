#include "mainwindow.h"
#include <QLabel>
#include "loginform.h"
#include "infowidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->showMaximized();

    for (int i = 0; i< MainWindow::CountOfContentWidgets; i++)
    {
	this->ContentWidgetList.append(NULL);
    }

    this->setCentralWidget(this->getContentWidget(MainWindow::LoginWidget));
    //this->create_sidemenu();



}

void MainWindow::create_sidemenu()
{
    this->setDockOptions(QMainWindow::AnimatedDocks|QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);
    this->setCorner(Qt::TopLeftCorner,Qt::LeftDockWidgetArea);
    this->setCorner(Qt::TopRightCorner,Qt::TopDockWidgetArea);
    this->dock_side_menu = new QDockWidget("&Seitenmenü",this);
    this->dock_side_menu->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->side_menu= new SideMenu(this);
    this->dock_side_menu->setWidget(this->side_menu);
    this->addDockWidget(Qt::LeftDockWidgetArea,this->dock_side_menu);

    this->connect(this->side_menu->getClientMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(set_content(QTreeWidgetItem*,QTreeWidgetItem*)));
    this->connect(this->side_menu->getGroupMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(set_content(QTreeWidgetItem*,QTreeWidgetItem*)));

    this->setCentralWidget(this->getContentWidget(MainWindow::PersonWidget));

}
void MainWindow::creat_InfoWidget()
{
    QDockWidget *dw =new QDockWidget("",this);
    dw->setAllowedAreas(Qt::AllDockWidgetAreas);
    dw->setWidget(new InfoWidget(this));
    this->addDockWidget(Qt::TopDockWidgetArea,dw);
}

void MainWindow::set_content(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    switch(current->type())
    {
    case 2000:
	this->setCentralWidget(this->getContentWidget(MainWindow::PersonWidget));
	break;
    }
    return;
}

QWidget *MainWindow::getContentWidget(int ContentTyp)
{
    QWidget *result = this->ContentWidgetList.at(ContentTyp);
    if (result!=NULL)
    {
	return result;
    }
    else
    {
	switch (ContentTyp)
	{
	case MainWindow::PersonWidget:
	    result=new person(this);
	    break;
	case MainWindow::LoginWidget:
	    result=new LoginForm(this);
	    break;
	}
    }
    return result;
}
