#include "Wohngruppenereignis.hxx"
#include "Wohngruppenereignis-odb.hxx"
#include "Mitarbeiter-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Wohngruppenereignis>;


using namespace drkv;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Wohngruppenereignis, Wohngruppe, wohngruppe_, Wohngruppe, Ereignis, ereignisse_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Wohngruppenereignis, Schreiber, schreiber_, Mitarbeiter, Wohngruppenereignis, wohngruppenereignisse_ )
