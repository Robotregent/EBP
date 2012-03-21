#ifndef MITARBEITERTEST_H
#define MITARBEITERTEST_H
#include "AutoTest.h"
#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>
#include <EBPdb/Mitarbeiter.hxx>


class MitarbeiterTest : public QObject
{
    Q_OBJECT
    QSharedPointer<ebp::connection> testCon;
    QSharedPointer<ebp::Mitarbeiter> aMitarbeiter;
private slots:
    void initTestCase();
    void testCreateNewMitarbeiter();
    void testSetAndGetAttributes();
    void updatePasswort();
    void cleanupTestCase();

};
DECLARE_TEST(MitarbeiterTest)

#endif // MITARBEITERTEST_H
