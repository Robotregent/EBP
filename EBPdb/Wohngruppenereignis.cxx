#include "Wohngruppenereignis.hxx"
#include "Wohngruppenereignis-odb.hxx"
#include "Mitarbeiter-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Wohngruppenereignis>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Wohngruppenereignis, Wohngruppe, wohngruppe_, Wohngruppe, Ereignis, ereignisse_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Wohngruppenereignis, Schreiber, schreiber_, Mitarbeiter, Wohngruppenereignis, wohngruppenereignisse_ )


DATABASEOBJECT_IMPLEMENT_LOAD( Wohngruppenereignis, Schreiber, Mitarbeiter, schreiber_ )
