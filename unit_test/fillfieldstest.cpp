#include "fillfieldstest.h"
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Verfuegung.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Bewohnerereignis.hxx>
#include <EBPdb/Wohngruppe.hxx>
#include <EBPdb/Wohngruppenereignis.hxx>
#include <EBPdb/Dokumentation.hxx>
void FillFieldsTest::initTestCase()
{
    aConnection = QSharedPointer< ebp::connection >( new ebp::connection("ebp_test_root", "ebp_test", "localhost", 3306));
    QVERIFY(aConnection->establish("ebp_test_root"));
}

void FillFieldsTest::fillMitarbeiter()
{
    QList<QSharedPointer<ebp::Mitarbeiter> > maList = ebp::Mitarbeiter::loadAll(aConnection);
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
    for ( int i =0; i<wohngruppenEreignisList.count();i++)
    {
	wohngruppenEreignisList.at(i)->text("Testtext"+QVariant(i).toString());

	wohngruppenEreignisList.at(i)->zeitpunkt(QDateTime::currentDateTime());

	QVERIFY(wohngruppenEreignisList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillBewohner()
{
    QList<QSharedPointer<ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);
    for ( int i =0; i<bewohnerList.count();i++)
    {
	bewohnerList.at(i)->geburtsdatum(QDate::currentDate());

	bewohnerList.at(i)->seit(QDate::currentDate());

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
    for ( int i =0; i<bewohnerEreignisList.count();i++)
    {
	bewohnerEreignisList.at(i)->zeitpunkt(QDateTime::currentDateTime());

	bewohnerEreignisList.at(i)->text("Testtext"+QVariant(i).toString());

	QVERIFY(bewohnerEreignisList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillVerfuegung()
{
    QList<QSharedPointer<ebp::Verfuegung> > vList = ebp::Verfuegung::loadAll(aConnection);
    for ( int i =0; i<vList.count();i++)
    {
	vList.at(i)->typ(ebp::Verfuegung::Patientenverfuegung);

	vList.at(i)->grund("Grund"+QVariant(i).toString());

	vList.at(i)->gerichtsbescheid(QDate::currentDate());

	QVERIFY(vList.at(i)->update(aConnection));
    }
}

void FillFieldsTest::fillDokumentation()
{
    QList<QSharedPointer<ebp::Dokumentation> > dokuList = ebp::Dokumentation::loadAll(aConnection);
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
