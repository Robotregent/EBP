#include "removetest.h"
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

void RemoveTest::initTestCase()
{
    aConnection = QSharedPointer< ebp::connection >( new ebp::connection("ebp_test_root", "ebp_test", "localhost", 3306));
    QVERIFY(aConnection->establish("ebp_test_root"));
}

void RemoveTest::removeMitarbeiter()
{
    QList< QSharedPointer < ebp::Mitarbeiter > > maList = ebp::Mitarbeiter::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Mitarbeiter > ma, maList )
    {
        QVERIFY(ma->remove(aConnection));
    }
}

void RemoveTest::removeBewohner()
{
    QList< QSharedPointer < ebp::Bewohner > > bList = ebp::Bewohner::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Bewohner > b, bList )
    {
        QVERIFY(b->remove(aConnection));
    }
}

void RemoveTest::removeBewohnerereignis()
{
    QList< QSharedPointer < ebp::Bewohner > > beList = ebp::Bewohner::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Bewohner > be, beList )
    {
        QVERIFY(be->remove(aConnection));
    }
}

void RemoveTest::removeWohngruppe()
{
    QList< QSharedPointer < ebp::Wohngruppe > >wgList = ebp::Wohngruppe::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Wohngruppe > wg, wgList )
    {
        QVERIFY(wg->remove(aConnection));
    }
}

void RemoveTest::removeWohngruppenereignis()
{
    QList< QSharedPointer < ebp::Wohngruppenereignis > >wgList = ebp::Wohngruppenereignis::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Wohngruppenereignis > wg, wgList )
    {
        QVERIFY(wg->remove(aConnection));
    }
}

void RemoveTest::removeDokumentation()
{
    QList< QSharedPointer < ebp::Dokumentation > > dokuList = ebp::Dokumentation::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Dokumentation > doku, dokuList )
    {
        QVERIFY(doku->remove(aConnection));
    }
}

void RemoveTest::removeVerfuegung()
{
    QList< QSharedPointer < ebp::Verfuegung > > vList = ebp::Verfuegung::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Verfuegung > v, vList )
    {
        QVERIFY(v->remove(aConnection));
    }

}

void RemoveTest::removeAbwesenheit()
{
    QList< QSharedPointer < ebp::Abwesenheit > > aList = ebp::Abwesenheit::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Abwesenheit > a, aList )
    {
        QVERIFY(a->remove(aConnection));
    }
}

void RemoveTest::removeProtokoll()
{
    QList< QSharedPointer < ebp::Protokoll > > pList = ebp::Protokoll::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Protokoll > p, pList )
    {
        QVERIFY(p->remove(aConnection));
    }
}

void RemoveTest::removeProjekt()
{
    QList< QSharedPointer < ebp::Projekt > > pList = ebp::Projekt::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Projekt > p, pList )
    {
        QVERIFY(p->remove(aConnection));
    }
}

void RemoveTest::removeLeistungstraeger()
{
    QList< QSharedPointer < ebp::Leistungstraeger > > lList = ebp::Leistungstraeger::loadAll(aConnection);
    foreach (const QSharedPointer < ebp::Leistungstraeger > l, lList )
    {
        QVERIFY(l->remove(aConnection));
    }
}
void RemoveTest::cleanupTestCase()
{
    aConnection.clear();
}
