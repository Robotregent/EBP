#include "Protokoll.hxx"
#include "Protokoll-odb.hxx"
#include "Mitarbeiter-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Protokoll>;


using namespace drkv;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Protokoll, Bewohner, bewohner_, Bewohner, Protokoll, protokolle_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Protokoll, Teilnehmer, teilnehmer_, Mitarbeiter, ProtokollTeilnehmer, protokollTeilnehmer_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Protokoll, Schreiber, schreiber_, Mitarbeiter, ProtokollSchreiber, protokollSchreiber_ )
