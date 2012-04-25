#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // UTF-8 encoding setzen.
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );
    QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );

    QApplication a(argc, argv);
    /*QTranslator* translator = new QTranslator();
    if (translator->load("ebp_client_Altenhilfe", ":/costumer/altenhilfe")) {
	a.installTranslator(translator);
    }*/
    QTranslator translator;
    translator.load("ebp_client_Altenhilfe");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
