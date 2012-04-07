#ifndef LINKTEST_H
#define LINKTEST_H

#include "AutoTest.h"

#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>

class LinkTest : public QObject
{
    Q_OBJECT
    QSharedPointer< ebp::connection > aConnection;

private slots:
    void initTestCase();
    void linkWohngruppe();
    void linkWohngruppenereignis();
    void linkBewohner();
    void linkBewohnerEreignis();
    void linkVerfuegung();
    void linkDokumentation();
    void linkAbwesenheit();
    void linkProtokoll();
    void linkLeistungstraeger();
    void linkProjekt();
    void linkBetreuung();
    void cleanupTestCase();

};
DECLARE_TEST(LinkTest)
#endif // LINKTEST_H
