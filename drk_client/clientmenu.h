#ifndef CLIENTMENU_H
#define CLIENTMENU_H

#include <QTreeWidget>

class ClientMenu : public QTreeWidget
{
    Q_OBJECT
private:
    QTreeWidgetItem* person;

public:
    explicit ClientMenu(QWidget *parent = 0);

signals:

public slots:

};

#endif // CLIENTMENU_H
