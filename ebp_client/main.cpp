#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include "mainwindow.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    // UTF-8 encoding setzen.
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
    QString trans="";
    if(argc>1)
    {
	trans=QString(argv[1]);
    }

    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("ebp_client"+trans);
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
