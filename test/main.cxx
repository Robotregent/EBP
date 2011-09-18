#include <drkv/connection.hxx>
#include <drkv/Mitarbeiter.hxx>

#include <QDebug>


using namespace drkv;


int main( int argc, char * argv[] )
{
	QSharedPointer<connection> c( new connection( "drk_admin", "drk" ) );

	if( !c->establish("drk_pass") )
		return 1;

	return 0;
}
