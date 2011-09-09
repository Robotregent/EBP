#include <QtGui/QApplication>
#include "admindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdminDialog w;
    w.show();

    return a.exec();
}
