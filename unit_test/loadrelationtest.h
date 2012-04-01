#ifndef LOADRELATIONTEST_H
#define LOADRELATIONTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>
#include "AutoTest.h"

class LoadRelationTest : public QObject
{
    Q_OBJECT
    QSharedPointer< ebp::connection > aConnection;

private slots:
    void initTestCase();
    void loadMitarbeiter();
    void loadWohngruppenereignis();
    void loadBewohner();
    void loadBewohnerEreignis();
    void loadVerfuegung();
    void loadDokumentation();
    void loadAbwesenheit();
    void loadProtokoll();
    void loadProjekt();
    void loadLeistungstraeger();
    void cleanupTestCase();

};
DECLARE_TEST(LoadRelationTest)
#endif // LOADRELATIONTEST_H
