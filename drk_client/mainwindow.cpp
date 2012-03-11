#include "mainwindow.h"
#include <QLabel>
#include <QMenuBar>
#include <QSettings>
#include <QDebug>
#include <QtCore/QtConcurrentRun>

#include "loginform.h"
#include "infoframe.h"
#include "decreescrollarea.h"
#include "betreuung.h"
#include "bewohnerprotokoll.h"
#include "leistungstraegerarea.h"
#include "meldeliste.h"
#include "ereignis.h"
#include "projekt.h"
#include "WohngruppenUndBewohnerLaden.h"
#include "pleaswaitdialog.h"
#include "person.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //this->showMaximized();


    for (int i = 0; i< MainWindow::CountOfContentWidgets; i++)
    {
        this->ContentWidgetList.append(NULL);
    }
    this->create_topmenu();
    this->setCentralWidget(this->getContentWidget(MainWindow::LoginWidget));
    this->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    this->setMinimumSize(this->sizeHint());

    this->readSettings();


}
void MainWindow::validLogin(QSharedPointer<ebp::connection> pointer)
{
    PointerToConnection=pointer;

    this->loadWohnguppeUndBewohner();

    this->create_sidemenu();
    this->creat_InfoWidget();

}

void MainWindow::create_sidemenu()
{
    this->setDockOptions(QMainWindow::AnimatedDocks|QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);
    this->setCorner(Qt::TopLeftCorner,Qt::TopDockWidgetArea);
    this->setCorner(Qt::TopRightCorner,Qt::TopDockWidgetArea);
    this->dock_side_menu = new QDockWidget(tr("Navigation"),this);
    this->dock_side_menu->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->side_menu= new SideMenu(this);
    this->dock_side_menu->setWidget(this->side_menu);
    this->dock_side_menu->setObjectName("Navigation");
    this->addDockWidget(Qt::LeftDockWidgetArea,this->dock_side_menu);

    this->viewMenu->addAction(this->dock_side_menu->toggleViewAction());

    //Versuche Größe in Griff zu bekommen
    //this->dock_side_menu->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Expanding);
    //this->dock_side_menu->setMaximumSize(this->dock_side_menu->sizeHint());
    //this->dock_side_menu->adjustSize();

    this->connect(this->side_menu->getClientMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(set_content(QTreeWidgetItem*,QTreeWidgetItem*)));
    this->connect(this->side_menu->getGroupMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(set_content(QTreeWidgetItem*,QTreeWidgetItem*)));

    this->setCentralWidget(this->getContentWidget(MainWindow::PersonWidget));

}
void MainWindow::creat_InfoWidget()
{
    QDockWidget *dw =new QDockWidget(tr("Information zu aktueller Auswahl"),this);
    dw->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->_infoFrame = new InfoFrame(this);
    dw->setWidget(this->_infoFrame);
    dw->setObjectName("Information");
    this->addDockWidget(Qt::TopDockWidgetArea,dw);
    this->viewMenu->addAction(dw->toggleViewAction());
    //Bewohner und Wohngruppe anzeigen
    this->setCurBewohnerAndWohngruppeInfo();
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
    //Versuch größe in grif zu bekommen
    //this->centralWidget()->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    //this->centralWidget()->setMinimumSize(this->centralWidget()->sizeHint());

    //this->centralWidget()->adjustSize();
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
MainWindow::~MainWindow()
{
    //delete side_menu;
    //delete viewMenu;
}
void MainWindow::writeSettings()
{
    QSettings settings("EBP.ini", QSettings::IniFormat);
    settings.setValue("pos", this->pos());
    settings.setValue("size", this->size());
    settings.setValue("windowState", saveState());

    if (!this->_curBewohner.isNull())
    {
	settings.setValue("lastBewohner",this->_curBewohner->name());
    }
    if (!this->_curWohngruppe.isNull())
    {
	settings.setValue("lastWohngruppe",this->_curWohngruppe->name());
    }
}

void MainWindow::readSettings()
{
    //Zustand wiederherstellen
    QSettings settings("EBP.ini", QSettings::IniFormat);
    QPoint pos = settings.value("pos", QPoint(0, 0)).toPoint();
    QSize size = settings.value("size", QSize(1200, 800)).toSize();
    resize(size);
    move(pos);
    this->restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    this->writeSettings();
    //qDebug() << QApplication::applicationDirPath();
    QMainWindow::closeEvent(event);
}


void MainWindow::loadWohnguppeUndBewohner()
{
    if(this->PointerToConnection.isNull())
	return;

    QSettings settings("EBP.ini", QSettings::IniFormat);
    //asynchrones Laden aller Wohngruppen und Bewohner
    QFuture< QList < QSharedPointer <ebp::Wohngruppe> > > allGroups = QtConcurrent::run(ebp::loadAllGroups, this->PointerToConnection, this->_curMitarbeiter);
    PleasWaitDialog *pwd=new PleasWaitDialog(this);
    pwd->show();

    // Wohngruppe
    allGroups.waitForFinished();
    this->_AlleWohngruppenDesAktuellenMa = allGroups.result();
    //Aktuelle Wohngruppe setzen (alt)
    this->_curWohngruppe.isNull();
    if(!_AlleWohngruppenDesAktuellenMa.isEmpty())
    {
	this->_curWohngruppe = _AlleWohngruppenDesAktuellenMa.first();
	QString lastW = settings.value("lastWohngruppe",QVariant("NULL")).toString();
	if (lastW != "NULL")
	{
	    foreach(QSharedPointer <ebp::Wohngruppe> wg, _AlleWohngruppenDesAktuellenMa )
	    {
		if (wg->name() == lastW)
		{
		    this->_curWohngruppe = wg;
		    continue;
		}
	    }
	}
    }


    if(!this->_curWohngruppe.isNull())
    {
        QFuture< QList < QSharedPointer <ebp::Bewohner> > > allBewohner = QtConcurrent::run(ebp::loadAllBewohner, this->PointerToConnection, this->_curWohngruppe);

        allBewohner.waitForFinished();
        this->_alleBewohnerDerAktuellenGruppe=allBewohner.result();

        //Aktuellen Bewohner setzen
        this->_curBewohner.isNull();
        if (!_alleBewohnerDerAktuellenGruppe.isEmpty())
        {
            this->_curBewohner = _alleBewohnerDerAktuellenGruppe.first();
            QString lastB = settings.value("lastBewohner",QVariant("NULL")).toString();
            if (lastB != "NULL")
            {
                foreach(QSharedPointer <ebp::Bewohner> bw , _alleBewohnerDerAktuellenGruppe)
                {
                    if (bw->name()==lastB)
                    {
                        this->_curBewohner = bw;
                        continue;
                    }
                }
            }
        }


    }
    pwd->close();


}
void MainWindow::setCurBewohnerAndWohngruppeInfo()
{
    if (!this->_curBewohner.isNull())
	this->_infoFrame->setCurBewohner(this->_curBewohner->name());
    else
	this->_infoFrame->setCurBewohner("Keine Informationen verfügbar");
    if(!this->_curWohngruppe.isNull())
	this->_infoFrame->setCurWohngruppe(this->_curWohngruppe->name());
    else
	this->_infoFrame->setCurWohngruppe("Keine Informationen verfügbar");

}

void MainWindow::setCurMitarbeiter(QSharedPointer<ebp::Mitarbeiter> curMitarbeiter)
{
    this->_curMitarbeiter = curMitarbeiter;
}





