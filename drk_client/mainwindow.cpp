#include "mainwindow.h"
#include <QLabel>
#include <QMenuBar>

#include "loginform.h"
#include "infoframe.h"
#include "decreescrollarea.h"
#include "betreuung.h"
#include "bewohnerprotokoll.h"
#include "leistungstraegerarea.h"
#include "meldeliste.h"
#include "ereignis.h"
#include "projekt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->showMaximized();


    for (int i = 0; i< MainWindow::CountOfContentWidgets; i++)
    {
        this->ContentWidgetList.append(NULL);
    }
    this->create_topmenu();
    this->setCentralWidget(this->getContentWidget(MainWindow::LoginWidget));

}

void MainWindow::create_sidemenu()
{
    this->setDockOptions(QMainWindow::AnimatedDocks|QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);
    this->setCorner(Qt::TopLeftCorner,Qt::TopDockWidgetArea);
    this->setCorner(Qt::TopRightCorner,Qt::TopDockWidgetArea);
    this->dock_side_menu = new QDockWidget(tr("Seitenmenü"),this);
    this->dock_side_menu->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->side_menu= new SideMenu(this);
    this->dock_side_menu->setWidget(this->side_menu);
    this->addDockWidget(Qt::LeftDockWidgetArea,this->dock_side_menu);

    this->viewMenu->addAction(this->dock_side_menu->toggleViewAction());

    this->connect(this->side_menu->getClientMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(set_content(QTreeWidgetItem*,QTreeWidgetItem*)));
    this->connect(this->side_menu->getGroupMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(set_content(QTreeWidgetItem*,QTreeWidgetItem*)));

    this->setCentralWidget(this->getContentWidget(MainWindow::PersonWidget));

}
void MainWindow::creat_InfoWidget()
{
    QDockWidget *dw =new QDockWidget(tr("Information zu aktueller Auswahl"),this);
    dw->setAllowedAreas(Qt::AllDockWidgetAreas);
    dw->setWidget(new InfoFrame(this));
    this->addDockWidget(Qt::TopDockWidgetArea,dw);
    this->viewMenu->addAction(dw->toggleViewAction());
}

void MainWindow::set_content(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    switch(current->type())
    {
    case 2000:
	this->setCentralWidget(this->getContentWidget(MainWindow::PersonWidget));
	break;
    case 2001:
        this->setCentralWidget(this->getContentWidget(MainWindow::BetreuungWidget));
        break;
    case 2002:
	this->setCentralWidget(this->getContentWidget(MainWindow::DecreeScrollWidget));
	break;
    case 2010:
        this->setCentralWidget(this->getContentWidget(MainWindow::ProjektWidget));
        break;
    case 2020:
        this->setCentralWidget(this->getContentWidget(MainWindow::BProtokollWidget));
        break;
    case 2003:
        this->setCentralWidget(this->getContentWidget(MainWindow::Leistungstraeger));
        break;
    case 3000:
        this->setCentralWidget(this->getContentWidget(MainWindow::EreignisWidget));
        break;
    case 3010:
        this->setCentralWidget(this->getContentWidget(MainWindow::MeldeListeWidget));
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
	case MainWindow::DecreeScrollWidget:
	    result= new DecreeScrollArea(this);
	    break;
        case MainWindow::BetreuungWidget:
            result = new Betreuung(this);
            break;
        case MainWindow::BProtokollWidget:
            result = new BewohnerProtokoll(this);
            break;
        case MainWindow::Leistungstraeger:
            result = new LeistungstraegerArea(this);
            break;
        case MainWindow::MeldeListeWidget:
            result = new MeldeListe(this);
            break;
        case MainWindow::EreignisWidget:
            result = new Ereignis(this);
            break;
        case MainWindow::ProjektWidget:
            result = new Projekt(this);
            break;
	}
    }
    //this->ContentWidgetList.replace(ContentTyp,result);
    return result;
}
void MainWindow::create_topmenu()
{
    this->viewMenu = this->menuBar()->addMenu(tr("&Ansicht"));
}
void MainWindow::create_actions()
{

}
