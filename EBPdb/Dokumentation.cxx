#include "Abwesenheit.hxx"
#include "Abwesenheit-odb.hxx"
#include "Bewohner-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Abwesenheit>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Abwesenheit, Bewohner, bewohner_, Bewohner, Abwesenheit, abwesenheiten_ )
