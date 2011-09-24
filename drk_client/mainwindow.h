#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QList>
#include "sidemenu.h"
#include "person.h"
#include "../drkv/connection.hxx"
using namespace drkv;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void create_sidemenu();
    QList <QWidget *> ContentWidgetList;
    QDockWidget *dock_side_menu;
    SideMenu *side_menu;
    QSharedPointer<connection> PointerToConnection;
private slots:
    void set_content( QTreeWidgetItem * current, QTreeWidgetItem * previous );
public:
    explicit MainWindow(QWidget *parent = 0);
    enum ContentWidgets { LoginWidget = 0, PersonWidget = 1 , CountOfContentWidgets = 2} ;
    QWidget *getContentWidget(int ContentTyp);
    void validLogin(QSharedPointer<connection> pointer)
    {
	PointerToConnection=pointer;
	this->create_sidemenu();
    }

signals:

public slots:

};

#endif // MAINWINDOW_H
