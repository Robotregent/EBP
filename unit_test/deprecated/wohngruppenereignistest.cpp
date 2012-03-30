#include "wohngruppenereignistest.h"

/**
  * \brief Initialisiert die Connection und das Wohngruppenereignis zum testen.
  */
void WohngruppenEreignisTest::initTestCase()
{
    aConnection = QSharedPointer<ebp::connection> ( new ebp::connection("testUser","testDB"));
    QVERIFY(!aConnection.isNull());
    aConnection->establish("test");
    srand ( time(NULL) );
    aWgEreignis = QSharedPointer<ebp::Wohngruppenereignis>( new ebp::Wohngruppenereignis(QDateTime::currentDateTime(),QVariant(rand() % 100000 + 1).toString()));
    QVERIFY(!aWgEreignis.isNull());
    aWgEreignis->create(aConnection);

}
/**
  * \brief Testet das Erstellen und Laden der Relation Schreiber <-1- -1-> Wohngruppenereignis
  */
void WohngruppenEreignisTest::schreiberRelation()
{
    QList < QSharedPointer< ebp::Mitarbeiter > > maList = ebp::Mitarbeiter::loadAll(aConnection);
    if ( maList.count()<1)
	return;
    ebp::Wohngruppenereignis::linkSchreiber(aWgEreignis, maList.first());
    QList< QSharedPointer<ebp::Mitarbeiter> > ma =  aWgEreignis->loadSchreiber(aConnection);
    QVERIFY(maList.first()->login()==ma.first()->login());

    ebp::Wohngruppenereignis::unlinkSchreiber(aWgEreignis,ma.first());
    ma =  aWgEreignis->loadSchreiber(aConnection);
    QVERIFY(ma.count()<1);
}
/**
  * \brief Testet das Setzen und Lesen der Datenbankfelder
  */
void WohngruppenEreignisTest::testFields()
{
    QDateTime time = QDateTime::currentDateTime();
    QString testText = "Testtext";

    aWgEreignis->text(testText);
    QVERIFY(aWgEreignis->text()==testText);

    aWgEreignis->zeitpunkt(time);
    QVERIFY(aWgEreignis->zeitpunkt()==time);
}
/**
  * \brief Löschen des Wohngruppenereignis
  */
void WohngruppenEreignisTest::cleanupTestCase()
{
    aWgEreignis->remove(aConnection);
}
