#include "linktest.h"

void LinkTest::initTestCase()
{
    aConnection = QSharedPointer< ebp::connection >( new ebp::connection("ebp_test_root", "ebp_test", "localhost", 3306));
    QVERIFY(aConnection->establish("ebp_test_root"));
}

void LinkTest::linkMitarbeiter()
{


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
		ebp::Wohngruppenereignis::linkSchreiber(ereignis, mitarbeiter);
		ebp::Wohngruppenereignis::linkWohngruppe(ereignis,wohngruppe);
	    }
	    else
	    {
		mitarbeiter = mitarbeiterList.at(2);
		wohngruppe = wohngruppeList.at(2);
		ebp::Wohngruppenereignis::linkSchreiber(ereignis, mitarbeiter);
		ebp::Wohngruppenereignis::linkWohngruppe(ereignis,wohngruppe);

	    }
	    QVERIFY(ereignisList.at(i)->update(aConnection));
	}
    }
}

void LinkTest::linkBewohner()
{


}

void LinkTest::linkBewohnerEreignis()
{


}

void LinkTest::linkVerfuegung()
{


}

void LinkTest::linkDokumentation()
{


}
