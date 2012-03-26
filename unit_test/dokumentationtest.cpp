#include "dokumentationtest.h"
/**
  * \brief Initialisiert Connection und Dokumentation
  */
void DokumentationTest::initTestCase()
{
    aConnection = QSharedPointer<ebp::connection> ( new ebp::connection("testUser","testDB"));
    QVERIFY(!aConnection.isNull());
    aConnection->establish("test");
    //srand ( time(NULL) );
    aDoku = QSharedPointer<ebp::Dokumentation> (new ebp::Dokumentation(ebp::Dokumentation::einkaufen,ebp::Dokumentation::bekommeAssistenz));
    QVERIFY(!aDoku.isNull());
    QVERIFY(aDoku->create(aConnection));
}
/**
  * \brief Testet das Erstellen den Relation Dokumentation <-n- -1-> Bewohner
  */
void DokumentationTest::bewohnerRelation()
{
    QSharedPointer< ebp::Bewohner > aBewohner = ebp::Bewohner::loadAll(aConnection).first();
    QVERIFY(!aBewohner.isNull());

    ebp::Dokumentation::linkBewohner(aDoku,aBewohner);
    QVERIFY(aDoku->update(aConnection));

    QSharedPointer< ebp::Bewohner > theSameBewohner = aDoku->bewohner();
    QVERIFY(aBewohner->nummer() == theSameBewohner->nummer());

    ebp::Dokumentation::unlinkBewohner(aDoku,aBewohner);
    QVERIFY(aDoku->update(aConnection));

    QSharedPointer< ebp::Bewohner > noBewohner = aDoku->bewohner();
    QVERIFY(noBewohner.isNull());
}
/**
  * \brief Testet das Setzen und Lesen der Datenbankfelder
  */
void DokumentationTest::testFields()
{
    QString Beschreibung = "Testbeschreibung", Ziele = "Testziele", Erlaeuterungen = "Testerläuterungen";
    ebp::Dokumentation::Einstufung Einstufung = ebp::Dokumentation::bekommeBeratung;
    ebp::Dokumentation::Typ Typ = ebp::Dokumentation::partnerschaften;

    aDoku->typ(Typ);
    QVERIFY(Typ == aDoku->typ());

    aDoku->einstufung(Einstufung);
    QVERIFY(Einstufung == aDoku->einstufung());

    aDoku->beschreibung(Beschreibung);
    QVERIFY(Beschreibung == aDoku->beschreibung());

    aDoku->erlaeuterungen(Erlaeuterungen);
    QVERIFY(Erlaeuterungen == aDoku->erlaeuterungen());

    aDoku->ziele(Ziele);
    QVERIFY(Ziele == aDoku->ziele());
}
/**
  * \brief Löschen des Dokumentationsobjekts
  */
void DokumentationTest::cleanupTestCase()
{
    aDoku->remove(aConnection);
}
