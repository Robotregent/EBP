#include "Protokoll.hxx"
#include "Protokoll-odb.hxx"
#include "Mitarbeiter-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Protokoll>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Protokoll, Bewohner, bewohner_, Bewohner, Protokoll, protokolle_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Protokoll, Teilnehmer, teilnehmer_, Mitarbeiter, ProtokollTeilnehmer, protokollTeilnehmer_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Protokoll, Schreiber, schreiber_, Mitarbeiter, ProtokollSchreiber, protokollSchreiber_ )


DATABASEOBJECT_IMPLEMENT_LOAD( Protokoll, Teilnehmer, Mitarbeiter, teilnehmer_ )
DATABASEOBJECT_IMPLEMENT_LOAD( Protokoll, Schreiber, Mitarbeiter, schreiber_ )


bool Protokoll::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
{
	if( bewohner() )
		return bewohner()->hasPermission( connection );
	return true;
}
