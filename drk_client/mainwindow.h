#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QList>
#include "sidemenu.h"
#include "person.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void create_sidemenu();
    QList <QWidget *> ContentWidgetList;
    QDockWidget *dock_side_menu;
    SideMenu *side_menu;

private slots:
    void set_content( QTreeWidgetItem * current, QTreeWidgetItem * previous );
public:
    explicit MainWindow(QWidget *parent = 0);
    enum ContentWidgets { PersonWidget = 0 , CountOfContentWidgets = 1} ;
    QWidget *getContentWidget(int ContentTyp);

signals:

public slots:

};

#endif // MAINWINDOW_H
