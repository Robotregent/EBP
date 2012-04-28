#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include "admindialog.h"

int main(int argc, char *argv[])
{
    // UTF-8 encoding setzen.
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );

    QApplication a(argc, argv);

    QString trans="";
    if(argc>1)
    {
        trans=QString(argv[1]);
    }
    QTranslator translator;
    translator.load("admindialog"+trans);
    a.installTranslator(&translator);



    AdminDialog w;
    w.show();

    return a.exec();
}
