#include "linktest.h"
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Verfuegung.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Bewohnerereignis.hxx>
#include <EBPdb/Wohngruppe.hxx>
#include <EBPdb/Wohngruppenereignis.hxx>
#include <EBPdb/Dokumentation.hxx>
#include <EBPdb/Abwesenheit.hxx>
#include <EBPdb/Projekt.hxx>
#include <EBPdb/Protokoll.hxx>
#include <EBPdb/Leistungstraeger.hxx>

void LinkTest::initTestCase()
{
    aConnection = QSharedPointer< ebp::connection >( new ebp::connection("ebp_test_root", "ebp_test", "localhost", 3306));
    QVERIFY(aConnection->establish("ebp_test_root"));
}

void LinkTest::linkWohngruppe()
{
    QList< QSharedPointer< ebp::Wohngruppe > > gruppenList = ebp::Wohngruppe::loadAll(aConnection);
    QList< QSharedPointer< ebp::Mitarbeiter > > mitarbeiterList = ebp::Mitarbeiter::loadAll(aConnection);

    QSharedPointer< ebp::Wohngruppe > gruppe;
    QSharedPointer< ebp::Mitarbeiter > mitarbeiter;

    if(mitarbeiterList.count()>=gruppenList.count())
    {
        for ( int i = 0 ; i< gruppenList.count(); i++)
        {
            gruppe = gruppenList.at(i);
            mitarbeiter = mitarbeiterList.at(i);
            ebp::Wohngruppe::linkMitarbeiter(gruppe,mitarbeiter);
            QVERIFY(gruppe->update(aConnection));
        }
    }
    else
        QFAIL("Konnte Test nicht durchführen, da zu wenig Mitarbeiter geladen wurden.");
}

void LinkTest::linkWohngruppenereignis()
{
    QList< QSharedPointer< ebp::Wohngruppenereignis > > ereignisList = ebp::Wohngruppenereignis::loadAll(aConnection);
    QList< QSharedPointer< ebp::Mitarbeiter > > mitarbeiterList = ebp::Mitarbeiter::loadAll(aConnection);
    QList< QSharedPointer< ebp::Wohngruppe > > wohngruppeList = ebp::Wohngruppe::loadAll(aConnection);
    QSharedPointer< ebp::Mitarbeiter >  mitarbeiter;
    QSharedPointer< ebp::Wohngruppenereignis >  ereignis;
    QSharedPointer< ebp::Wohngruppe > wohngruppe;
    if((mitarbeiterList.count()>1)&&(wohngruppeList.count()>1))
    {
	for ( int i = 0; i<ereignisList.count();i++)
	{
	    ereignis = ereignisList.at(i);
	    if ( i<5)
	    {
		mitarbeiter = mitarbeiterList.at(1);
                wohngruppe = wohngruppeList.at(1);
            }
	    else
	    {
		mitarbeiter = mitarbeiterList.at(2);
		wohngruppe = wohngruppeList.at(2);
	    }
            ebp::Wohngruppenereignis::linkSchreiber(ereignis, mitarbeiter);
            ebp::Wohngruppenereignis::linkWohngruppe(ereignis,wohngruppe);
	    QVERIFY(ereignisList.at(i)->update(aConnection));
	}
    }
    else
        QFAIL("Konnte Test nicht durchführen, da zu wenig Wohngruppen oder Mitarbeiter geladen wurden.");
}

void LinkTest::linkBewohner()
{
    QList< QSharedPointer< ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);
    QList< QSharedPointer< ebp::Mitarbeiter > > mitarbeiterList = ebp::Mitarbeiter::loadAll(aConnection);
    QList< QSharedPointer< ebp::Wohngruppe > > wohngruppeList = ebp::Wohngruppe::loadAll(aConnection);
    QSharedPointer< ebp::Mitarbeiter >  mitarbeiter;
    QSharedPointer< ebp::Wohngruppe > wohngruppe;

    if((mitarbeiterList.count()>=bewohnerList.count())&&(wohngruppeList.count()>=bewohnerList.count()))
    {
        int i = 0;

        foreach ( QSharedPointer< ebp::Bewohner > bw , bewohnerList)
        {
            mitarbeiter = mitarbeiterList.at(i);
            wohngruppe = wohngruppeList.at(i);
            ebp::Bewohner::linkBezugsbetreuer(bw,mitarbeiter);
            ebp::Bewohner::linkWohngruppe(bw, wohngruppe);
            QVERIFY(bw->update(aConnection));
            i++;
        }
    }
    else
        QFAIL("Konnte Test nicht durchführen, da zu wenig Wohngruppen oder Mitarbeiter geladen wurden.");

}

void LinkTest::linkBewohnerEreignis()
{
    QList< QSharedPointer< ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);
    QList< QSharedPointer< ebp::Bewohnerereignis > > ereignisList = ebp::Bewohnerereignis::loadAll(aConnection);
    QSharedPointer< ebp::Bewohner >  bewohner;
    if(bewohnerList.count()>1)
    {
        int i = 0;
        foreach (QSharedPointer < ebp::Bewohnerereignis > be,  ereignisList)
        {
            if(i<(ereignisList.count()/2))
            {
                bewohner = bewohnerList.at(1);
            }
            else
            {
                bewohner = bewohnerList.at(2);
            }
            ebp::Bewohnerereignis::linkBewohner(be,bewohner);
            QVERIFY(be->update(aConnection));
            i++;
        }
    }
    else
        QFAIL("Konnte Test nicht durchführen, da zu wenig Bewohner geladen wurden.");
}

void LinkTest::linkVerfuegung()
{
    QList< QSharedPointer< ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);
    QList< QSharedPointer< ebp::Verfuegung > > verfuegungList = ebp::Verfuegung::loadAll(aConnection);
    QSharedPointer< ebp::Bewohner >  bewohner;
    if(bewohnerList.count()>1)
    {
        int i = 0;
        foreach (QSharedPointer < ebp::Verfuegung > vf,  verfuegungList)
        {
            if(i<(verfuegungList.count()/2))
            {
                bewohner = bewohnerList.at(1);
            }
            else
            {
                bewohner = bewohnerList.at(2);
            }
            ebp::Verfuegung::linkBewohner(vf,bewohner);
            QVERIFY(vf->update(aConnection));
            i++;
        }
    }
    else
        QFAIL("Konnte Test nicht durchführen, da zu wenig Bewohner geladen wurden.");
}

void LinkTest::linkDokumentation()
{
    QList< QSharedPointer< ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);
    QList< QSharedPointer< ebp::Dokumentation > > dokuList = ebp::Dokumentation::loadAll(aConnection);
    QSharedPointer< ebp::Bewohner >  bewohner;
    if(bewohnerList.count()>1)
    {
        int i = 0;
        foreach (QSharedPointer < ebp::Dokumentation > doku,  dokuList)
        {
            if(i<(dokuList.count()/2))
            {
                bewohner = bewohnerList.at(1);
            }
            else
            {
                bewohner = bewohnerList.at(2);
            }
            ebp::Dokumentation::linkBewohner(doku,bewohner);
            QVERIFY(doku->update(aConnection));
            i++;
        }
    }
    else
        QFAIL("Konnte Test nicht durchführen, da zu wenig Bewohner geladen wurden.");

}
void LinkTest::linkAbwesenheit()
{
    QList< QSharedPointer< ebp::Abwesenheit > > abwesenheitList = ebp::Abwesenheit::loadAll(aConnection);
    QList< QSharedPointer< ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);
    QSharedPointer< ebp::Bewohner >  bewohner;
    if(bewohnerList.count()>1)
    {
        int i = 0;
        foreach (QSharedPointer < ebp::Abwesenheit > ab,  abwesenheitList)
        {
            if(i<(abwesenheitList.count()/2))
            {
                bewohner = bewohnerList.at(1);
            }
            else
            {
                bewohner = bewohnerList.at(2);
            }
            ebp::Abwesenheit::linkBewohner(ab,bewohner);
            QVERIFY(ab->update(aConnection));
            i++;
        }
    }
    else
        QFAIL("Konnte Test nicht durchführen, da zu wenig Bewohner geladen wurden.");
}

void LinkTest::linkProtokoll()
{

    QList< QSharedPointer< ebp::Protokoll > > protokollList = ebp::Protokoll::loadAll(aConnection);
    QList< QSharedPointer< ebp::Mitarbeiter > > mitarbeiterList = ebp::Mitarbeiter::loadAll(aConnection);
    QList< QSharedPointer< ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);
    QSharedPointer< ebp::Mitarbeiter> schreiber;
    QSharedPointer< ebp::Mitarbeiter> teilnehmer;
    QSharedPointer< ebp::Bewohner >  bewohner;
    if((bewohnerList.count()>1)&&(mitarbeiterList.count()>1))
    {
        int i = 0;
        foreach (QSharedPointer< ebp::Protokoll > pk , protokollList )
        {
            teilnehmer = mitarbeiterList.at(i);
            if(i<(protokollList.count()/2))
            {
                schreiber = mitarbeiterList.at(1);
                bewohner = bewohnerList.at(1);
            }
            else
            {
                schreiber = mitarbeiterList.at(2);
                bewohner = bewohnerList.at(2);
            }
            ebp::Protokoll::linkBewohner(pk,bewohner);
            ebp::Protokoll::linkSchreiber(pk,schreiber);
            ebp::Protokoll::linkTeilnehmer(pk,teilnehmer);
            QVERIFY(pk->update(aConnection));
            i++;
        }
    }
    else
        QFAIL("Konnte Test nicht durchführen, da zu wenig Bewohner oder Mitarbeiter geladen wurden.");;
}

void LinkTest::linkLeistungstraeger()
{
     QList< QSharedPointer< ebp::Leistungstraeger > > leistungList = ebp::Leistungstraeger::loadAll(aConnection);
     QList< QSharedPointer< ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);
     QSharedPointer< ebp::Bewohner >  bewohner;
     if(bewohnerList.count()>1)
     {
         int i = 0;
         foreach (QSharedPointer < ebp::Leistungstraeger > lt,  leistungList)
         {
             if(i<(leistungList.count()/2))
             {
                 bewohner = bewohnerList.at(1);
             }
             else
             {
                 bewohner = bewohnerList.at(2);
             }
             ebp::Leistungstraeger::linkBewohner(lt,bewohner);
             QVERIFY(lt->update(aConnection));
             i++;
         }
     }
     else
         QFAIL("Konnte Test nicht durchführen, da zu wenig Bewohner geladen wurden.");
}
void LinkTest::linkProjekt()
{
    QList< QSharedPointer< ebp::Projekt > > projektList = ebp::Projekt::loadAll(aConnection);
    QList< QSharedPointer< ebp::Mitarbeiter > > mitarbeiterList = ebp::Mitarbeiter::loadAll(aConnection);
    QList< QSharedPointer< ebp::Bewohner> > bewohnerList = ebp::Bewohner::loadAll(aConnection);
    QSharedPointer< ebp::Mitarbeiter> verantwortlicher;
    QSharedPointer< ebp::Bewohner >  bewohner;
    if((mitarbeiterList.count()>=projektList.count())&&(bewohnerList.count()>=projektList.count()))
    {
        int i = 0;
        foreach(QSharedPointer< ebp::Projekt > projekt, projektList)
        {
            verantwortlicher = mitarbeiterList.at(i);
            bewohner = bewohnerList.at(i);
            ebp::Projekt::linkBewohner(projekt,bewohner);
            ebp::Projekt::linkVerantwortlicher(projekt,verantwortlicher);
            QVERIFY(projekt->update(aConnection));
            i++;
        }
     }
     else
        QFAIL("Konnte Test nicht durchführen, da zu wenig Bewohner oder Mitarbeiter geladen wurden.");
}
void LinkTest::cleanupTestCase()
{
    aConnection.clear();
}
