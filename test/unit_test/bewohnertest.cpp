#include "bewohnertest.h"
#include <EBPdb/connection.hxx>
#include <EBPdb/Wohngruppe.hxx>
#include <EBPdb/Bewohnerereignis.hxx>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
  * \brief Initialisiert Connection und Bewohner
  */
void BewohnerTest::initTestCase()
{
    aConnection = QSharedPointer<ebp::connection> ( new ebp::connection("testUser","testDB"));
    QVERIFY(!aConnection.isNull());
    aConnection->establish("test");
    srand ( time(NULL) );
    aBewohner = QSharedPointer<ebp::Bewohner>( new ebp::Bewohner(rand() % 100000 + 1));
    QVERIFY(!aBewohner.isNull());
    aBewohner->create(aConnection);
}
/**
  * \brief Testet das Erstellen den Relation Bewohner <-1- -1-> Wohngruppe
  */
void BewohnerTest::wohngruppenRelation()
{
    QList< QSharedPointer<ebp::Wohngruppe> > wgList = ebp::Wohngruppe::loadAll(aConnection);
    if(wgList.count()<1)
        return;

    // Relation Bewohner - Wohngruppe erstellen und prüfen
    ebp::Bewohner::linkWohngruppe(aBewohner,wgList.first());
    aBewohner->update(aConnection);

    QSharedPointer< ebp::Wohngruppe > wgLink = aBewohner->wohngruppe();
    QVERIFY(wgLink->name()==wgList.first()->name());

    //Relation wieder auflösen
    ebp::Bewohner::unlinkWohngruppe(aBewohner,wgList.first());
    aBewohner->update(aConnection);

    QSharedPointer< ebp::Wohngruppe > wgUnlink = aBewohner->wohngruppe();
    QVERIFY(wgUnlink.isNull());
}
/**
  * \brief Testet das Erstellen den Relation Bewohner <-1- -1-> Mitarbeiter
  */
void BewohnerTest::bezugsbetreuungRelation()
{
    QList< QSharedPointer<ebp::Mitarbeiter> > maList = ebp::Mitarbeiter::loadAll(aConnection);
    if(maList.count()<1)
        return;

    // Relation Bewohner - Mitarbeiter erstellen und prüfen
    ebp::Bewohner::linkBezugsbetreuer(aBewohner,maList.first());
    aBewohner->update(aConnection);

    QSharedPointer< ebp::Mitarbeiter > maLink = aBewohner->bezugsbetreuer();
    QVERIFY(maLink->login()==maList.first()->login());

    //Relation wieder auflösen
    ebp::Bewohner::unlinkBezugsbetreuer(aBewohner,maList.first());
    aBewohner->update(aConnection);

    QSharedPointer< ebp::Mitarbeiter > maUnlink = aBewohner->bezugsbetreuer();
    QVERIFY(maUnlink.isNull());
}
/**
  * \brief Testet das Erstellen den Relation Bewohner <-1- -n-> Projekt
  */
void BewohnerTest::projektRelation()
{
    QSharedPointer< ebp::Projekt > newProjekt =
            QSharedPointer< ebp::Projekt >(new ebp::Projekt("testProjekt","ProjektBeschreibung","TestTyp",QDate::currentDate(),QDate::currentDate()));

    newProjekt->create(aConnection);
    newProjekt->update(aConnection);
    // Relation Bewohner - Projekt testen
    ebp::Projekt::linkBewohner(newProjekt,aBewohner);
    newProjekt->update(aConnection);
    QList < QSharedPointer< ebp::Projekt > > projects = aBewohner->loadProjekte(aConnection);
    QVERIFY(projects.count()>0);

    // Relation wieder lösen
    ebp::Projekt::unlinkBewohner(newProjekt,aBewohner);
    newProjekt->update(aConnection);
    projects = aBewohner->loadProjekte(aConnection);
    QVERIFY(projects.count()==0);

    //aufräumen
    newProjekt->remove(aConnection);

}
/**
  * \brief Testet das Erstellen den Relation Bewohner <-1- -n-> Protokoll
  */
void BewohnerTest::protokollRelation()
{
    QSharedPointer< ebp::Protokoll > newProtokoll =
            QSharedPointer< ebp::Protokoll >(new ebp::Protokoll("Viel Testinhalt",QDate::currentDate()));

    newProtokoll->create(aConnection);
    newProtokoll->update(aConnection);
    // Relation Bewohner - Protokoll testen
    ebp::Protokoll::linkBewohner(newProtokoll,aBewohner);
    newProtokoll->update(aConnection);


    QList < QSharedPointer< ebp::Protokoll > > protokolls = aBewohner->loadProtokolle(aConnection);
    QVERIFY(protokolls.count()>0);

    // Relation wieder lösen
    ebp::Protokoll::unlinkBewohner(newProtokoll,aBewohner);
    newProtokoll->update(aConnection);
    protokolls = aBewohner->loadProtokolle(aConnection);
    QVERIFY(protokolls.count()==0);

    //aufräumen
    newProtokoll->remove(aConnection);

}
/**
  * \brief Testet das Erstellen den Relation Bewohner <-1- -n-> Bewohnerereignis
  */
void BewohnerTest::ereignisRelation()
{
    QSharedPointer< ebp::Bewohnerereignis > newEreignis =
            QSharedPointer< ebp::Bewohnerereignis >(new ebp::Bewohnerereignis(QDateTime::currentDateTime(),"Ereignis Testtext"));

    newEreignis->create(aConnection);
    newEreignis->update(aConnection);
    // Relation Bewohner - Bewohnerereignis testen
    ebp::Bewohnerereignis::linkBewohner(newEreignis,aBewohner);
    newEreignis->update(aConnection);


    QList < QSharedPointer< ebp::Bewohnerereignis > > ereignisse = aBewohner->loadEreignisse(aConnection);
    QVERIFY(ereignisse.count()>0);

    // Relation wieder lösen
    ebp::Bewohnerereignis::unlinkBewohner(newEreignis,aBewohner);
    newEreignis->update(aConnection);
    ereignisse = aBewohner->loadEreignisse(aConnection);
    QVERIFY(ereignisse.count()==0);

    //aufräumen
    newEreignis->remove(aConnection);

}
/**
  * \brief Testet das Erstellen den Relation Bewohner <-1- -n-> Abwesenheit
  */
void BewohnerTest::AbwesenheitRealtion()
{
    QSharedPointer< ebp::Abwesenheit > newAbwesenheit =
            QSharedPointer< ebp::Abwesenheit >(new ebp::Abwesenheit(QDate::currentDate(),"Testgrund"));

    newAbwesenheit->create(aConnection);
    newAbwesenheit->update(aConnection);
    // Relation Bewohner - Abwesenheit testen
    ebp::Abwesenheit::linkBewohner(newAbwesenheit,aBewohner);
    newAbwesenheit->update(aConnection);


    QList < QSharedPointer< ebp::Abwesenheit > > abwesenheiten = aBewohner->loadAbwesenheiten(aConnection);
    QVERIFY(abwesenheiten.count()>0);

    // Relation wieder lösen
    ebp::Abwesenheit::unlinkBewohner(newAbwesenheit,aBewohner);
    newAbwesenheit->update(aConnection);
    abwesenheiten = aBewohner->loadAbwesenheiten(aConnection);
    QVERIFY(abwesenheiten.count()==0);

    //aufräumen
    newAbwesenheit->remove(aConnection);

}
/**
  * \brief Testet das Setzen und Lesen der Datenbankfelder
  */
void BewohnerTest::fields()
{
    QDate geburtstag = QDate::currentDate(),
            seit = QDate::currentDate();
    QString anrede = "Testanrede",
            vorname = "Testvorname",
            nachname = "Testnachname",
            geburtsort = "Testort",
            eMail ="test@mail.test",
            telefon = "1234567",
            familienstatus = "ledig",
            konfession = "testkonfession",
            staat = "Teststaat",
            anmerkung = "lange Anmerkung";

    aBewohner->geburtsdatum(geburtstag);
    QVERIFY(aBewohner->geburtsdatum()==geburtstag);

    aBewohner->seit(seit);
    QVERIFY(aBewohner->seit()==seit);

    aBewohner->anrede(anrede);
    QVERIFY(aBewohner->anrede()==anrede);

    aBewohner->vorname(vorname);
    QVERIFY(aBewohner->vorname()==vorname);

    aBewohner->nachname(nachname);
    QVERIFY(aBewohner->nachname()==nachname);

    aBewohner->geburtsort(geburtsort);
    QVERIFY(aBewohner->geburtsort()==geburtsort);

    aBewohner->telefon(telefon);
    QVERIFY(aBewohner->telefon()==telefon);

    aBewohner->email(eMail);
    QVERIFY(aBewohner->email()==eMail);

    aBewohner->familienstatus(familienstatus);
    QVERIFY(aBewohner->familienstatus()==familienstatus);

    aBewohner->konfession(konfession);
    QVERIFY(aBewohner->konfession()==konfession);

    aBewohner->staat(staat);
    QVERIFY(aBewohner->staat()==staat);

    aBewohner->anmerkung(anmerkung);
    QVERIFY(aBewohner->anmerkung()==anmerkung);


}
/**
  * \brief Löschen der TestBewohners
  */
void BewohnerTest::cleanupTestCase()
{
    aBewohner->remove(aConnection);
}
