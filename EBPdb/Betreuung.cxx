#include "Betreuung.hxx"
#include "Betreuung-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Betreuung>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEONE( Betreuung, Bewohner, bewohner_, Bewohner, Betreuung, betreuung_ )


bool Betreuung::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
{
	if( bewohner() )
		return bewohner()->hasPermission( connection );
	return true;
}
