#include "verfuegungtest.h"

/**
  * \brief Initialisiert Connection und Verfuegung
  */
void VerfuegungTest::initTestCase()
{
    aConnection = QSharedPointer<ebp::connection> ( new ebp::connection("testUser","testDB"));
    QVERIFY(!aConnection.isNull());
    aConnection->establish("test");
    aVerfuegung = QSharedPointer<ebp::Verfuegung> (new ebp::Verfuegung(true,"test",QDate::currentDate(),"Testgrund"));
    QVERIFY(!aVerfuegung.isNull());
    QVERIFY(aVerfuegung->create(aConnection));
}
/**
  * \brief Testet das Erstellen den Relation Verfuegung <-n- -1-> Bewohner
  */
void VerfuegungTest::bewohnerRelation()
{
    QSharedPointer< ebp::Bewohner > aBewohner = ebp::Bewohner::loadAll(aConnection).first();
    QVERIFY(!aBewohner.isNull());

    ebp::Verfuegung::linkBewohner(aVerfuegung,aBewohner);
    QVERIFY(aVerfuegung->update(aConnection));

    QSharedPointer< ebp::Bewohner > theSameBewohner = aVerfuegung->bewohner();
    QVERIFY(aBewohner->nummer() == theSameBewohner->nummer());

    ebp::Verfuegung::unlinkBewohner(aVerfuegung,aBewohner);
    QVERIFY(aVerfuegung->update(aConnection));

    QSharedPointer< ebp::Bewohner > noBewohner = aVerfuegung->bewohner();
    QVERIFY(noBewohner.isNull());
}
/**
  * \brief Testet das Setzen und Lesen der Datenbankfelder
  */
void VerfuegungTest::testFields()
{
    QString Text = "TestText", Grund = "Testgrund";
    QDate Gerichtsbescheid = QDate(2012,12,21);

    aVerfuegung->text(Text);
    QVERIFY(Text == aVerfuegung->text());

    aVerfuegung->grund(Grund);
    QVERIFY(Grund == aVerfuegung->grund());

    aVerfuegung->gerichtsbescheid(Gerichtsbescheid);
    QVERIFY(Gerichtsbescheid == aVerfuegung->gerichtsbescheid());
}
/**
  * \brief Löschen des Verfuegungsobjekts
  */
void VerfuegungTest::cleanupTestCase()
{
    aVerfuegung->remove(aConnection);
}
