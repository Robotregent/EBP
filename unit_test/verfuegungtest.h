#ifndef VERFUEGUNGTEST_H
#define VERFUEGUNGTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "AutoTest.h"
#include <EBPdb/connection.hxx>
#include <EBPdb/Verfuegung.hxx>
#include <EBPdb/Bewohner.hxx>
class VerfuegungTest : public QObject
{
    Q_OBJECT
    QSharedPointer<ebp::connection> aConnection;
    QSharedPointer<ebp::Verfuegung> aVerfuegung;


private slots:
    void initTestCase();
    void bewohnerRelation();
    void testFields();
    void cleanupTestCase();

};
DECLARE_TEST(VerfuegungTest)

#endif // VERFUEGUNGTEST_H
