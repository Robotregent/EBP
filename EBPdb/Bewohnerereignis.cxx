#include "Bewohnerereignis.hxx"
#include "Bewohnerereignis-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Bewohnerereignis>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Bewohnerereignis, Bewohner, bewohner_, Bewohner, Ereignis, ereignisse_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Bewohnerereignis, Schreiber, schreiber_, Mitarbeiter, Bewohnerereignis, bewohnerereignisse_ )


DATABASEOBJECT_IMPLEMENT_LOAD( Bewohnerereignis, Schreiber, Mitarbeiter, schreiber_ )
