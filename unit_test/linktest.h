#ifndef LINKTEST_H
#define LINKTEST_H

#include "AutoTest.h"

#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Verfuegung.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Bewohnerereignis.hxx>
#include <EBPdb/Wohngruppe.hxx>
#include <EBPdb/Wohngruppenereignis.hxx>
#include <EBPdb/Dokumentation.hxx>

class LinkTest : public QObject
{
    Q_OBJECT
    QSharedPointer< ebp::connection > aConnection;

private slots:
    void initTestCase();
    void linkMitarbeiter();
    void linkWohngruppenereignis();
    void linkBewohner();
    void linkBewohnerEreignis();
    void linkVerfuegung();
    void linkDokumentation();

};
DECLARE_TEST(LinkTest)
#endif // LINKTEST_H
