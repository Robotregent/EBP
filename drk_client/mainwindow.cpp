#include "mainwindow.h"
#include <QLabel>
#include <QMenuBar>
#include <QSettings>
#include <QDebug>
#include <QtCore/QtConcurrentRun>
#include <exception>
#include <QToolBar>

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
#include "texttransferagent.h"
#include "dokumentation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //this->showMaximized();


    for (int i = 0; i< MainWindow::CountOfContentWidgets; i++)
    {
        this->ContentWidgetList.append(NULL);
    }
    this->setCentralWidget(this->getContentWidget(MainWindow::LoginWidget));
    this->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    this->setMinimumSize(this->sizeHint());

    this->readSettings();

    //DockOptions
    this->setDockOptions(QMainWindow::AnimatedDocks|QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);
    this->setCorner(Qt::TopLeftCorner,Qt::TopDockWidgetArea);
    this->setCorner(Qt::TopRightCorner,Qt::TopDockWidgetArea);
    this->setCorner(Qt::BottomLeftCorner,Qt::LeftDockWidgetArea);
    this->setCorner(Qt::BottomRightCorner,Qt::BottomDockWidgetArea);


}
void MainWindow::validLogin(QSharedPointer<ebp::connection> pointer)
{
    thisSession.curConnection=pointer;

    this->loadWohnguppeUndBewohner();

    this->create_TextTransferDock();
    this->create_sidemenu();
    this->creat_InfoWidget();

    this->create_actions();

}

void MainWindow::create_sidemenu()
{

    this->dock_side_menu = new QDockWidget(tr("Navigation"),this);
    this->dock_side_menu->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->side_menu= new SideMenu(this);
    this->dock_side_menu->setWidget(this->side_menu);
    this->dock_side_menu->setObjectName("Navigation");
    this->addDockWidget(Qt::LeftDockWidgetArea,this->dock_side_menu);


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
    InfoDockWidget =new QDockWidget(tr("Information zu aktueller Auswahl"),this);
    InfoDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->_infoFrame = new InfoFrame(this);
    InfoDockWidget->setWidget(this->_infoFrame);
    InfoDockWidget->setObjectName("Information");
    this->addDockWidget(Qt::TopDockWidgetArea,InfoDockWidget);
    //Bewohner und Wohngruppe anzeigen
    this->setCurBewohnerAndWohngruppeInfo();
}
void MainWindow::create_TextTransferDock()
{
    this->TextTransferDock = new QDockWidget(this);
    this->TextTransferDock->setVisible(false);
    this->TextTransferDock->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->TextTransferDock->setObjectName("TextTransferAgent");
    this->addDockWidget(Qt::BottomDockWidgetArea,this->TextTransferDock);
}
TextTransferInterface *convertToInterface(QWidget *toConvert)
{
    TextTransferInterface *result;
    result =dynamic_cast<TextTransferInterface*>(toConvert);

    return result;
}

TextTransferAgent *MainWindow::setTextTransferAgent(TextTransferInterface *interface)
{
    TextTransferAgent *result;
    if(this->TextTransferDock->widget()!=NULL)
	delete this->TextTransferDock->widget();

    QList<TextTransferInterface *> interfaceList;
    if (interface!=NULL)
	interfaceList.append(interface);
    result=new TextTransferAgent(interfaceList,thisSession, this);
    this->TextTransferDock->setWidget(result);
    this->TextTransferDock->setVisible(true);
    return result;
}

void MainWindow::set_content(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    if(this->TextTransferDock!=NULL)
	this->TextTransferDock->setVisible(false);
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
    /// \todo Betreuungsdokumentation genauer aufteilen:
    case 2310:
    case 2311:
    case 2312:
    case 2320:
    case 2321:
    case 2322:
    case 2330:
    case 2331:
    case 2332:
	this->setCentralWidget(this->getContentWidget(MainWindow::DocumentationWidget));
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
	    {
		result = new BewohnerProtokoll(this);
		this->setTextTransferAgent(dynamic_cast<TextTransferInterface*>(result));
		break;
	    }
        case MainWindow::Leistungstraeger:
            result = new LeistungstraegerArea(this);
            break;
        case MainWindow::MeldeListeWidget:
            result = new MeldeListe(this);
            break;
        case MainWindow::EreignisWidget:
	    {
		TextTransferAgent *agent=setTextTransferAgent(NULL);
		result = new Ereignis(agent,this);
		break;
	    }
        case MainWindow::ProjektWidget:
	    {
		result = new Projekt(this);
		this->setTextTransferAgent(dynamic_cast<TextTransferInterface*>(result));
		break;
	    }
	case MainWindow::DocumentationWidget:
	    result = new Dokumentation("Hier kommt der Name der Betreuungsdokumentation hin",this);
	    break;
	}
    }
    //this->ContentWidgetList.replace(ContentTyp,result);
    return result;
}

void MainWindow::create_actions()
{
    //Action erstellen
    QAction *saveAction = new QAction(QIcon(":/actions/save"),tr("Speichern"),this);
    saveAction->setVisible(true);
    saveAction->setShortcut(QKeySequence::Save);  
    saveAction->setStatusTip(tr("Speichert aktuelle Änderungen"));
    connect(saveAction, SIGNAL(triggered()),this, SLOT(saveCurrentContent()));

    //Zu toolbar hinzufügen
    QToolBar *toolbar;
    toolbar = this->addToolBar(tr("Speichern"));
    toolbar->setObjectName("Speichern");
    toolbar->addAction(saveAction);

    toolbar->addSeparator();

    toolbar = this->addToolBar(tr("Ansicht"));
    toolbar->setObjectName("Ansicht");
    toolbar->addAction(this->dock_side_menu->toggleViewAction());
    toolbar->addAction(this->InfoDockWidget->toggleViewAction());


}
/**
  * \brief Slot für die SaveAction
  */
void MainWindow::saveCurrentContent()
{
    qDebug()<<"SaveSlot";
    try
    {
        QWidget *ptrToCast = this->centralWidget();
        SaveContentInterface *saveInterface =dynamic_cast<SaveContentInterface*>(ptrToCast);
        if(saveInterface!=0)
            saveInterface->saveContent();
    }
    catch (std::exception& ex)
    {

        qDebug()<<"Crash: "<<ex.what();
    }
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

    if (!this->thisSession.curBewohner.isNull())
    {
	settings.setValue("lastBewohner",this->thisSession.curBewohner->name());
    }
    if (!this->thisSession.curWohngruppe.isNull())
    {
	settings.setValue("lastWohngruppe",this->thisSession.curWohngruppe->name());
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
    if(this->thisSession.curConnection.isNull())
	return;

    QSettings settings("EBP.ini", QSettings::IniFormat);
    //asynchrones Laden aller Wohngruppen und Bewohner
    QFuture< QList < QSharedPointer <ebp::Wohngruppe> > > allGroups = QtConcurrent::run(ebp::loadAllGroups, this->thisSession.curConnection, this->thisSession.curMitarbeiter);
    PleasWaitDialog *pwd=new PleasWaitDialog(this);
    pwd->show();

    // Wohngruppe
    allGroups.waitForFinished();
    this->thisSession.allGroups = allGroups.result();
    //Aktuelle Wohngruppe setzen (alt)
    this->thisSession.curWohngruppe.isNull();
    if(!thisSession.allGroups.isEmpty())
    {
	this->thisSession.curWohngruppe = thisSession.allGroups.first();
	QString lastW = settings.value("lastWohngruppe",QVariant("NULL")).toString();
	if (lastW != "NULL")
	{
	    foreach(QSharedPointer <ebp::Wohngruppe> wg, thisSession.allGroups )
	    {
		if (wg->name() == lastW)
		{
		    this->thisSession.curWohngruppe = wg;
		    continue;
		}
	    }
	}
    }


    if(!this->thisSession.curWohngruppe.isNull())
    {
	QFuture< QList < QSharedPointer <ebp::Bewohner> > > allBewohner = QtConcurrent::run(ebp::loadAllBewohner, this->thisSession.curConnection, this->thisSession.curWohngruppe);

        allBewohner.waitForFinished();
	this->thisSession.allBewohner=allBewohner.result();

        //Aktuellen Bewohner setzen
	this->thisSession.curBewohner.isNull();
	if (!thisSession.allBewohner.isEmpty())
        {
	    this->thisSession.curBewohner = thisSession.allBewohner.first();
            QString lastB = settings.value("lastBewohner",QVariant("NULL")).toString();
            if (lastB != "NULL")
            {
		foreach(QSharedPointer <ebp::Bewohner> bw , thisSession.allBewohner)
                {
                    if (bw->name()==lastB)
                    {
			this->thisSession.curBewohner = bw;
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
    if (!this->thisSession.curBewohner.isNull())
	this->_infoFrame->setCurBewohner(this->thisSession.curBewohner->name());
    else
	this->_infoFrame->setCurBewohner("Keine Informationen verfügbar");
    if(!this->thisSession.curWohngruppe.isNull())
	this->_infoFrame->setCurWohngruppe(this->thisSession.curWohngruppe->name());
    else
	this->_infoFrame->setCurWohngruppe("Keine Informationen verfügbar");

}

void MainWindow::setCurMitarbeiter(QSharedPointer<ebp::Mitarbeiter> curMitarbeiter)
{
    this->thisSession.curMitarbeiter = curMitarbeiter;
}





