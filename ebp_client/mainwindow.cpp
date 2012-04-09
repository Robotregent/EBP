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
    this->bwDialog = NULL;
    this->wgDialog = NULL;
    this->saveAction = NULL;

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
void MainWindow::validLogin(QSharedPointer<ebp::Mitarbeiter> newMitarbeiter, QSharedPointer<ebp::connection> newConnection)
{
    thisSession.curConnection=newConnection;
    thisSession.curMitarbeiter=newMitarbeiter;

    this->loadWohnguppeUndBewohner();

    this->create_TextTransferDock();
    this->create_sidemenu();
    this->creat_InfoWidget();

    this->create_actions();

    this->setCurBewohner(thisSession.curBewohner);
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

    this->connect(this->side_menu->getClientMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(itemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    this->connect(this->side_menu->getGroupMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(itemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    this->connect(this->side_menu->getClientMenu(),SIGNAL(itemActivated(QTreeWidgetItem*,int)),SLOT(itemActivated(QTreeWidgetItem*,int)));
    this->connect(this->side_menu->getGroupMenu(),SIGNAL(itemActivated(QTreeWidgetItem*,int)),SLOT(itemActivated(QTreeWidgetItem*,int)));

    this->connect(this->side_menu,SIGNAL(currentChanged(int)),SLOT(tabChanged(int)));

    this->setCentralWidget(this->getContentWidget(MainWindow::PersonWidget));

}
void MainWindow::creat_InfoWidget()
{
    InfoDockWidget =new QDockWidget(tr("Information zu aktueller Auswahl"),this);
    InfoDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->_infoFrame = new InfoFrame(this->bwDialog,this->wgDialog,this);
    InfoDockWidget->setWidget(this->_infoFrame);
    InfoDockWidget->setObjectName("Information");
    this->addDockWidget(Qt::TopDockWidgetArea,InfoDockWidget);
    //Bewohner und Wohngruppe anzeigen
    //this->setCurBewohnerAndWohngruppeInfo();
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

void MainWindow::set_content(QTreeWidgetItem *current)
{
    if(current==NULL)
	return;

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
	this->setCentralWidget(this->getContentWidget(MainWindow::DocumentationEinkaufenWidget));
	break;
    case 2312:
	this->setCentralWidget(this->getContentWidget(MainWindow::DocumentationWaschpflegeWidget));
	break;
    case 2320:
    case 2321:
	this->setCentralWidget(this->getContentWidget(MainWindow::DocumentationKoerperpflegeWidget));
	break;
    case 2322:
	this->setCentralWidget(this->getContentWidget(MainWindow::DocumentationAufstehenWidget));
	break;
    case 2330:
    case 2331:
	this->setCentralWidget(this->getContentWidget(MainWindow::DocumentationPartnerschaftenWidget));
	break;
    case 2332:
	this->setCentralWidget(this->getContentWidget(MainWindow::DocumentationFreundschaftenWidget));
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
	if (thisSession.curBewohner.isNull()&&(ContentTyp!=MainWindow::LoginWidget))
	{
	    //Defaulttyp, wenn Bewohner leer ist
	    result=new person(this->thisSession,this);
	}
	else
	{
	    switch (ContentTyp)
	    {
	    case MainWindow::PersonWidget:
		result=new person(this->thisSession,this);
		break;
	    case MainWindow::LoginWidget:
		result=new LoginForm(this);
		QObject::connect((LoginForm *)result,SIGNAL(validLogin(QSharedPointer<ebp::Mitarbeiter>,QSharedPointer<ebp::connection>)),SLOT(validLogin(QSharedPointer<ebp::Mitarbeiter>,QSharedPointer<ebp::connection>)));
		break;
	    case MainWindow::DecreeScrollWidget:
		result= new DecreeScrollArea(this->thisSession,this);
		break;
	    case MainWindow::BetreuungWidget:
		result = new Betreuung(this->thisSession,this);
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
		    result = new Projekt(thisSession,this);
		    this->setTextTransferAgent(dynamic_cast<TextTransferInterface*>(result));
		    break;
		}
	    case MainWindow::DocumentationEinkaufenWidget:
		result = new Dokumentation(thisSession,ebp::Dokumentation::einkaufen,this);
		break;
	    case MainWindow::DocumentationAufstehenWidget:
		result = new Dokumentation(thisSession,ebp::Dokumentation::aufstehenUndZuBettgehen,this);
		break;
	    case MainWindow::DocumentationFreundschaftenWidget:
		result = new Dokumentation(thisSession,ebp::Dokumentation::freundschaften,this);
		break;
	    case MainWindow::DocumentationKoerperpflegeWidget:
		result = new Dokumentation(thisSession,ebp::Dokumentation::koerperpflege,this);
		break;
	    case MainWindow::DocumentationPartnerschaftenWidget:
		result = new Dokumentation(thisSession,ebp::Dokumentation::partnerschaften,this);
		break;
	    case MainWindow::DocumentationWaschpflegeWidget:
		result = new Dokumentation(thisSession,ebp::Dokumentation::waeschepflege,this);
		break;

	    }
	}
    }

    //this->ContentWidgetList.replace(ContentTyp,result);
    return result;
}

void MainWindow::create_actions()
{
    //Action erstellen
    saveAction = new QAction(QIcon(":/actions/save"),tr("Speichern"),this);
    saveAction->setVisible(true);
    saveAction->setShortcut(QKeySequence::Save);  
    saveAction->setStatusTip(tr("Speichert aktuelle Änderungen"));
    connect(saveAction, SIGNAL(triggered()),this, SLOT(saveCurrentContent()));

    //Zu toolbar hinzufügen
    QToolBar *toolbar;
    toolBars.clear();
    toolbar = this->addToolBar(tr("Speichern"));
    toolbar->setObjectName("Speichern");
    toolbar->addAction(saveAction);
    toolbar->addSeparator();

    toolBars.append(toolbar);

    toolbar = this->addToolBar(tr("Ansicht"));
    toolbar->setObjectName("Ansicht");
    toolbar->addAction(this->dock_side_menu->toggleViewAction());
    toolbar->addAction(this->InfoDockWidget->toggleViewAction());
    toolbar->addSeparator();

    toolBars.append(toolbar);

    toolbar = this->addToolBar(tr("Neu anmelden"));
    QAction* logout = new QAction(QIcon(":/actions/Logout"),tr("Neu anmelden"),this);
    logout->setVisible(true);
    logout->setStatusTip(tr("Logen Sie sich aus."));
    toolbar->setObjectName("Logout");
    toolbar->addAction(logout);
    connect(logout, SIGNAL(triggered()),this, SLOT(logout()));

    toolBars.append(toolbar);
}
/**
  *\brief Slot zum auslogen
  */
void MainWindow::logout()
{
    thisSession.allBewohner.clear();
    thisSession.allGroups.clear();
    thisSession.curBewohner.clear();
    thisSession.curConnection.clear();
    thisSession.curMitarbeiter.clear();
    thisSession.curWohngruppe.clear();

    this->side_menu->disconnect(this);
    delete this->side_menu;

    this->bwDialog->disconnect(this);
    delete this->bwDialog;
    this->bwDialog = NULL;

    this->wgDialog->disconnect(this);
    delete this->wgDialog;
    this->wgDialog = NULL;

    this->InfoDockWidget->setVisible(false);
    delete this->InfoDockWidget;

    this->dock_side_menu->setVisible(false);
    delete this->dock_side_menu;


    foreach (QToolBar *t, toolBars)
    {
	this->removeToolBar(t);
	delete t;
    }
    toolBars.clear();

    this->setCentralWidget(this->getContentWidget(MainWindow::LoginWidget));
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
    if (wgDialog!=NULL)
	delete wgDialog;
    if (bwDialog!=NULL)
	delete bwDialog;
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
    //QFuture< QList < QSharedPointer <ebp::Wohngruppe> > > allGroups = QtConcurrent::run(ebp::loadAllGroups, this->thisSession.curConnection, this->thisSession.curMitarbeiter);
    //PleasWaitDialog *pwd=new PleasWaitDialog(this);
    //pwd->show();

    // Wohngruppe
    //allGroups.waitForFinished();
    //this->thisSession.allGroups = allGroups.result();
    //this->thisSession.allGroups = ebp::loadAllGroups(this->thisSession.curConnection,this->thisSession.curMitarbeiter);
    this->thisSession.allGroups = thisSession.curMitarbeiter->loadWohngruppen(thisSession.curConnection);
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
	//QFuture< QList < QSharedPointer <ebp::Bewohner> > > allBewohner = QtConcurrent::run(ebp::loadAllBewohner, this->thisSession.curConnection, this->thisSession.curWohngruppe);

	//allBewohner.waitForFinished();

	this->thisSession.allBewohner=ebp::loadAllBewohner(this->thisSession.curConnection,this->thisSession.allGroups);

        //Aktuellen Bewohner setzen
	this->thisSession.curBewohner.isNull();

	if (!thisSession.allBewohner.isEmpty())
        {
	    thisSession.curBewohner = thisSession.allBewohner.first();
            QString lastB = settings.value("lastBewohner",QVariant("NULL")).toString();
            if (lastB != "NULL")
            {
		foreach(QSharedPointer <ebp::Bewohner> bw , thisSession.allBewohner)
                {
                    if (bw->name()==lastB)
                    {
			thisSession.curBewohner = bw;
                        continue;
                    }
                }
            }

        }

    }
    //pwd->close();

    this->bwDialog = new ChooseBwDialog(thisSession.allBewohner,"Bewohner wählen:",this);
    QObject::connect(bwDialog,SIGNAL(chosen(QSharedPointer<ebp::Bewohner>)),this,SLOT(setCurBewohner(QSharedPointer<ebp::Bewohner>)));

    this->wgDialog = new ChooseWgDialog(thisSession.allGroups,"Wohngruppe wählen:",this);
    QObject::connect(wgDialog,SIGNAL(chosen(QSharedPointer<ebp::Wohngruppe>)),this,SLOT(setCurWohngruppe(QSharedPointer<ebp::Wohngruppe>)));


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

void MainWindow::setCurBewohner(QSharedPointer<ebp::Bewohner> chosenBw)
{
    thisSession.curBewohner = chosenBw;
    if(!chosenBw.isNull())
    {
	// Änderungen dürfen nur gespeichert werden, wenn Mitarbeiter die Betreuungsberechtigung hat
	bool hasPermission = false;
	QSharedPointer<ebp::Mitarbeiter> betreuuer=thisSession.curBewohner->bezugsbetreuer();
	if (this->saveAction != NULL)
	{
	    if(!betreuuer.isNull())
	    {
		if (betreuuer->login()==thisSession.curMitarbeiter->login())
		    hasPermission=true;
	    }

	    this->saveAction->setEnabled(hasPermission);
	}
	this->setCurBewohnerAndWohngruppeInfo();
	set_content(this->side_menu->getClientMenu()->currentItem());
    }
}
void MainWindow::setCurWohngruppe(QSharedPointer<ebp::Wohngruppe> chosenWg)
{
    thisSession.curWohngruppe = chosenWg;
    this->setCurBewohnerAndWohngruppeInfo();
}
void MainWindow::itemActivated(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    set_content(item);
}
void MainWindow::itemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous)
    set_content(current);
}
void MainWindow::tabChanged(int index)
{
    if (this->side_menu!=NULL)
    {
	switch ( index )
	{
	case 0:
	    set_content(this->side_menu->getClientMenu()->currentItem());
	    break;
	case 1:
	    set_content(this->side_menu->getGroupMenu()->currentItem());
	    break;
	}
    }

}
