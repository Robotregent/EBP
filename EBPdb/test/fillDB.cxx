#include <stdio.h>
#include <EBPdb/connection.hxx>
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Wohnheim.hxx>

using namespace ebp;


bool createMitarbeiter( QSharedPointer<connection> & c, int nr )
{
	Mitarbeiter x( "ebp_test_user_" + QString::number(nr), Mitarbeiter::WohngruppenRecht, "Mitarbeiter_" + QString::number(nr) );
	if( !x.create( c, x.name() ) )
	{
		fprintf( stderr, "Could not create '%s'\n", x.name().toLocal8Bit().data() );
		return false;
	}
	return true;
}


bool createBewohner( QSharedPointer<connection> & c, int b )
{
	Bewohner x( b );
	if( !x.create( c ) )
	{
		fprintf( stderr, "Could not create '%s'\n", x.name().toLocal8Bit().data() );
		return false;
	}
	return true;
}

bool createWohngruppe( QSharedPointer<connection> & c, int wh, int wg )
{
	Wohngruppe x( "Wohngruppe_" + QString::number(wh) + "_" + QString::number(wg) );
	if( !x.create( c ) )
	{
		fprintf( stderr, "Could not create '%s'\n", x.name().toLocal8Bit().data() );
		return false;
	}
	return true;
}

bool createWohnheim( QSharedPointer<connection> & c, int wh )
{
	Wohnheim x( "Wohnheim_" + QString::number(wh) );
	if( !x.create( c ) )
	{
		fprintf( stderr, "Could not create '%s'\n", x.name().toLocal8Bit().data() );
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
