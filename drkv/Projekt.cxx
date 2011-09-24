#include "Projekt.hxx"
#include "Projekt-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Projekt>;


using namespace drkv;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Projekt, Bewohner, bewohner_, Bewohner, Projekt, projekte_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Projekt, Verantwortlicher, verantwortliche_, Mitarbeiter, Projekt, projekte_ )
