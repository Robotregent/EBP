#ifndef BEWOHNERTEST_H
#define BEWOHNERTEST_H

#include <QObject>
#include "AutoTest.h"
#include <QtTest/QtTest>
#include <EBPdb/Bewohner.hxx>
/** Testet das object-relational Mapping die Klasse Bewohner.
  *
  */
class BewohnerTest : public QObject
{
    Q_OBJECT

private:
    QSharedPointer<ebp::connection> aConnection;
    QSharedPointer<ebp::Bewohner> aBewohner;
private slots:
    void initTestCase();

    void wohngruppenRelation();
    void bezugsbetreuungRelation();
    void projektRelation();
    void protokollRelation();
    void ereignisRelation();
    void AbwesenheitRealtion();
    void fields();

    void cleanupTestCase();

};
DECLARE_TEST(BewohnerTest)
#endif // BEWOHNERTEST_H
