#ifndef UNLINKTEST_H
#define UNLINKTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "AutoTest.h"
#include <EBPdb/connection.hxx>

class UnlinkTest : public QObject
{
    Q_OBJECT
    QSharedPointer< ebp::connection > aConnection;

private slots:
    void initTestCase();
    void unlinkWohngruppe();
    void unlinkWohngruppenereignis();
    void unlinkBewohner();
    void unlinkBewohnerEreignis();
    void unlinkVerfuegung();
    void unlinkDokumentation();
    void unlinkAbwesenheit();
    void unlinkProtokoll();
    void unlinkLeistungstraeger();
    void unlinkProjekt();
    void unlinkBetreuung();
    void cleanupTestCase();

};
DECLARE_TEST(UnlinkTest)

#endif // UNLINKTEST_H
