#ifndef LOADFILDSTEST_H
#define LOADFILDSTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>
#include "AutoTest.h"

class LoadFieldsTest : public QObject
{
    Q_OBJECT
    QSharedPointer< ebp::connection > aConnection;

private slots:
    void initTestCase();
    void useMitarbeiter();
    void useWohngruppenereignis();
    void useBewohner();
    void useBewohnerEreignis();
    void useVerfuegung();
    void useDokumentation();
    void useAbwesenheit();
    void useProtokoll();
    void useProjekt();
    void useLeistungstraeger();
    void useBetreuung();
    void useConnections();
    void cleanupTestCase();

};
DECLARE_TEST(LoadFieldsTest)
#endif // LOADFILDSTEST_H
