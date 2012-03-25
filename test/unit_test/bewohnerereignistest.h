#ifndef BEWOHNEREREIGNISTEST_H
#define BEWOHNEREREIGNISTEST_H

#include <QObject>
#include <QtTest>
#include "AutoTest.h"
#include <EBPdb/Bewohnerereignis.hxx>
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/connection.hxx>
/** Testet das object-relational Mapping die Klasse Bewohnerereignis.
  * Der Test für die Relation Bewohnerereignis <--> Bewohner ist Teil des
  * Tests BewohnerTest
  */
class BewohnerEreignisTest : public QObject
{
    Q_OBJECT
    QSharedPointer<ebp::connection> aConnection;
    QSharedPointer<ebp::Bewohnerereignis> aBeEreignis;

private slots:
    void initTestCase();
    void schreiberRelation();
    void testFields();
    void cleanupTestCase();


};
DECLARE_TEST(BewohnerEreignisTest)
#endif // BEWOHNEREREIGNISTEST_H
