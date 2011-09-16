#include <drkv/connection.hxx>
#include <drkv/Mitarbeiter.hxx>

#include <QDebug>


using namespace drkv;


int main( int argc, char * argv[] )
{
	QSharedPointer<connection> c( new connection( "drk_admin", "drk" ) );

	if( !c->establish("drk_pass") )
		return 1;

	QList< QSharedPointer<Mitarbeiter> > mitarbeiter = Mitarbeiter::getAll( c );
	foreach( const QSharedPointer<Mitarbeiter> & m, mitarbeiter )
	{
		qDebug() << m->login();
	}

	return 0;
}
