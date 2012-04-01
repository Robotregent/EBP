#ifndef CONNECTIONTEST_H
#define CONNECTIONTEST_H

#include "AutoTest.h"

#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>
#include <EBPdb/Mitarbeiter.hxx>
#include <exception>

//Declaration
/** Testet das object-relational Mapping die Klasse Connection.
  *
  */
class ConnectionTest : public QObject
{
    Q_OBJECT
    QSharedPointer<ebp::connection> testCon;
private slots:
    void initTestCase();
    void establishCon();
    void loginMitarbeiter();
    void getAttributes();
    void cleanupTestCase();

};
DECLARE_TEST(ConnectionTest)
#endif // CONNECTIONTEST_H