#ifndef DOKUMENTATIONTEST_H
#define DOKUMENTATIONTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "AutoTest.h"
#include <EBPdb/connection.hxx>
#include <EBPdb/Dokumentation.hxx>
#include <EBPdb/Bewohner.hxx>
/** Testet das object-relational Mapping der Klasse Dokumentation.
  *
  */
class DokumentationTest : public QObject
{
    Q_OBJECT
    QSharedPointer<ebp::connection> aConnection;
    QSharedPointer<ebp::Dokumentation> aDoku;

private slots:
    void initTestCase();
    void bewohnerRelation();
    void testFields();
    void cleanupTestCase();

};
DECLARE_TEST(DokumentationTest)
#endif // DOKUMENTATIONTEST_H
