#include "createtest.h"
#include <time.h>
void CreateTest::mitarbeiterTest()
{
    QSharedPointer< ebp::Mitarbeiter > aMitarbeiter  =  QSharedPointer<ebp::Mitarbeiter>
							(
							    new ebp::Mitarbeiter(
							    "testLogin",
							    ebp::Mitarbeiter::AdminRecht,
							    "Mr Test"
							));
    QVERIFY(!aMitarbeiter.isNull());
    QVERIFY(aMitarbeiter->create(aConnection));
    srand ( time(NULL) );
}

void CreateTest::initTestCase()
{
    aConnection = QSharedPointer< ebp::connection >( new ebp::connection("ebp_test_root", "ebp_test", "localhost", 3306));
    QVERIFY(aConnection->establish("ebp_test_root"));
}
void CreateTest::bewohnerTest()
{

    QSharedPointer< ebp::Bewohner > aBewohner = QSharedPointer<ebp::Bewohner>( new ebp::Bewohner(rand() % 100000 + 1));
    QVERIFY(!aBewohner.isNull());
    QVERIFY(aBewohner->create(aConnection));
}

void CreateTest::bewohnerereignisTest()
{
    QSharedPointer< ebp::Bewohnerereignis > aBewohnerereignis = QSharedPointer<ebp::Bewohnerereignis>( new ebp::Bewohnerereignis(QDateTime::currentDateTime(),QVariant(rand() % 100000 + 1).toString()));
    QVERIFY(!aBewohnerereignis.isNull());
    QVERIFY(aBewohnerereignis->create(aConnection));
}

void CreateTest::wohngruppeTest()
{
    QSharedPointer< ebp::Wohngruppe > aWohngruppe = QSharedPointer<ebp::Wohngruppe>( new ebp::Wohngruppe(QVariant(rand() % 100000 + 1).toString()));
    QVERIFY(!aWohngruppe.isNull());
    QVERIFY(aWohngruppe->create(aConnection));
}

void CreateTest::wohngruppenereignisTest()
{
    QSharedPointer< ebp::Wohngruppenereignis > aWohngruppenereignis = QSharedPointer<ebp::Wohngruppenereignis>( new ebp::Wohngruppenereignis(QDateTime::currentDateTime(),QVariant(rand() % 100000 + 1).toString()));
    QVERIFY(!aWohngruppenereignis.isNull());
    QVERIFY(aWohngruppenereignis->create(aConnection));
}

void CreateTest::dokumentationTest()
{
    QSharedPointer< ebp::Dokumentation > aDokumentation = QSharedPointer<ebp::Dokumentation> (new ebp::Dokumentation(ebp::Dokumentation::einkaufen,ebp::Dokumentation::bekommeAssistenz));
    QVERIFY(!aDokumentation.isNull());
    QVERIFY(aDokumentation->create(aConnection));
}

void CreateTest::verfuegungTest()
{
    QSharedPointer< ebp::Verfuegung > aVerfuegung = QSharedPointer<ebp::Verfuegung> (new ebp::Verfuegung(true,ebp::Verfuegung::Patientenverfuegung,QDate::currentDate(),"Testgrund"));
    QVERIFY(!aVerfuegung.isNull());
    QVERIFY(aVerfuegung->create(aConnection));
}
