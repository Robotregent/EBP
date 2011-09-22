#include <drkv/connection.hxx>
#include <drkv/Mitarbeiter.hxx>
#include <drkv/Wohngruppe.hxx>

#include <QDebug>

#include <iostream>


using namespace drkv;
using namespace std;


int main( int argc, char * argv[] )
{
	QSharedPointer<connection> c( new connection( "drk_admin", "drk", "127.0.0.1" ) );

	if( !c->establish("drk_pass") )
		return 1;
/*
	QSharedPointer<Wohngruppe> wg1
	(
		new Wohngruppe
		(
			"Gruppe 1"
		)
	);
	wg1->create( c );

	QSharedPointer<Wohngruppe> wg2
	(
		new Wohngruppe
		(
			"Gruppe 2"
		)
	);
	wg2->create( c );

	QSharedPointer<Wohngruppe> wg3
	(
		new Wohngruppe
		(
			"Gruppe 3"
		)
	);
	wg3->create( c );

	QSharedPointer<Mitarbeiter> ma1
	(
		new Mitarbeiter
		(
			"drk_test1",
			Mitarbeiter::WohnheimRecht,
			"Tester 1",
			"",
			""
		)
	);
	ma1->create( c, "test" );

	QSharedPointer<Mitarbeiter> ma2
	(
		new Mitarbeiter
		(
			"drk_test2",
			Mitarbeiter::WohnheimRecht,
			"Tester 2",
			"",
			""
		)
	);
	ma2->create( c, "test" );
*/
/*
	QSharedPointer<Bewohner> bw1
	(
		new Bewohner
		(
			1,
			"bw1",
			QDate(),
			"",
			"",
			""
		)
	);
	bw1->create( c );
*/

	{
		QList< QSharedPointer<Bewohner> > bwList = Bewohner::loadAll( c );
		QList< QSharedPointer<Mitarbeiter> > maList = Mitarbeiter::loadAll( c );
		Mitarbeiter::linkBezugsbetreuer( maList[0], bwList[0] );
//		Mitarbeiter::linkBezugsbetreuer( maList[0], bwList[0] );
//		Mitarbeiter::linkBezugsbetreuer( maList[0], bwList[1] );
		maList[0]->update(c);
	}

/*
	{
		QList< QSharedPointer<Wohngruppe> > wgList = Wohngruppe::loadAll( c );
		QList< QSharedPointer<Mitarbeiter> > maList = Mitarbeiter::loadAll( c );
		Wohngruppe::linkMitarbeiter( wgList[0], maList[0] );
		Wohngruppe::linkMitarbeiter( wgList[0], maList[0] );
		Wohngruppe::linkMitarbeiter( wgList[1], maList[1] );
		Wohngruppe::linkMitarbeiter( wgList[1], maList[1] );
		Wohngruppe::linkMitarbeiter( wgList[2], maList[0] );
		Wohngruppe::linkMitarbeiter( wgList[2], maList[1] );
		wgList[0]->update(c);
		wgList[1]->update(c);
		wgList[2]->update(c);
	}
*/
/*
	{
		QList< QSharedPointer<Mitarbeiter> > maList = Mitarbeiter::loadAll( c );
	}
*/
	cout << "---" << endl;

	{
		QList< QSharedPointer<Mitarbeiter> > maList = Mitarbeiter::loadAll( c );
		for( QList< QSharedPointer<Mitarbeiter> >::const_iterator m = maList.begin(); m!=maList.end(); ++m )
		{
			cout << (*m)->login().toStdString() << endl;
			QList< QSharedPointer<Wohngruppe> > wgList = (*m)->loadWohngruppen( c );
			for( QList< QSharedPointer<Wohngruppe> >::const_iterator w = wgList.begin(); w!=wgList.end(); ++w )
			{
				cout << "   " << (*w)->name().toStdString() << endl;
			}
		}
	}

	cout << "---" << endl;

	{
		QList< QSharedPointer<Wohngruppe> > wgList = Wohngruppe::loadAll( c );
		for( QList< QSharedPointer<Wohngruppe> >::const_iterator w = wgList.begin(); w!=wgList.end(); ++w )
		{
			cout << (*w)->name().toStdString() << endl;
			QList< QSharedPointer<Mitarbeiter> > maList = (*w)->loadMitarbeiter( c );
			for( QList< QSharedPointer<Mitarbeiter> >::const_iterator m = maList.begin(); m!=maList.end(); ++m )
			{
				cout << "  " << (*m)->login().toStdString() << endl;
			}
		}
	}
	return 0;
}
