#include "Projekt.hxx"
#include "Projekt-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Projekt>;


using namespace drkv;

DATABASEOBJECT_IMPLEMENT_LINK_MANYTOMANY( Projekt, Verantwortlicher, verantwortliche_, Mitarbeiter, Projekt, projekte_ )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Projekt, Bewohner, Bewohner, Projekt )
