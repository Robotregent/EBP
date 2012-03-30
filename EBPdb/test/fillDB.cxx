#include <stdio.h>
#include <EBPdb/connection.hxx>
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Wohnheim.hxx>

using namespace ebp;


bool createMitarbeiter( QSharedPointer<connection> & c, int nr )
{
	QSharedPointer<Mitarbeiter> x( new Mitarbeiter( "ebp_test_user_" + QString::number(nr), Mitarbeiter::WohngruppenRecht, "Mitarbeiter_" + QString::number(nr) ) );
	if( !x->create( c, x->name() ) )
	{
		fprintf( stderr, "Could not create '%s'\n", x->name().toLocal8Bit().data() );
		return false;
	}
	return true;
}


bool createBewohner( QSharedPointer<connection> & c, int b )
{
	QSharedPointer<Bewohner> x( new Bewohner( b ) );
	if( !x->create( c ) )
	{
		fprintf( stderr, "Could not create '%s'\n", x->name().toLocal8Bit().data() );
		return false;
	}
	QSharedPointer<Dokumentation> d1( new Dokumentation( Dokumentation::einkaufen, Dokumentation::istWichtig ) );
	QSharedPointer<Dokumentation> d2( new Dokumentation( Dokumentation::aufstehenUndZuBettgehen, Dokumentation::istWichtig ) );
	QSharedPointer<Dokumentation> d3( new Dokumentation( Dokumentation::freundschaften, Dokumentation::istWichtig ) );
	Dokumentation::linkBewohner( d1, x );
	Dokumentation::linkBewohner( d2, x );
	Dokumentation::linkBewohner( d3, x );
	d1->create( c );
	d2->create( c );
	d3->create( c );
	x->update( c );
	return true;
}

bool createWohngruppe( QSharedPointer<connection> & c, int wh, int wg )
{
	QSharedPointer<Wohngruppe> x( new Wohngruppe( "Wohngruppe_" + QString::number(wh) + "_" + QString::number(wg) ) );
	if( !x->create( c ) )
	{
		fprintf( stderr, "Could not create '%s'\n", x->name().toLocal8Bit().data() );
		return false;
	}
	return true;
}

bool createWohnheim( QSharedPointer<connection> & c, int wh )
{
	QSharedPointer<Wohnheim> x( new Wohnheim( "Wohnheim_" + QString::number(wh) ) );
	if( !x->create( c ) )
	{
		fprintf( stderr, "Could not create '%s'\n", x->name().toLocal8Bit().data() );
		return false;
	}
	for( int i=0; i<3; i++ )
	{
		if( !createWohngruppe( c, wh, i ) )
		{
			return false;
		}
	}
	return true;
}

bool fillDatabase( QSharedPointer<connection> & c )
{
	for( int i=0; i<3; i++ )
	{
		if( !createWohnheim( c, i ) )
		{
			return false;
		}
	}
	for( int i=0; i<10; i++ )
	{
		if( !createMitarbeiter( c, i ) )
		{
			return false;
		}
	}
	for( int i=0; i<10; i++ )
	{
		if( !createBewohner( c, i ) )
		{
			return false;
		}
	}
	return true;
}

int main( int argc, char ** argv )
{
	QSharedPointer<connection> c( new connection( "ebp_test_root", "ebp_test", "localhost", 3306 ) );
	if( !c->establish( "ebp_test_root" ) )
	{
		fprintf( stderr, "Could not connect\n" );
		return 1;
	}

	if( !fillDatabase( c ) )
		return 1;
	else
		return 0;
}
