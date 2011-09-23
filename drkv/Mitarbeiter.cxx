#include "Mitarbeiter.hxx"
#include "Mitarbeiter-odb.hxx"
#include "Bewohner-odb.hxx"
#include "Bewohnerereignis-odb.hxx"
#include "Wohngruppe-odb.hxx"
#include "Wohngruppenereignis-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Mitarbeiter>;


using namespace drkv;


DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Wohngruppe, Wohngruppe, Mitarbeiter )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Projekt, Projekt, Verantwortlicher )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Bewohnerereignis, Bewohnerereignis, Schreiber )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Wohngruppenereignis, Wohngruppenereignis, Schreiber )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, ProtokollTeilnehmer, Protokoll, Teilnehmer )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, ProtokollSchreiber, Protokoll, Schreiber )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Mitarbeiter, Bezugsbetreuer, Bewohner, Bezugsbetreuer )


QList< QSharedPointer<Wohngruppe> > Mitarbeiter::loadWohngruppen( const QSharedPointer<drkv::connection> & connection ) const
{
	QList< QSharedPointer<Wohngruppe> > ret;
	odb::transaction t( connection->getDB()->begin() );
	for( QList< QLazyWeakPointer<Wohngruppe> >::const_iterator i = wohngruppen_.begin(); i!=wohngruppen_.end(); ++i )
	{
		ret.push_back( (*i).load() );
	}
	t.commit();
	return ret;
}


QList< QSharedPointer<Projekt> > Mitarbeiter::loadProjekte( const QSharedPointer<drkv::connection> & connection ) const
{
	QList< QSharedPointer<Projekt> > ret;
	odb::transaction t( connection->getDB()->begin() );
	for( QList< QLazyWeakPointer<Projekt> >::const_iterator i = projekte_.begin(); i!=projekte_.end(); ++i )
	{
		ret.push_back( (*i).load() );
	}
	t.commit();
	return ret;
}


QList< QSharedPointer<Bewohner> > Mitarbeiter::loadBezugsbetreuer( const QSharedPointer<drkv::connection> & connection ) const
{
	QList< QSharedPointer<Bewohner> > ret;
	odb::transaction t( connection->getDB()->begin() );
	for( QList< QLazyWeakPointer<Bewohner> >::const_iterator i = bezugsbetreuer_.begin(); i!=bezugsbetreuer_.end(); ++i )
	{
		ret.push_back( (*i).load() );
	}
	t.commit();
	return ret;
}


bool Mitarbeiter::create( const QSharedPointer<drkv::connection> & connection, const QString & password )
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


bool Mitarbeiter::create( const QSharedPointer<drkv::connection> & connection )
{
	qWarning() << tr("Erstelle Benutzer ohne Passwort.");
	return create( connection, "" );
}


bool Mitarbeiter::remove( const QSharedPointer<drkv::connection> & connection )
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


bool Mitarbeiter::updatePassword( const QSharedPointer<drkv::connection> & connection, const QString & password )
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
