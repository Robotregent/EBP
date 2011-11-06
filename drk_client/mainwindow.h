#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QList>
#include <QMenu>
#include "sidemenu.h"
#include "person.h"
#include "../drkv/connection.hxx"
using namespace drkv;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void create_sidemenu();
    void creat_InfoWidget();
    void create_topmenu();
    void create_actions();
    QList <QWidget *> ContentWidgetList;
    QDockWidget *dock_side_menu;
    SideMenu *side_menu;
    QSharedPointer<connection> PointerToConnection;
    QMenu *viewMenu;

private slots:
    void set_content( QTreeWidgetItem * current, QTreeWidgetItem * previous );
public:
    explicit MainWindow(QWidget *parent = 0);
    enum ContentWidgets { LoginWidget = 0, PersonWidget = 1 , DecreeScrollWidget = 2,  BetreuungWidget = 3, BProtokollWidget = 4, Leistungstraeger=5, MeldeListeWidget=6,CountOfContentWidgets = 7} ;
    QWidget *getContentWidget(int ContentTyp);
    void validLogin(QSharedPointer<connection> pointer)
    {
	PointerToConnection=pointer;
	this->create_sidemenu();
	this->creat_InfoWidget();
    }

signals:

public slots:

};

#endif // MAINWINDOW_H
