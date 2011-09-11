#include <drkv/database.hxx>
#include <drkv/Mitarbeiter.hxx>

#include <QDebug>


using namespace drkv;


int main( int argc, char * argv[] )
{
	QSharedPointer<database> db( new database( "drk_admin", "drk_pass", "drk" ) );

	QList< QSharedPointer<Mitarbeiter> > mitarbeiter = Mitarbeiter::getAll( db );
	foreach( const QSharedPointer<Mitarbeiter> & m, mitarbeiter )
	{
		qDebug() << m->login();
	}

	return 0;
}
