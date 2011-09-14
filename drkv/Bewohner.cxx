#include "Bewohner.hxx"
#include "Bewohner-odb.hxx"
#include "database.hxx"

#include <QDebug>


using namespace drkv;


bool Bewohner::create( const QSharedPointer<drkv::database> & db )
{
	try
	{
		odb::transaction t( db->begin() );
		db->persist( *this );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


bool Bewohner::remove( const QSharedPointer<drkv::database> & db )
{
	try
	{
		odb::transaction t( db->begin() );
		db->erase( *this );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


bool Bewohner::update( const QSharedPointer<drkv::database> & db )
{
	try
	{
		odb::transaction t( db->begin() );
		db->update( *this );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


QList< QSharedPointer<Bewohner> > Bewohner::getAll( const QSharedPointer<drkv::database> & db )
{
	QList< QSharedPointer<Bewohner> > list;
	try
	{
		odb::transaction t( db->begin() );
		odb::result<Bewohner> r( db->query<Bewohner>() );
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
