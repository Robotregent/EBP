#include "groupmenu.h"

GroupMenu::GroupMenu(QWidget *parent) :
    QTreeWidget(parent)
{

    //Hide Header
    this->setHeaderHidden(true);
}
