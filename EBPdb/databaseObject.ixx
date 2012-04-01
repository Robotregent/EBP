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


	template< class T > bool databaseObject<T>::reload( const QSharedPointer<ebp::connection> & connection )
	{
		try
		{
			odb::transaction t( connection->getDB()->begin() );
			connection->getDB()->reload( *((T*)this) );
			t.commit();
		}
		catch( const odb::exception & e )
		{
			qCritical() << e.what();
			return false;
		}
		return true;
	}

/*
	template< class T > bool databaseObject<T>::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
	{
		return true;
	}
*/

	template< class T > QList< QSharedPointer<T> > databaseObject<T>::loadAll( const QSharedPointer<ebp::connection> & connection )
	{
		QList< QSharedPointer<T> > list;
		try
		{
			odb::transaction t( connection->getDB()->begin() );
			odb::result<T> r( connection->getDB()->query<T>() );
			for( typename odb::result<T>::iterator i( r.begin() ); i != r.end(); ++i )
			{
				QSharedPointer<T> p = i.load();
				if( !p )
				{
					qWarning() << tr("ODB gab null pointer beim Laden von \"%1\" zurück!").arg( typeid(T).name() );
					continue;
				}
				if( p->hasPermission( connection ) )
				{
					list.push_back( p );
				}
				else
				{
					qWarning() << tr("Zugriff auf \"%1\" verweigert.").arg( typeid(T).name() );
				}
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
