#include "bewohnerereignistest.h"
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
  * \brief Initialisiert die Connection und das Bewohnerereignis zum testen.
  */
void BewohnerEreignisTest::initTestCase()
{

    aDeadConnection = QSharedPointer<ebp::connection> ( new ebp::connection("NULL","NULL"));

    aConnection = QSharedPointer<ebp::connection> ( new ebp::connection("testUser","testDB"));
    QVERIFY(!aConnection.isNull());
    aConnection->establish("test");
    srand ( time(NULL) );
    aBeEreignis = QSharedPointer<ebp::Bewohnerereignis>( new ebp::Bewohnerereignis(QDateTime::currentDateTime(),QVariant(rand() % 100000 + 1).toString()));
    QVERIFY(!aBeEreignis.isNull());
    aBeEreignis->create(aConnection);

}
/**
  * \brief Testet das Erstellen und Laden der Relation Schreiber <-1- -1-> Bewohnerereignis
  */
void BewohnerEreignisTest::schreiberRelation()
{
    QList < QSharedPointer< ebp::Mitarbeiter > > maList = ebp::Mitarbeiter::loadAll(aConnection);
    if ( maList.count()<1)
	return;
    ebp::Bewohnerereignis::linkSchreiber(aBeEreignis, maList.first());
    QList< QSharedPointer<ebp::Mitarbeiter> > ma;
    /*try
    {
        ma =  aBeEreignis->loadSchreiber(aDeadConnection);
        QVERIFY(true);
    }
    catch(std::exception ex)
    {
        QVERIFY(false);
    }*/

    ma =  aBeEreignis->loadSchreiber(aConnection);

    QVERIFY(maList.first()->login()==ma.first()->login());

    ebp::Bewohnerereignis::unlinkSchreiber(aBeEreignis,ma.first());
    ma =  aBeEreignis->loadSchreiber(aConnection);
    QVERIFY(ma.count()<1);
}
/**
  * \brief Testet das Setzen und Lesen der Datenbankfelder
  */
void BewohnerEreignisTest::testFields()
{
    QDateTime time = QDateTime::currentDateTime();
    QString testText = "Testtext";

    aBeEreignis->text(testText);
    QVERIFY(aBeEreignis->text()==testText);

    aBeEreignis->zeitpunkt(time);
    QVERIFY(aBeEreignis->zeitpunkt()==time);
}
/**
  * \brief Löschen des Bewohnerereignis
  */
void BewohnerEreignisTest::cleanupTestCase()
{
    aBeEreignis->remove(aConnection);
}
