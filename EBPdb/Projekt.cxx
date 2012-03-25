#include "Projekt.hxx"
#include "Projekt-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Projekt>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Projekt, Bewohner, bewohner_, Bewohner, Projekt, projekte_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Projekt, Verantwortlicher, verantwortliche_, Mitarbeiter, Projekt, projekte_ )



DATABASEOBJECT_IMPLEMENT_LOAD( Projekt, Verantwortliche, Mitarbeiter, verantwortliche_ )


bool Projekt::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
{
	return bewohner()->hasPermission( connection );
}
