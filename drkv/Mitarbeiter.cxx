#include "Mitarbeiter.hxx"
#include "Mitarbeiter-odb.hxx"
#include "connection.hxx"

#include <QDebug>


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


bool Mitarbeiter::update( const QSharedPointer<drkv::connection> & connection )
{
	try
	{
		odb::transaction t( connection->getDB()->begin() );
		connection->getDB()->update( *this );
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


QList< QSharedPointer<Mitarbeiter> > Mitarbeiter::getAll( const QSharedPointer<drkv::connection> & connection )
{
	QList< QSharedPointer<Mitarbeiter> > list;
	try
	{
		odb::transaction t( connection->getDB()->begin() );
		odb::result<Mitarbeiter> r( connection->getDB()->query<Mitarbeiter>() );
		for( odb::result<Mitarbeiter>::iterator i( r.begin() ); i != r.end(); ++i )
		{
			list.push_back( i.load() );
		}
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return QList< QSharedPointer<Mitarbeiter> >();
	}
	return list;
}
