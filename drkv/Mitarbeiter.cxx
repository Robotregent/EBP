#include "Mitarbeiter.hxx"
#include "Mitarbeiter-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Mitarbeiter>;


using namespace drkv;


bool Mitarbeiter::create( const QSharedPointer<drkv::connection> & connection, const QString & password )
{
	if( login().isNull() || login()=="" )
	{
		qCritical() << tr("Kann keinen neuen Benutzer ohne Login-Namen erstellen.");
		return false;
	}
	if( password.isNull() || password=="" )
	{
		qCritical() << tr("Kann keinen neuen Benutzer ohne Passwort erstellen.");
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
