#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QTabWidget>
#include "clientmenu.h"
#include "groupmenu.h"
#include <QBoxLayout>

/**
  * \brief Seitenmenü. Hält Navigation für Klienten- und Wohngruppenmasken
  */
class SideMenu : public QTabWidget
{
    Q_OBJECT

    GroupMenu *Group;
    ClientMenu *Client;

public:
    explicit SideMenu(QWidget *parent = 0);
    ClientMenu *getClientMenu() { return Client; }
    GroupMenu *getGroupMenu() { return Group; }
    ~SideMenu();

signals:

public slots:

};

#endif // SIDEMENU_H
