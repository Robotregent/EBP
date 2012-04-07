#include "loadfieldstest.h"
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Verfuegung.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Bewohnerereignis.hxx>
#include <EBPdb/Wohngruppe.hxx>
#include <EBPdb/Wohngruppenereignis.hxx>
#include <EBPdb/Dokumentation.hxx>
#include <EBPdb/Projekt.hxx>
#include <EBPdb/Protokoll.hxx>
#include <EBPdb/Abwesenheit.hxx>
void LoadFieldsTest::initTestCase()
{
    aConnection = QSharedPointer< ebp::connection >( new ebp::connection("ebp_test_root", "ebp_test", "localhost", 3306));

    QVERIFY(aConnection->establish("ebp_test_root"));
}

void LoadFieldsTest::useMitarbeiter()
{
    QList<QSharedPointer<ebp::Mitarbeiter> > maList = ebp::Mitarbeiter::loadAll(aConnection);
    QVERIFY(maList.count()>1);
    for ( int i =0; i<maList.count();i++)
    {
        QCOMPARE(maList.at(i)->name() , QVariant(i).toString()+"Mitarbeiter");

        QCOMPARE(maList.at(i)->berechtigung(),ebp::Mitarbeiter::WohngruppenRecht);

        QCOMPARE(maList.at(i)->email(),"test"+QVariant(i).toString()+"@mail");

        QCOMPARE(maList.at(i)->telefon(),QVariant(i).toString());

    }
}

void LoadFieldsTest::useWohngruppenereignis()
{
    QList<QSharedPointer<ebp::Wohngruppenereignis> > wohngruppenEreignisList = ebp::Wohngruppenereignis::loadAll(aConnection);
    QVERIFY(wohngruppenEreignisList.count()>1);
    for ( int i =0; i<wohngruppenEreignisList.count();i++)
    {
        QCOMPARE(wohngruppenEreignisList.at(i)->text(),"Testtext"+QVariant(i).toString());

        QCOMPARE(wohngruppenEreignisList.at(i)->zeitpunkt(),QDateTime(QDate(2012,4,1),QTime(11,11)));
    }
}

void LoadFieldsTest::useBewohner()
{
    QList<QSharedPointer<ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);

    QVERIFY(bewohnerList.count()>1);

    for ( int i =0; i<bewohnerList.count();i++)
    {
        QCOMPARE(bewohnerList.at(i)->geburtsdatum(),QDate(2012,4,1));

        QCOMPARE(bewohnerList.at(i)->seit(),QDate(2012,4,1));

        QCOMPARE(bewohnerList.at(i)->anrede(),"anrede"+QVariant(i).toString());

        QCOMPARE(bewohnerList.at(i)->vorname(),"vorname"+QVariant(i).toString());

        QCOMPARE(bewohnerList.at(i)->nachname(),"nachname"+QVariant(i).toString());

        QCOMPARE(bewohnerList.at(i)->geburtsort(),"geburtsort"+QVariant(i).toString());

        QCOMPARE(bewohnerList.at(i)->telefon(),"telefon"+QVariant(i).toString());

        QCOMPARE(bewohnerList.at(i)->email(),"eMail"+QVariant(i).toString());

        QCOMPARE(bewohnerList.at(i)->familienstatus(),"familienstatus"+QVariant(i).toString());

        QCOMPARE(bewohnerList.at(i)->konfession(),"konfession"+QVariant(i).toString());

        QCOMPARE(bewohnerList.at(i)->staat(),"staat"+QVariant(i).toString());

        QCOMPARE(bewohnerList.at(i)->anmerkung(),"anmerkung"+QVariant(i).toString());
    }
}

void LoadFieldsTest::useBewohnerEreignis()
{
    QList<QSharedPointer<ebp::Bewohnerereignis> > bewohnerEreignisList = ebp::Bewohnerereignis::loadAll(aConnection);
    QVERIFY(bewohnerEreignisList.count()>1);
    for ( int i =0; i<bewohnerEreignisList.count();i++)
    {
        QCOMPARE(bewohnerEreignisList.at(i)->zeitpunkt(),QDateTime(QDate(2012,4,1),QTime(11,11)));

        QCOMPARE(bewohnerEreignisList.at(i)->text(),"Testtext"+QVariant(i).toString());
    }
}

void LoadFieldsTest::useVerfuegung()
{
    QList<QSharedPointer<ebp::Verfuegung> > vList = ebp::Verfuegung::loadAll(aConnection);
    QVERIFY(vList.count()>1);
    for ( int i =0; i<vList.count();i++)
    {
        QCOMPARE(vList.at(i)->typ(),ebp::Verfuegung::Patientenverfuegung);

        QCOMPARE(vList.at(i)->grund(),"Grund"+QVariant(i).toString());

        QCOMPARE(vList.at(i)->gerichtsbescheid(),QDate(2012,4,1));

        //QVERIFY(vList.at(i)->update(aConnection));
    }
}

void LoadFieldsTest::useDokumentation()
{
    QList<QSharedPointer<ebp::Dokumentation> > dokuList = ebp::Dokumentation::loadAll(aConnection);
    QVERIFY(dokuList.count()>1);
    for ( int i =0; i<dokuList.count();i++)
    {
        QCOMPARE(dokuList.at(i)->typ(),ebp::Dokumentation::partnerschaften);

        QCOMPARE(dokuList.at(i)->einstufung(),ebp::Dokumentation::bekommeBeratung);

        QCOMPARE(dokuList.at(i)->beschreibung(),"Testbeschreibung_"+QVariant(i).toString());

        QCOMPARE(dokuList.at(i)->erlaeuterungen(),"Testerläuterung"+QVariant(i).toString());

        QCOMPARE(dokuList.at(i)->ziele(),"TestZiele"+QVariant(i).toString());
        //QVERIFY(dokuList.at(i)->update(aConnection));
    }
}

void LoadFieldsTest::useAbwesenheit()
{
    QList<QSharedPointer<ebp::Abwesenheit> > abwesenheitsList = ebp::Abwesenheit::loadAll(aConnection);
    QVERIFY(abwesenheitsList.count()>1);
    for ( int i =0; i<abwesenheitsList.count();i++)
    {
        QCOMPARE(abwesenheitsList.at(i)->grund(),QString("Testgrund"));

        QCOMPARE(abwesenheitsList.at(i)->tag(),QDate(2012,4,1));

        //QVERIFY(abwesenheitsList.at(i)->update(aConnection));
    }
}

void LoadFieldsTest::useProtokoll()
{
    QList<QSharedPointer<ebp::Protokoll> > protokollList = ebp::Protokoll::loadAll(aConnection);
    QVERIFY(protokollList.count()>1);
    for ( int i =0; i<protokollList.count();i++)
    {
        QCOMPARE(protokollList.at(i)->datum(),QDate(2012,4,1));

        QCOMPARE(protokollList.at(i)->inhalt(),QString("VIEl Testinhalt"));

        //QVERIFY(protokollList.at(i)->update(aConnection));
    }
}

void LoadFieldsTest::useProjekt()
{
    QList<QSharedPointer<ebp::Projekt> > projektList = ebp::Projekt::loadAll(aConnection);
    QVERIFY(projektList.count()>1);
    for ( int i =0; i<projektList.count();i++)
    {
        QCOMPARE(projektList.at(i)->beginn(),QDate(2012,4,1));

        QCOMPARE(projektList.at(i)->ende(),QDate(2012,4,1));

        QCOMPARE(projektList.at(i)->name(),QString("Testname"));

        QCOMPARE(projektList.at(i)->beschreibung(),QString("Lange Testbeschreibung"));

        QCOMPARE(projektList.at(i)->typ(),QString("TestTyp"));

	QCOMPARE(projektList.at(i)->ziele(),QString("TestZiele"));

        //QVERIFY(projektList.at(i)->update(aConnection));
    }
}

void LoadFieldsTest::useLeistungstraeger()
{
    QList<QSharedPointer<ebp::Leistungstraeger> > leistungstraegerList = ebp::Leistungstraeger::loadAll(aConnection);
    QVERIFY(leistungstraegerList.count()>1);
    for ( int i =0; i<leistungstraegerList.count();i++)
    {
        QCOMPARE(leistungstraegerList.at(i)->name(),QString("Testname"));

        QCOMPARE(leistungstraegerList.at(i)->strasse(),QString("Teststraße"));

        QCOMPARE(leistungstraegerList.at(i)->plz(),QString("88069"));

        QCOMPARE(leistungstraegerList.at(i)->ort(),QString("Testort"));

        QCOMPARE(leistungstraegerList.at(i)->ansprechpartner(),QString("Testansprechpartner"));

        QCOMPARE(leistungstraegerList.at(i)->telefon(),QString("000000"));

        QCOMPARE(leistungstraegerList.at(i)->fax(),QString("11111111"));

        QCOMPARE(leistungstraegerList.at(i)->email(),QString("test@Test.de"));

        QCOMPARE(leistungstraegerList.at(i)->anmerkung(),QString("Testanmerkung"));

        //QVERIFY(leistungstraegerList.at(i)->update(aConnection));
    }
}
void LoadFieldsTest::cleanupTestCase()
{
    aConnection.clear();
}

