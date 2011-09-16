#include "Bewohner.hxx"
#include "Bewohner-odb.hxx"
#include "connection.hxx"

#include <QDebug>


using namespace drkv;


bool Bewohner::create( const QSharedPointer<drkv::connection> & connection )
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


bool Bewohner::remove( const QSharedPointer<drkv::connection> & connection )
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


bool Bewohner::update( const QSharedPointer<drkv::connection> & connection )
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


QList< QSharedPointer<Bewohner> > Bewohner::getAll( const QSharedPointer<drkv::connection> & connection )
{
	QList< QSharedPointer<Bewohner> > list;
	try
	{
		odb::transaction t( connection->getDB()->begin() );
		odb::result<Bewohner> r( connection->getDB()->query<Bewohner>() );
		for( odb::result<Bewohner>::iterator i( r.begin() ); i != r.end(); ++i )
		{
			list.push_back( i.load() );
		}
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return QList< QSharedPointer<Bewohner> >();
	}
	return list;
}
