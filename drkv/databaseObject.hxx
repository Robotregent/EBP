#ifndef DATABASEOBJECT_HXX
#define DATABASEOBJECT_HXX


#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QDate>
#include <QSharedPointer>


namespace drkv
{
	class connection;

	class databaseObjectIFace
	{
	public:
		virtual bool create( const QSharedPointer<drkv::connection> & connection ) = 0;
		virtual bool remove( const QSharedPointer<drkv::connection> & connection ) = 0;
		virtual bool update( const QSharedPointer<drkv::connection> & connection ) = 0;
	};

	template< class T > class databaseObject : public databaseObjectIFace
	{
	public:
		virtual bool create( const QSharedPointer<drkv::connection> & connection );
		virtual bool remove( const QSharedPointer<drkv::connection> & connection );
		virtual bool update( const QSharedPointer<drkv::connection> & connection );
		static QList< QSharedPointer<T> > getAll( const QSharedPointer<drkv::connection> & connection );
	};
}


#endif // DATABASEOBJECT_HXX
