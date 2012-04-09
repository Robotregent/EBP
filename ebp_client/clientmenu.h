#ifndef CLIENTMENU_H
#define CLIENTMENU_H

#include <QTreeWidget>

class ClientMenu : public QTreeWidget
{
    Q_OBJECT
private:
    QTreeWidgetItem* person;
    QTreeWidgetItem* protocol;
    QTreeWidgetItem* project;
    QTreeWidgetItem* documentation;

public:
    explicit ClientMenu(QWidget *parent = 0);
    ~ClientMenu();

signals:

public slots:

};

#endif // CLIENTMENU_H