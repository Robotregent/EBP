#include "fillfieldstest.h"
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
void FillFieldsTest::initTestCase()
{
    aConnection = QSharedPointer< ebp::connection >( new ebp::connection("ebp_test_root", "ebp_test", "localhost", 3306));

    QVERIFY(aConnection->establish("ebp_test_root"));
}

void FillFieldsTest::fillMitarbeiter()
{
    QList<QSharedPointer<ebp::Mitarbeiter> > maList = ebp::Mitarbeiter::loadAll(aConnection);
    QVERIFY(maList.count()>1);
    for ( int i =0; i<maList.count();i++)
    {
	maList.at(i)->name(QVariant(i).toString()+"Mitarbeiter");

	maList.at(i)->berechtigung(ebp::Mitarbeiter::WohngruppenRecht);

	maList.at(i)->email("test"+QVariant(i).toString()+"@mail");

	maList.at(i)->telefon(QVariant(i).toString());

	QVERIFY(maList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillWohngruppenereignis()
{
    QList<QSharedPointer<ebp::Wohngruppenereignis> > wohngruppenEreignisList = ebp::Wohngruppenereignis::loadAll(aConnection);
    QVERIFY(wohngruppenEreignisList.count()>1);
    for ( int i =0; i<wohngruppenEreignisList.count();i++)
    {
	wohngruppenEreignisList.at(i)->text("Testtext"+QVariant(i).toString());

        wohngruppenEreignisList.at(i)->zeitpunkt(QDateTime(QDate(2012,4,1),QTime(11,11)));

	QVERIFY(wohngruppenEreignisList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillBewohner()
{
    QList<QSharedPointer<ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);

    QVERIFY(bewohnerList.count()>1);

    for ( int i =0; i<bewohnerList.count();i++)
    {
        bewohnerList.at(i)->geburtsdatum(QDate(2012,4,1));

        bewohnerList.at(i)->seit(QDate(2012,4,1));

	bewohnerList.at(i)->anrede("anrede"+QVariant(i).toString());

	bewohnerList.at(i)->vorname("vorname"+QVariant(i).toString());

	bewohnerList.at(i)->nachname("nachname"+QVariant(i).toString());

	bewohnerList.at(i)->geburtsort("geburtsort"+QVariant(i).toString());

	bewohnerList.at(i)->telefon("telefon"+QVariant(i).toString());

	bewohnerList.at(i)->email("eMail"+QVariant(i).toString());

	bewohnerList.at(i)->familienstatus("familienstatus"+QVariant(i).toString());

	bewohnerList.at(i)->konfession("konfession"+QVariant(i).toString());

	bewohnerList.at(i)->staat("staat"+QVariant(i).toString());

	bewohnerList.at(i)->anmerkung("anmerkung"+QVariant(i).toString());

	QVERIFY(bewohnerList.at(i)->update(aConnection));

    }
}

void FillFieldsTest::fillBewohnerEreignis()
{
    QList<QSharedPointer<ebp::Bewohnerereignis> > bewohnerEreignisList = ebp::Bewohnerereignis::loadAll(aConnection);
    QVERIFY(bewohnerEreignisList.count()>1);
    for ( int i =0; i<bewohnerEreignisList.count();i++)
    {
        bewohnerEreignisList.at(i)->zeitpunkt(QDateTime(QDate(2012,4,1),QTime(11,11)));

	bewohnerEreignisList.at(i)->text("Testtext"+QVariant(i).toString());

	QVERIFY(bewohnerEreignisList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillVerfuegung()
{
    QList<QSharedPointer<ebp::Verfuegung> > vList = ebp::Verfuegung::loadAll(aConnection);
    QVERIFY(vList.count()>1);
    for ( int i =0; i<vList.count();i++)
    {
	vList.at(i)->typ(ebp::Verfuegung::Patientenverfuegung);

	vList.at(i)->grund("Grund"+QVariant(i).toString());

        vList.at(i)->gerichtsbescheid(QDate(2012,4,1));

	QVERIFY(vList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillDokumentation()
{
    QList<QSharedPointer<ebp::Dokumentation> > dokuList = ebp::Dokumentation::loadAll(aConnection);
    QVERIFY(dokuList.count()>1);
    for ( int i =0; i<dokuList.count();i++)
    {
	dokuList.at(i)->typ(ebp::Dokumentation::partnerschaften);

	dokuList.at(i)->einstufung(ebp::Dokumentation::bekommeBeratung);

	dokuList.at(i)->beschreibung("Testbeschreibung_"+QVariant(i).toString());

	dokuList.at(i)->erlaeuterungen("Testerläuterung"+QVariant(i).toString());

	dokuList.at(i)->ziele("TestZiele"+QVariant(i).toString());
	QVERIFY(dokuList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillAbwesenheit()
{
    QList<QSharedPointer<ebp::Abwesenheit> > abwesenheitsList = ebp::Abwesenheit::loadAll(aConnection);
    QVERIFY(abwesenheitsList.count()>1);
    for ( int i =0; i<abwesenheitsList.count();i++)
    {
        abwesenheitsList.at(i)->grund("Testgrund");

        abwesenheitsList.at(i)->tag(QDate(2012,4,1));

        QVERIFY(abwesenheitsList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillProtokoll()
{
    QList<QSharedPointer<ebp::Protokoll> > protokollList = ebp::Protokoll::loadAll(aConnection);
    QVERIFY(protokollList.count()>1);
    for ( int i =0; i<protokollList.count();i++)
    {
        protokollList.at(i)->datum(QDate(2012,4,1));

        protokollList.at(i)->inhalt("VIEl Testinhalt");

        QVERIFY(protokollList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillProjekt()
{
    QList<QSharedPointer<ebp::Projekt> > projektList = ebp::Projekt::loadAll(aConnection);
    QVERIFY(projektList.count()>1);
    for ( int i =0; i<projektList.count();i++)
    {
        projektList.at(i)->beginn(QDate(2012,4,1));

        projektList.at(i)->ende(QDate(2012,4,1));

        projektList.at(i)->name("Testname");

        projektList.at(i)->beschreibung("Lange Testbeschreibung");

        projektList.at(i)->typ("TestTyp");

	projektList.at(i)->ziele("TestZiele");

        QVERIFY(projektList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillLeistungstraeger()
{
    QList<QSharedPointer<ebp::Leistungstraeger> > leistungstraegerList = ebp::Leistungstraeger::loadAll(aConnection);
    QVERIFY(leistungstraegerList.count()>1);
    for ( int i =0; i<leistungstraegerList.count();i++)
    {
        leistungstraegerList.at(i)->name("Testname");

        leistungstraegerList.at(i)->strasse("Teststraße");

        leistungstraegerList.at(i)->plz("88069");

        leistungstraegerList.at(i)->ort("Testort");

        leistungstraegerList.at(i)->ansprechpartner("Testansprechpartner");

        leistungstraegerList.at(i)->telefon("000000");

        leistungstraegerList.at(i)->fax("11111111");

        leistungstraegerList.at(i)->email("test@Test.de");

        leistungstraegerList.at(i)->anmerkung("Testanmerkung");

        QVERIFY(leistungstraegerList.at(i)->update(aConnection));
    }
}
void FillFieldsTest::cleanupTestCase()
{
    aConnection.clear();
}
