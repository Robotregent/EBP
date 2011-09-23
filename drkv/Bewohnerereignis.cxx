#include "Bewohnerereignis.hxx"
#include "Bewohnerereignis-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Bewohnerereignis>;


using namespace drkv;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Bewohnerereignis, Bewohner, bewohner_, Bewohner, Ereignis, ereignisse_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Bewohnerereignis, Schreiber, schreiber_, Mitarbeiter, Bewohnerereignis, bewohnerereignisse_ )
