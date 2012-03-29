#ifndef FILLFIELDSTEST_H
#define FILLFIELDSTEST_H
#include "AutoTest.h"
#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>
class FillFieldsTest : public QObject
{
    Q_OBJECT
    QSharedPointer< ebp::connection > aConnection;

private slots:
    void initTestCase();
    void fillMitarbeiter();
    void fillWohngruppenereignis();
    void fillBewohner();
    void fillBewohnerEreignis();
    void fillVerfuegung();
    void fillDokumentation();

};
DECLARE_TEST(FillFieldsTest)
#endif // FILLFIELDSTEST_H
