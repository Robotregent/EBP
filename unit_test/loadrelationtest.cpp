#include "loadrelationtest.h"
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

void LoadRelationTest::initTestCase()
{
    aConnection = QSharedPointer< ebp::connection >( new ebp::connection("ebp_test_root", "ebp_test", "localhost", 3306));

    QVERIFY(aConnection->establish("ebp_test_root"));
}

void LoadRelationTest::loadMitarbeiter()
{
    QList < QSharedPointer < ebp::Mitarbeiter > > maList = ebp::Mitarbeiter::loadAll(aConnection);
    QList < QSharedPointer < ebp::Bewohnerereignis > > beList;
    QList < QSharedPointer < ebp::Projekt > > projekteList;
    QList < QSharedPointer < ebp::Wohngruppenereignis > > wgeList;
    QList < QSharedPointer < ebp::Protokoll > > teilnehmerList;
    QList < QSharedPointer < ebp::Protokoll > > schreiberList;
    QList < QSharedPointer < ebp::Bewohner > > bewohnerList;
    QList < QSharedPointer < ebp::Wohngruppe > > gruppenList;


    bool beIsLinked = false, projektIsLinked = false, wgeIsLinked = false, teilnehmerIsLinked = false,
            schreiberIsLinked = false, bewohnerIsLinked = false, gruppeIsLinked = false;

    foreach (const QSharedPointer < ebp::Mitarbeiter >  ma, maList)
    {
        beList = ma->loadBewohnerereignisse(aConnection);
        if (beList.count()>0)
            beIsLinked = true;

        projekteList = ma->loadProjekte(aConnection);
        if (projekteList.count()>0)
            projektIsLinked = true;

        wgeList = ma->loadWohngruppenereignisse(aConnection);
        if ( wgeList.count()>0)
            wgeIsLinked = true;

        schreiberList = ma->loadProtokollSchreiber(aConnection);
        if(schreiberList.count()>0)
            schreiberIsLinked = true;

        teilnehmerList = ma->loadProtokollTeilnehmer(aConnection);
        if(teilnehmerList.count()>0)
            teilnehmerIsLinked = true;

        bewohnerList = ma->loadBezugsbetreuer(aConnection);
        if(bewohnerList.count()>0)
            bewohnerIsLinked = true;

        gruppenList = ma->loadWohngruppen(aConnection);
        if (gruppenList.count()>0)
            gruppeIsLinked = true;
    }


    QVERIFY(beIsLinked);
    QVERIFY(projektIsLinked);
    QVERIFY(wgeIsLinked);
    QVERIFY(schreiberIsLinked);
    QVERIFY(teilnehmerIsLinked);
    QVERIFY(bewohnerIsLinked);
    QVERIFY(gruppeIsLinked);
}

void LoadRelationTest::loadWohngruppenereignis()
{
    QList < QSharedPointer < ebp::Wohngruppenereignis > > wgeList = ebp::Wohngruppenereignis::loadAll(aConnection);
    QList < QSharedPointer < ebp::Mitarbeiter > > maList;
    QSharedPointer < ebp::Wohngruppe > gruppe;
    foreach (const QSharedPointer< ebp::Wohngruppenereignis > wge, wgeList )
    {
        gruppe=wge->wohngruppe();
        QVERIFY(!gruppe.isNull());

        maList = wge->loadSchreiber(aConnection);
        QVERIFY(maList.count()>0);
    }
}

void LoadRelationTest::loadBewohner()
{
    QList < QSharedPointer < ebp::Bewohner > > bList = ebp::Bewohner::loadAll(aConnection);
    QSharedPointer < ebp::Wohngruppe > gruppe;
    QSharedPointer < ebp::Mitarbeiter > betreuer;
    QList < QSharedPointer < ebp::Projekt > > projekteList;
    QList < QSharedPointer < ebp::Protokoll > > protokollList;
    QList < QSharedPointer < ebp::Bewohnerereignis > > ereignisseList;
    QList < QSharedPointer < ebp::Abwesenheit > > abwesenheitList;
    QList < QSharedPointer < ebp::Verfuegung > > verfuegungenList;
    QList < QSharedPointer < ebp::Dokumentation > > dokumentationList;
    QList < QSharedPointer < ebp::Leistungstraeger > > leistungstraegerList;

    bool projektIsLinked = false, protokollIsLinked = false, ereignisIsLinked = false,
            abwesenheitIsLinked = false, verfuegungIsLinked = false,
            dokumentationIsLinked = false, leistungstraegerIsLinked = false;

    foreach (const QSharedPointer< ebp::Bewohner > b, bList )
    {
        gruppe = b->wohngruppe();
        QVERIFY(!gruppe.isNull());

        betreuer = b->bezugsbetreuer();
        QVERIFY(!betreuer.isNull());

        projekteList = b->loadProjekte(aConnection);
        if(projekteList.count()>0)
            projektIsLinked = true;

        protokollList = b->loadProtokolle(aConnection);
        if(protokollList.count()>0)
            protokollIsLinked = true;

        ereignisseList = b->loadEreignisse(aConnection);
        if(ereignisseList.count()>0)
            ereignisIsLinked = true;

        abwesenheitList = b->loadAbwesenheiten(aConnection);
        if(abwesenheitList.count()>0)
            abwesenheitIsLinked = true;

        verfuegungenList = b->loadVerfuegungen(aConnection);
        if (verfuegungenList.count()>0)
            verfuegungIsLinked = true;

        dokumentationList = b->loadDokumentationen(aConnection);
        if (dokumentationList.count()>0)
            dokumentationIsLinked = true;

        leistungstraegerList = b->loadLeistungstraeger(aConnection);
        if(leistungstraegerList.count()>0)
            leistungstraegerIsLinked = true;
    }
    QVERIFY(projektIsLinked);
    QVERIFY(protokollIsLinked);
    QVERIFY(ereignisIsLinked);
    QVERIFY(abwesenheitIsLinked);
    QVERIFY(verfuegungIsLinked);
    QVERIFY(dokumentationIsLinked);
    QVERIFY(leistungstraegerIsLinked);

}

void LoadRelationTest::loadBewohnerEreignis()
{
    QList < QSharedPointer < ebp::Bewohnerereignis > > ereignisseList = ebp::Bewohnerereignis::loadAll(aConnection);
    QList < QSharedPointer < ebp::Mitarbeiter > > maList;
    QSharedPointer < ebp::Bewohner > bewohner;

    foreach ( const QSharedPointer < ebp::Bewohnerereignis > be, ereignisseList)
    {
        maList = be->loadSchreiber(aConnection);
        QVERIFY(maList.count()>0);

        bewohner = be->bewohner();
        QVERIFY(!be.isNull());
    }
}

void LoadRelationTest::loadVerfuegung()
{
    QList < QSharedPointer < ebp::Verfuegung > > verfuegungList = ebp::Verfuegung::loadAll(aConnection);
    QSharedPointer < ebp::Bewohner > bewohner;
    foreach ( const QSharedPointer < ebp::Verfuegung > v, verfuegungList)
    {
        bewohner = v->bewohner();
        QVERIFY(!bewohner.isNull());
    }
}

void LoadRelationTest::loadDokumentation()
{
    QList < QSharedPointer < ebp::Dokumentation > > dokuList = ebp::Dokumentation::loadAll(aConnection);
    QSharedPointer < ebp::Bewohner > bewohner;
    foreach ( const QSharedPointer < ebp::Dokumentation > d, dokuList)
    {
        bewohner = d->bewohner();
        QVERIFY(!bewohner.isNull());
    }
}

void LoadRelationTest::loadAbwesenheit()
{
    QList < QSharedPointer < ebp::Abwesenheit > > abwesenheitsList = ebp::Abwesenheit::loadAll(aConnection);
    QSharedPointer < ebp::Bewohner > bewohner;
    foreach ( const QSharedPointer < ebp::Abwesenheit > a, abwesenheitsList)
    {
        bewohner = a->bewohner();
        QVERIFY(!bewohner.isNull());
    }
}

void LoadRelationTest::loadProtokoll()
{
    QList < QSharedPointer < ebp::Protokoll > > protokollList = ebp::Protokoll::loadAll(aConnection);
    QList < QSharedPointer < ebp::Mitarbeiter > > schreiberList;
    QList < QSharedPointer < ebp::Mitarbeiter > > teilnehmerList;
    QSharedPointer < ebp::Bewohner > bewohner;

    bool schreiberIsLinked = false, teilnehmerIsLinked = false;

    foreach ( const QSharedPointer < ebp::Protokoll > p, protokollList)
    {
        bewohner = p->bewohner();
        QVERIFY(!bewohner.isNull());

        schreiberList = p->loadSchreiber(aConnection);
        if(schreiberList.count()>0)
            schreiberIsLinked = true;

        teilnehmerList = p->loadTeilnehmer(aConnection);
        if(teilnehmerList.count()>0)
            teilnehmerIsLinked = true;
    }
    QVERIFY(schreiberIsLinked);
    QVERIFY(teilnehmerIsLinked);
}

void LoadRelationTest::loadProjekt()
{
    QList < QSharedPointer < ebp::Projekt > > projektList = ebp::Projekt::loadAll(aConnection);
    QList < QSharedPointer < ebp::Mitarbeiter > > verantwortlicheList;;
    QSharedPointer < ebp::Bewohner > bewohner;

    bool verantwortlicherIsLinked = false;

    foreach ( const QSharedPointer < ebp::Projekt > p, projektList)
    {
        bewohner = p->bewohner();
        QVERIFY(!bewohner.isNull());

        verantwortlicheList = p->loadVerantwortliche(aConnection);
        if(verantwortlicheList.count()>0)
            verantwortlicherIsLinked = true;
    }
    QVERIFY(verantwortlicherIsLinked);
}

void LoadRelationTest::loadLeistungstraeger()
{
    QList < QSharedPointer < ebp::Leistungstraeger > > leistungstraegerList = ebp::Leistungstraeger::loadAll(aConnection);
    QList < QSharedPointer < ebp::Bewohner > > bewohnerList;
    bool bewohnerIsLinked = false;
    foreach ( const QSharedPointer < ebp::Leistungstraeger > l, leistungstraegerList)
    {
        bewohnerList = l->loadBewohner(aConnection);
        if(bewohnerList.count()>0)
            bewohnerIsLinked = true;
    }
    QVERIFY(bewohnerIsLinked);
}

void LoadRelationTest::loadBetreuung()
{
    QList < QSharedPointer < ebp::Betreuung > > betreuungList = ebp::Betreuung::loadAll(aConnection);
    QSharedPointer < ebp::Bewohner > bewohner;
    foreach ( QSharedPointer< ebp::Betreuung > b, betreuungList)
    {
	bewohner = b->bewohner();
	QVERIFY(!bewohner.isNull());
    }

}

void LoadRelationTest::cleanupTestCase()
{
    aConnection.clear();
}

