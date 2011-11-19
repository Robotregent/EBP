#include "databaseObject.hxx"
#include "connection.hxx"

#include <odb/core.hxx>
#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

#include <QDebug>


namespace ebp
{


	template< class T > bool databaseObject<T>::create( const QSharedPointer<ebp::connection> & connection )
	{
		try
		{
			odb::transaction t( connection->getDB()->begin() );
			connection->getDB()->persist( *((T*)this) );
			t.commit();
		}
		catch( const odb::exception & e )
		{
			qCritical() << e.what();
			return false;
		}
		return true;
	}


	template< class T > bool databaseObject<T>::remove( const QSharedPointer<ebp::connection> & connection )
	{
		try
		{
			odb::transaction t( connection->getDB()->begin() );
			connection->getDB()->erase( *((T*)this) );
			t.commit();
		}
		catch( const odb::exception & e )
		{
			qCritical() << e.what();
			return false;
		}
		return true;
	}


	template< class T > bool databaseObject<T>::update( const QSharedPointer<ebp::connection> & connection )
	{
		try
		{
			odb::transaction t( connection->getDB()->begin() );
			connection->getDB()->update( *((T*)this) );
			t.commit();
		}
		catch( const odb::exception & e )
		{
			qCritical() << e.what();
			return false;
		}
		return true;
	}


	template< class T > QList< QSharedPointer<T> > databaseObject<T>::loadAll( const QSharedPointer<ebp::connection> & connection )
	{
		QList< QSharedPointer<T> > list;
		try
		{
			odb::transaction t( connection->getDB()->begin() );
			odb::result<T> r( connection->getDB()->query<T>() );
			for( typename odb::result<T>::iterator i( r.begin() ); i != r.end(); ++i )
			{
				list.push_back( i.load() );
			}
			t.commit();
		}
		catch( const odb::exception & e )
		{
			qCritical() << e.what();
			return QList< QSharedPointer<T> >();
		}
		return list;
	}


}