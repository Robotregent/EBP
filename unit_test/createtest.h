#ifndef CREATETEST_H
#define CREATETEST_H

#include "AutoTest.h"

#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>

/**
  * \brief Testet das Erstellen der Datenbankobjekte
  */
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
    void Abwesenheit();
    void Protokoll();
    void Projekt();
    void Leistungstraeger();
    void Betreuung();
    void Connection();
    void cleanupTestCase();



};
DECLARE_TEST(CreateTest)
#endif // CREATETEST_H
