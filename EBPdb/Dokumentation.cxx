#include "Dokumentation.hxx"
#include "Dokumentation-odb.hxx"
#include "Bewohner-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Dokumentation>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Dokumentation, Bewohner, bewohner_, Bewohner, Dokumentation, dokumentationen_ )


bool Dokumentation::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
{
	if( bewohner() )
		return bewohner()->hasPermission( connection );
	return true;
}
