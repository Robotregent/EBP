#include "Wohngruppe.hxx"
#include "Wohngruppe-odb.hxx"
#include "connection.hxx"

#include <QDebug>


using namespace drkv;


bool Wohngruppe::create( const QSharedPointer<drkv::connection> & connection )
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


bool Wohngruppe::remove( const QSharedPointer<drkv::connection> & connection )
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


bool Wohngruppe::update( const QSharedPointer<drkv::connection> & connection )
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


QList< QSharedPointer<Wohngruppe> > Wohngruppe::getAll( const QSharedPointer<drkv::connection> & connection )
{
	QList< QSharedPointer<Wohngruppe> > list;
	try
	{
		odb::transaction t( connection->getDB()->begin() );
		odb::result<Wohngruppe> r( connection->getDB()->query<Wohngruppe>() );
		for( odb::result<Wohngruppe>::iterator i( r.begin() ); i != r.end(); ++i )
		{
			list.push_back( i.load() );
		}
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return QList< QSharedPointer<Wohngruppe> >();
	}
	return list;
}
