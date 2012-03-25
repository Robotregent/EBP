#include "Verfuegung.hxx"
#include "Verfuegung-odb.hxx"
#include "Bewohner-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Verfuegung>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Verfuegung, Bewohner, bewohner_, Bewohner, Verfuegung, verfuegungen_ )
