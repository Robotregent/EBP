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

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void create_sidemenu();
    void creat_InfoWidget();
    void create_topmenu();
    void create_actions();
    void writeSettings();
    void readSettings();
    void loadWohnguppeUndBewohner();
    void setCurBewohnerAndWohngruppeInfo();
    QList <QWidget *> ContentWidgetList;
    QDockWidget *dock_side_menu;
    SideMenu *side_menu;
    QSharedPointer<ebp::connection> PointerToConnection;
    QMenu *viewMenu;
    QList < QSharedPointer<ebp::Bewohner> > _alleBewohnerDerAktuellenGruppe;
    QList < QSharedPointer<ebp::Wohngruppe> > _AlleWohngruppen;
    InfoFrame *_infoFrame;
    QSharedPointer<ebp::Bewohner> _curBewohner;
    QSharedPointer<ebp::Wohngruppe> _curWohngruppe;


private slots:
    void set_content( QTreeWidgetItem * current, QTreeWidgetItem * previous );
public:
    explicit MainWindow(QWidget *parent = 0);
    enum ContentWidgets { LoginWidget = 0, PersonWidget = 1 , DecreeScrollWidget = 2,  BetreuungWidget = 3, BProtokollWidget = 4,
                          Leistungstraeger=5, MeldeListeWidget=6, EreignisWidget = 7,ProjektWidget = 8, CountOfContentWidgets = 9} ;
    QWidget *getContentWidget(int ContentTyp);
    void validLogin(QSharedPointer<ebp::connection> pointer);

    ~MainWindow();
    void closeEvent(QCloseEvent *event);

signals:

public slots:

};

#endif // MAINWINDOW_H
