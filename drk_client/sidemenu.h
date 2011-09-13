#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QTabWidget>
#include "clientmenu.h"
#include "groupmenu.h"
#include <QBoxLayout>

class SideMenu : public QTabWidget
{
    Q_OBJECT
    QWidget *group;
    QWidget *client;
    GroupMenu *groupMenu;
    ClientMenu *clientMenu;
    QVBoxLayout *groupLay;
    QVBoxLayout *clientLay;
    QHBoxLayout *groupBG;
    QHBoxLayout *clientBG;
public:
    explicit SideMenu(QWidget *parent = 0);
    ClientMenu *getClientMenu() { return clientMenu; }
    GroupMenu *getGroupMenu() { return groupMenu; }

signals:

public slots:

};

#endif // SIDEMENU_H
