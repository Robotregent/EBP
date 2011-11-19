#include "Bewohner.hxx"
#include "Bewohner-odb.hxx"
#include "Bewohnerereignis-odb.hxx"
#include "Protokoll-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Bewohner>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Bewohner, Bezugsbetreuer, bezugsbetreuer_, Mitarbeiter, Bezugsbetreuer, bezugsbetreuer_ )
DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Bewohner, Wohngruppe, wohngruppe_, Wohngruppe, Bewohner, bewohner_ )

DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Bewohner, Projekt, Projekt, Bewohner )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Bewohner, Protokoll, Protokoll, Bewohner )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Bewohner, Ereignis, Bewohnerereignis, Bewohner )
