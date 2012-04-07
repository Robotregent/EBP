#include "createtest.h"
#include <time.h>
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Verfuegung.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Bewohnerereignis.hxx>
#include <EBPdb/Wohngruppe.hxx>
#include <EBPdb/Wohngruppenereignis.hxx>
#include <EBPdb/Dokumentation.hxx>
#include <EBPdb/Abwesenheit.hxx>
#include <EBPdb/Projekt.hxx>
#include <EBPdb/Protokoll.hxx>
#include <EBPdb/Leistungstraeger.hxx>
#include <EBPdb/Betreuung.hxx>
void CreateTest::mitarbeiterTest()
{
    for( int i = 0 ; i< 10; i++)
    {
	QSharedPointer< ebp::Mitarbeiter > aMitarbeiter  =  QSharedPointer<ebp::Mitarbeiter>
							    (
								new ebp::Mitarbeiter(
                                                                "testLogin"+QVariant(rand() % 100000 + 1).toString(),
								ebp::Mitarbeiter::AdminRecht,
                                                                "Mr Test"+QVariant(rand() % 100000 + 1).toString()
							    ));
	QVERIFY(!aMitarbeiter.isNull());
        //QVERIFY(aMitarbeiter->updatePassword(aConnection,"test_password"));
        QVERIFY(aMitarbeiter->create(aConnection,"test_password"));

    }
}

void CreateTest::initTestCase()
{
    aConnection = QSharedPointer< ebp::connection >( new ebp::connection("ebp_test_root", "ebp_test", "localhost", 3306));
    QVERIFY(aConnection->establish("ebp_test_root"));
    srand ( time(NULL) );
}
void CreateTest::bewohnerTest()
{
    for( int i = 0 ; i< 10; i++)
    {
	QSharedPointer< ebp::Bewohner > aBewohner = QSharedPointer<ebp::Bewohner>( new ebp::Bewohner(rand() % 100000 + 1));
	QVERIFY(!aBewohner.isNull());
	QVERIFY(aBewohner->create(aConnection));
    }
}

void CreateTest::bewohnerereignisTest()
{
    for( int i = 0 ; i< 10; i++)
    {
        QSharedPointer< ebp::Bewohnerereignis > aBewohnerereignis = QSharedPointer<ebp::Bewohnerereignis>( new ebp::Bewohnerereignis(QDateTime::currentDateTime(),QVariant(rand() % 100000 + 1).toString()));
        QVERIFY(!aBewohnerereignis.isNull());
        QVERIFY(aBewohnerereignis->create(aConnection));
    }
}

void CreateTest::wohngruppeTest()
{
    for( int i = 0 ; i< 10; i++)
    {
	QSharedPointer< ebp::Wohngruppe > aWohngruppe = QSharedPointer<ebp::Wohngruppe>( new ebp::Wohngruppe(QVariant(rand() % 100000 + 1).toString()));
	QVERIFY(!aWohngruppe.isNull());
	QVERIFY(aWohngruppe->create(aConnection));
    }
}

void CreateTest::wohngruppenereignisTest()
{
    for( int i = 0 ; i< 10; i++)
    {
	QSharedPointer< ebp::Wohngruppenereignis > aWohngruppenereignis = QSharedPointer<ebp::Wohngruppenereignis>( new ebp::Wohngruppenereignis(QDateTime::currentDateTime(),QVariant(rand() % 100000 + 1).toString()));
	QVERIFY(!aWohngruppenereignis.isNull());
	QVERIFY(aWohngruppenereignis->create(aConnection));
    }
}

void CreateTest::dokumentationTest()
{
    for( int i = 0 ; i< 10; i++)
    {
	QSharedPointer< ebp::Dokumentation > aDokumentation = QSharedPointer<ebp::Dokumentation> (new ebp::Dokumentation(ebp::Dokumentation::einkaufen,ebp::Dokumentation::bekommeAssistenz));
	QVERIFY(!aDokumentation.isNull());
	QVERIFY(aDokumentation->create(aConnection));
    }
}

void CreateTest::verfuegungTest()
{
    for( int i = 0 ; i< 10; i++)
    {
	QSharedPointer< ebp::Verfuegung > aVerfuegung = QSharedPointer<ebp::Verfuegung> (new ebp::Verfuegung(true,ebp::Verfuegung::Patientenverfuegung,QDate::currentDate(),"Testgrund"));
	QVERIFY(!aVerfuegung.isNull());
	QVERIFY(aVerfuegung->create(aConnection));
    }
}
void CreateTest::Abwesenheit()
{
    for( int i = 0 ; i< 10; i++)
    {
        QSharedPointer< ebp::Abwesenheit > aAbwesenheit = QSharedPointer<ebp::Abwesenheit> (new ebp::Abwesenheit(QDate::currentDate(),"Testgrund"));
        QVERIFY(!aAbwesenheit.isNull());
        QVERIFY(aAbwesenheit->create(aConnection));
    }
}

void CreateTest::Protokoll()
{
    for( int i = 0 ; i< 10; i++)
    {
        QSharedPointer< ebp::Protokoll > aProtokoll = QSharedPointer<ebp::Protokoll> (new ebp::Protokoll("TEstinhalt",QDate::currentDate()));
        QVERIFY(!aProtokoll.isNull());
        QVERIFY(aProtokoll->create(aConnection));
    }
}

void CreateTest::Projekt()
{
    for( int i = 0 ; i< 10; i++)
    {
        QSharedPointer< ebp::Projekt > aProjekt = QSharedPointer<ebp::Projekt> (new ebp::Projekt("TESTNAME","Testbeschreibung","Testtyp",QDate::currentDate(),QDate::currentDate()));
        QVERIFY(!aProjekt.isNull());
        QVERIFY(aProjekt->create(aConnection));
    }
}

void CreateTest::Leistungstraeger()
{
    for( int i = 0 ; i< 10; i++)
    {
        QSharedPointer< ebp::Leistungstraeger > aLeistungstraeger = QSharedPointer<ebp::Leistungstraeger> (new ebp::Leistungstraeger("Testname"));
        QVERIFY(!aLeistungstraeger.isNull());
        QVERIFY(aLeistungstraeger->create(aConnection));
    }
}
void CreateTest::Betreuung()
{
    for( int i = 0 ; i< 10; i++)
    {
	QSharedPointer< ebp::Betreuung > aBetreuung = QSharedPointer<ebp::Betreuung> (new ebp::Betreuung());
	QVERIFY(!aBetreuung.isNull());
	QVERIFY(aBetreuung->create(aConnection));
    }
}

void CreateTest::cleanupTestCase()
{
    aConnection.clear();
}
