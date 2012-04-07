#ifndef REMOVETEST_H
#define REMOVETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>
#include "AutoTest.h"

class RemoveTest : public QObject
{
    Q_OBJECT
    QSharedPointer< ebp::connection > aConnection;
private slots:
    void initTestCase();
    void removeMitarbeiter();
    void removeBewohner();
    void removeBewohnerereignis();
    void removeWohngruppe();
    void removeWohngruppenereignis();
    void removeDokumentation();
    void removeVerfuegung();
    void removeAbwesenheit();
    void removeProtokoll();
    void removeProjekt();
    void removeLeistungstraeger();
    void removeBetreung();
    void cleanupTestCase();
};
DECLARE_TEST(RemoveTest)

#endif // REMOVETEST_H
