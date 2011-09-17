#include "Projekt.hxx"
#include "Projekt-odb.hxx"
#include "connection.hxx"

#include <QDebug>


using namespace drkv;


bool Projekt::create( const QSharedPointer<drkv::connection> & connection )
{
	try
	{
		odb::transaction t( connection->getDB()->begin() );
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


bool Projekt::remove( const QSharedPointer<drkv::connection> & connection )
{
	try
	{
		odb::transaction t( connection->getDB()->begin() );
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


bool Projekt::update( const QSharedPointer<drkv::connection> & connection )
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
