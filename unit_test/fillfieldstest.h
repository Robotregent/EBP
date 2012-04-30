#ifndef FILLFIELDSTEST_H
#define FILLFIELDSTEST_H
#include "AutoTest.h"
#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>
/**
  * \brief Testet das Befüllen der Datenbankfelder
  */
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
    void fillAbwesenheit();
    void fillProtokoll();
    void fillProjekt();
    void fillLeistungstraeger();
    void fillBetreuung();
    void cleanupTestCase();

};
DECLARE_TEST(FillFieldsTest)
#endif // FILLFIELDSTEST_H
