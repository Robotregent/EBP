#include "Leistungstraeger.hxx"
#include "Leistungstraeger-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Leistungstraeger>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Leistungstraeger, Bewohner, bewohner_, Bewohner, Leistungstraeger, leistungstraeger_ )


DATABASEOBJECT_IMPLEMENT_LOAD( Leistungstraeger, Bewohner, Bewohner, bewohner_ )


bool Leistungstraeger::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
{
	return true;
}
