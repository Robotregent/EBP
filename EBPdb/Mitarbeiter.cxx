#include "Mitarbeiter.hxx"
#include "Mitarbeiter-odb.hxx"
#include "Bewohner-odb.hxx"
#include "Bewohnerereignis-odb.hxx"
#include "Wohngruppe-odb.hxx"
#include "Wohngruppenereignis-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Mitarbeiter>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Wohngruppe, Wohngruppe, Mitarbeiter )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Projekt, Projekt, Verantwortlicher )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Bewohnerereignis, Bewohnerereignis, Schreiber )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Wohngruppenereignis, Wohngruppenereignis, Schreiber )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, ProtokollTeilnehmer, Protokoll, Teilnehmer )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, ProtokollSchreiber, Protokoll, Schreiber )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Bezugsbetreuer, Bewohner, Bezugsbetreuer )


DATABASEOBJECT_IMPLEMENT_LOAD( Mitarbeiter, Wohngruppen, Wohngruppe, wohngruppen_ )
DATABASEOBJECT_IMPLEMENT_LOAD( Mitarbeiter, Projekte, Projekt, projekte_ )
DATABASEOBJECT_IMPLEMENT_LOAD( Mitarbeiter, Bewohnerereignisse, Bewohnerereignis, bewohnerereignisse_ )
DATABASEOBJECT_IMPLEMENT_LOAD( Mitarbeiter, Wohngruppenereignisse, Wohngruppenereignis, wohngruppenereignisse_ )
DATABASEOBJECT_IMPLEMENT_LOAD( Mitarbeiter, ProtokollTeilnehmer, Protokoll, protokollTeilnehmer_ )
DATABASEOBJECT_IMPLEMENT_LOAD( Mitarbeiter, ProtokollSchreiber, Protokoll, protokollSchreiber_ )
DATABASEOBJECT_IMPLEMENT_LOAD( Mitarbeiter, Bezugsbetreuer, Bewohner, bezugsbetreuer_ )


bool Mitarbeiter::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
{
	return true;
}


bool Mitarbeiter::create( const QSharedPointer<ebp::connection> & connection, const QString & password )
{
	if( login().isNull() || login()=="" )
	{
		qCritical() << tr("Kann keinen neuen Benutzer ohne Login-Namen erstellen.");
		return false;
	}

	try
	{
		odb::transaction t( connection->getDB()->begin() );
		connection->executeCreateUser( *this, password );
		connection->getDB()->persist( *this );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


bool Mitarbeiter::create( const QSharedPointer<ebp::connection> & connection )
{
	qWarning() << tr("Erstelle Benutzer ohne Passwort.");
	return create( connection, "" );
}


bool Mitarbeiter::remove( const QSharedPointer<ebp::connection> & connection )
{
	try
	{
		odb::transaction t( connection->getDB()->begin() );
		connection->executeDropUser( *this );
		connection->getDB()->erase( *this );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


bool Mitarbeiter::updatePassword( const QSharedPointer<ebp::connection> & connection, const QString & password )
{
	try
	{
		odb::transaction t( connection->getDB()->begin() );
		connection->executeSetPassword( *this, password );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}
