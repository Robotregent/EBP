#ifndef CREATETEST_H
#define CREATETEST_H

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

class CreateTest : public QObject
{
    Q_OBJECT
    QSharedPointer< ebp::connection > aConnection;


private slots:
    void initTestCase();
    void mitarbeiterTest();
    void bewohnerTest();
    void bewohnerereignisTest();
    void wohngruppeTest();
    void wohngruppenereignisTest();
    void dokumentationTest();
    void verfuegungTest();



};
DECLARE_TEST(CreateTest)
#endif // CREATETEST_H
