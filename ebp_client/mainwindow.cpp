#include "mainwindow.h"
#include <QLabel>
#include <QMenuBar>
#include <QSettings>
#include <QDebug>
#include <QtCore/QtConcurrentRun>
#include <exception>
#include <QToolBar>
#include <QMessageBox>

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
    this->setWindowTitle("Elektronische Betreuungsplanung");

    this->readSettings();

    //DockOptions
    this->setDockOptions(QMainWindow::AnimatedDocks|QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);
    this->setCorner(Qt::TopLeftCorner,Qt::TopDockWidgetArea);
    this->setCorner(Qt::TopRightCorner,Qt::TopDockWidgetArea);
    this->setCorner(Qt::BottomLeftCorner,Qt::LeftDockWidgetArea);
    this->setCorner(Qt::BottomRightCorner,Qt::BottomDockWidgetArea);
}
/**
  * \brief Slot. Wird ausgelöst nach erfolgreichem Login
  */
void MainWindow::validLogin(QSharedPointer<ebp::Mitarbeiter> newMitarbeiter, QSharedPointer<ebp::connection> newConnection)
{
    hasLogout = false;
    thisSession.curConnection=newConnection;
    thisSession.curMitarbeiter=newMitarbeiter;

    this->loadWohnguppeUndBewohner();

    this->create_TextTransferDock();
    this->create_sidemenu();
    this->creat_InfoWidget();
    this->create_actions();

    this->setCurBewohner(thisSession.curBewohner);
}
/**
  * \brief Seitenmenü mit Navigationsbaum erzeugen
  */
void MainWindow::create_sidemenu()
{

    this->dock_side_menu = new QDockWidget(tr("Navigation"),this);
    this->dock_side_menu->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    this->side_menu= new SideMenu(this);
    this->dock_side_menu->setWidget(this->side_menu);
    this->dock_side_menu->setObjectName("Navigation");
    this->addDockWidget(Qt::LeftDockWidgetArea,this->dock_side_menu);

    this->connect(this->side_menu->getClientMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(itemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    this->connect(this->side_menu->getGroupMenu(),SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),SLOT(itemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));

    this->connect(this->side_menu,SIGNAL(currentChanged(int)),SLOT(tabChanged(int)));

    this->setCentralWidget(this->getContentWidget(MainWindow::PersonWidget));
}
/**
  * \brief Infowidget initialisieren
  */
void MainWindow::creat_InfoWidget()
{
    InfoDockWidget =new QDockWidget(tr("Information zu aktueller Auswahl"),this);
    InfoDockWidget->setAllowedAreas(Qt::TopDockWidgetArea);
    this->_infoFrame = new InfoFrame(this->bwDialog,this->wgDialog,this);
    InfoDockWidget->setWidget(this->_infoFrame);
    InfoDockWidget->setObjectName("Information");
    this->addDockWidget(Qt::TopDockWidgetArea,InfoDockWidget);
}
/**
  * \brief Texttransferdock initialisieren
  */
void MainWindow::create_TextTransferDock()
{
    this->TextTransferDock = new QDockWidget(this);
    this->TextTransferDock->setVisible(false);
    this->TextTransferDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    this->TextTransferDock->setObjectName("TextTransferAgent");
    this->addDockWidget(Qt::BottomDockWidgetArea,this->TextTransferDock);
}
/**
  * \brief upcast für Texttransferinterface
  */
TextTransferInterface *convertToInterface(QWidget *toConvert)
{
    TextTransferInterface *result;
    result =dynamic_cast<TextTransferInterface*>(toConvert);

    return result;
}
/**
  * \brief Erzeugt Mediator Objekt für den Texttransfer
  */
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
/**
  * \brief Mapping Navigationsbaumeintrag <---> ContentWidget
  */
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
    case 2300:
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

    //Speicherberechtigung
    if (saveAction!=NULL)
    {
	if(current->type()<3000)
	    this->saveAction->setEnabled(this->savePermission);
	else
	    this->saveAction->setEnabled(true);
    }

    return;
}
/**
  * \brief Erzeuge ContentWidget
  * \param ContentTyp Entsprechend dem gewählten Eintrag aus Navigationsbaum
  */
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
                result = new BewohnerProtokoll(thisSession,this);
                this->setTextTransferAgent(dynamic_cast<TextTransferInterface*>(result));
                break;
            }
            case MainWindow::Leistungstraeger:
                result = new LeistungstraegerArea(this->thisSession,this);
                break;
            case MainWindow::MeldeListeWidget:
                result = new MeldeListe(this->thisSession,this);
                break;
            case MainWindow::EreignisWidget:
            {
                TextTransferAgent *agent=setTextTransferAgent(NULL);
                result = new Ereignis(thisSession,agent,this);
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
    return result;
}
/**
  * \brief Erzeugt Actions in der Toolbar
  */
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
    hasLogout = true;

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
void MainWindow::saveCurrentContent(bool pending)
{
    try
    {
        QWidget *ptrToCast = this->centralWidget();
        SaveContentInterface *saveInterface =dynamic_cast<SaveContentInterface*>(ptrToCast);
        if(saveInterface!=0)
        {
            if(pending)
            {
                if(saveInterface->hasPendingChanges())
                {
                    if(QMessageBox::question(this,"Ausstehende Änderungen","Es gibt noch ausstehende Änderungen. Wollen SIe diese speichern?","Ja","Nein")!=0)
                        return;
                }
                else
                {
                    return;
                }
            }
            if(saveInterface->saveContent())
                    QMessageBox::information(this,tr("Speichern der Änderung"),tr("Erfolgreich gespeichert"));
            else
                    QMessageBox::information(this,tr("Speichern der Änderung"),tr("Speichern fehlgeschlagen"));
        }
    }
    catch (std::exception& ex)
    {

        qDebug()<<"Crash: "<<ex.what();
    }
}
/**
  * \brief DESTROKTOR
  */
MainWindow::~MainWindow()
{
    if (wgDialog!=NULL)
	delete wgDialog;
    if (bwDialog!=NULL)
	delete bwDialog;
}
/**
  * \brief Schreibt aktuelle Fensterposition und Einstellung in die EBP.ini
  */
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
/**
  * \brief Liest EBP.ini aus und setzt Fenster in gespeicherten Modus / Position
  */
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
/**
  * \brief CloseEvent überschreiben, um Fenstereinstellungen zu speichern
  */
void MainWindow::closeEvent(QCloseEvent *event)
{
    this->writeSettings();
    QMainWindow::closeEvent(event);
}

/**
  * \brief Lädt Wohngruppen und Bewohner nach Login
  */
void MainWindow::loadWohnguppeUndBewohner()
{
    if(this->thisSession.curConnection.isNull())
	return;

    QSettings settings("EBP.ini", QSettings::IniFormat);

    // Wohngruppe
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

        this->thisSession.allBewohner=loadAllBewohner(this->thisSession.curConnection,this->thisSession.allGroups);
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

    this->bwDialog = new ChooseBwDialog(thisSession.allBewohner,tr("Bewohner wählen:"),this);
    QObject::connect(bwDialog,SIGNAL(chosen(QSharedPointer<ebp::Bewohner>)),this,SLOT(setCurBewohner(QSharedPointer<ebp::Bewohner>)));

    this->wgDialog = new ChooseWgDialog(thisSession.allGroups,tr("Wohngruppe wählen:"),this);
    QObject::connect(wgDialog,SIGNAL(chosen(QSharedPointer<ebp::Wohngruppe>)),this,SLOT(setCurWohngruppe(QSharedPointer<ebp::Wohngruppe>)));
}
/**
  * \brief Schreibt Informationen über aktuelle Bewohner und Wohngruppe in des Infowidget
  */
void MainWindow::setCurBewohnerAndWohngruppeInfo()
{
    if (!this->thisSession.curBewohner.isNull())
        this->_infoFrame->setCurBewohner(this->thisSession.curBewohner->name());
    else
        this->_infoFrame->setCurBewohner(tr("Keine Informationen verfügbar"));
    if(!this->thisSession.curWohngruppe.isNull())
        this->_infoFrame->setCurWohngruppe(this->thisSession.curWohngruppe->name());
    else
        this->_infoFrame->setCurWohngruppe(tr("Keine Informationen verfügbar"));
}
/**
  * \brief Slot. Wird ausgelöst, wenn neuer Bewohner gesetzt werden soll.
  */
void MainWindow::setCurBewohner(QSharedPointer<ebp::Bewohner> chosenBw)
{
    thisSession.curBewohner = chosenBw;
    if(!chosenBw.isNull())
    {
        // Änderungen dürfen nur gespeichert werden, wenn Mitarbeiter die Betreuungsberechtigung hat
        this->savePermission=false;
        QSharedPointer<ebp::Mitarbeiter> betreuuer=thisSession.curBewohner->bezugsbetreuer();

        if(!betreuuer.isNull())
        {
            if (betreuuer->login()==thisSession.curMitarbeiter->login())
            this->savePermission=true;
        }

        this->setCurBewohnerAndWohngruppeInfo();
        set_content(this->side_menu->getClientMenu()->currentItem());
    }
}
/**
  * \brief Slot der ausgelöst wird, wenn der gewählte Eintrag im Navigationsbaum sich ändert
  */
void MainWindow::setCurWohngruppe(QSharedPointer<ebp::Wohngruppe> chosenWg)
{
    thisSession.curWohngruppe = chosenWg;
    this->setCurBewohnerAndWohngruppeInfo();
}

/**
  * \brief Slot der ausgelöst wird, wenn der gewählte Eintrag im Navigationsbaum sich ändert
  */
void MainWindow::itemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // Noch Änderungen?
    if(!hasLogout)
    {
        if((previous->type()<3000)||previous->type()==3010)
            saveCurrentContent(true);
    }
    // Neue Maske
    set_content(current);
}
/**
  * \brief Slot. Wird ausgelöst, wenn sich der Tab des Seitenmenüs ändert.
  */
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
