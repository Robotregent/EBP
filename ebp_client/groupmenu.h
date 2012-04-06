#ifndef GROUPMENU_H
#define GROUPMENU_H

#include <QTreeWidget>

class GroupMenu : public QTreeWidget
{
    Q_OBJECT
private:
    QTreeWidgetItem* meldeliste;
    QTreeWidgetItem* gruppenbuch;
public:
    explicit GroupMenu(QWidget *parent = 0);
    ~GroupMenu();

signals:

public slots:

};

#endif // GROUPMENU_H
