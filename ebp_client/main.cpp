#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // UTF-8 encoding setzen.
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}