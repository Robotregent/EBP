#include "Bewohner.hxx"
#include "Bewohner-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Bewohner>;


using namespace drkv;


DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Bewohner, Bezugsbetreuer, Mitarbeiter, Bezugsbetreuer )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Bewohner, Wohngruppe, Wohngruppe, Bewohner )
DATABASEOBJECT_IMPLEMENT_LINK_MANYTOONE( Bewohner, Projekt, projekte_, Projekt, Bewohner, bewohner_ )
