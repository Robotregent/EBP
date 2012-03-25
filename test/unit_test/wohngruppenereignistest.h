#ifndef WOHNGRUPPENEREIGNISTEST_H
#define WOHNGRUPPENEREIGNISTEST_H

#include <QObject>
#include <QtTest>
#include "AutoTest.h"
#include <EBPdb/Bewohnerereignis.hxx>
#include <EBPdb/connection.hxx>
#include <EBPdb/Wohngruppe.hxx>
/** Testet das object-relational Mapping die Klasse Wohngruppenereignis.
  * Der Test für die Relation Wohngruppenereignis <--> Bewohner ist Teil des
  * Tests BewohnerTest
  */
class WohngruppenEreignisTest : public QObject
{
    Q_OBJECT
    QSharedPointer<ebp::connection> aConnection;
    QSharedPointer<ebp::Wohngruppenereignis> aWgEreignis;

private slots:
    void initTestCase();
    void schreiberRelation();
    void testFields();
    void cleanupTestCase();

};
DECLARE_TEST(WohngruppenEreignisTest)
#endif // WOHNGRUPPENEREIGNISTEST_H
