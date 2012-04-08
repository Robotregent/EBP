#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QList>
#include <QMenu>
#include "sidemenu.h"
//#include "person.h"
#include "infoframe.h"
#include <EBPdb/connection.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Wohngruppe.hxx>
#include "sessioncontext.h"
#include "texttransferinterface.h"
#include "texttransferagent.h"
#include "choosedialog.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void create_sidemenu();
    void creat_InfoWidget();
    void create_actions();
    void create_TextTransferDock();
    void writeSettings();
    void readSettings();
    void loadWohnguppeUndBewohner();
    void setCurBewohnerAndWohngruppeInfo();
    void set_content(QTreeWidgetItem * current);
    TextTransferAgent *setTextTransferAgent(TextTransferInterface *interface);
    TextTransferInterface *convertToInterface(QWidget *toConvert);
    QList <QWidget *> ContentWidgetList;
    QDockWidget *dock_side_menu;
    QDockWidget *TextTransferDock;
    QDockWidget *InfoDockWidget;
    SideMenu *side_menu;
    InfoFrame *_infoFrame;
    SessionContext thisSession;
    QString dbName;
    ChooseBwDialog *bwDialog;
    ChooseWgDialog *wgDialog;
    QAction *saveAction;


private slots:
    void itemChanged( QTreeWidgetItem * current, QTreeWidgetItem * previous );
    void itemActivated( QTreeWidgetItem * item, int column);
    void saveCurrentContent();
    void setCurWohngruppe(QSharedPointer< ebp::Wohngruppe > chosenWg);
    void setCurBewohner(QSharedPointer< ebp::Bewohner > chosenBw);
    void tabChanged(int index);
public:
    explicit MainWindow(QWidget *parent = 0);
    enum ContentWidgets { LoginWidget = 0, PersonWidget = 1 , DecreeScrollWidget = 2,  BetreuungWidget = 3, BProtokollWidget = 4,
			  Leistungstraeger=5, MeldeListeWidget=6, EreignisWidget = 7,ProjektWidget = 8, DocumentationEinkaufenWidget = 9, DocumentationWaschpflegeWidget = 10,
			  DocumentationKoerperpflegeWidget = 11, DocumentationAufstehenWidget = 12, DocumentationPartnerschaftenWidget = 13, DocumentationFreundschaftenWidget = 14,
			  CountOfContentWidgets = 15} ;
    QWidget *getContentWidget(int ContentTyp);
    void validLogin(QSharedPointer<ebp::connection> pointer);
    void setCurMitarbeiter(QSharedPointer<ebp::Mitarbeiter> curMitarbeiter);

    ~MainWindow();
    void closeEvent(QCloseEvent *event);

signals:

public slots:

};

#endif // MAINWINDOW_H
