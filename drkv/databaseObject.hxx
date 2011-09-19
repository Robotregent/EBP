#ifndef DATABASEOBJECT_HXX
#define DATABASEOBJECT_HXX


#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QDate>
#include <QSharedPointer>


#define DATABASEOBJECT_DECLARE_LINK( FROM, FROM_NAME, TO ) \
	static void link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ); \
	static void unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ); \

#define DATABASEOBJECT_DECLARE_LINK_INVERSE( FROM, FROM_NAME, TO ) \
	static void link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ); \
	static void unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ); \

#define DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( FROM, FROM_NAME, TO, TO_NAME ) \
	void FROM::link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) { TO::link##TO_NAME( to, from ); } \
	void FROM::unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) { TO::unlink##TO_NAME( to, from ); } \

#define DATABASEOBJECT_IMPLEMENT_LINK_MANYTOMANY( FROM, FROM_NAME, FROM_MEMBER, TO, TO_NAME, TO_MEMBER ) \
void FROM::link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	for( QList< QLazyWeakPointer<TO> >::const_iterator i = from->FROM_MEMBER.begin(); i != from->FROM_MEMBER.end(); ++i ) \
	{ \
		if( (*i).objectId<TO>() == to->id_ ) \
			goto otherSide; \
	} \
	from->FROM_MEMBER.push_back( to ); \
otherSide: \
	for( QList< QLazyWeakPointer<FROM> >::const_iterator i = to->TO_MEMBER.begin(); i != to->TO_MEMBER.end(); ++i ) \
	{ \
		if( (*i).objectId<FROM>() == from->id_ ) \
			return; \
	} \
	to->TO_MEMBER.push_back( from ); \
} \
void FROM::unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	for( QList< QLazyWeakPointer<TO> >::const_iterator i = from->FROM_MEMBER.begin(); i != from->FROM_MEMBER.end(); ++i ) \
	{ \
		if( (*i).objectId<TO>() == to->id_ ) \
		{ \
			from->FROM_MEMBER.removeAll( (*i) ); \
			i = from->FROM_MEMBER.begin(); \
		} \
	} \
	for( QList< QLazyWeakPointer<FROM> >::const_iterator i = to->TO_MEMBER.begin(); i != to->TO_MEMBER.end(); ++i ) \
	{ \
		if( (*i).objectId<FROM>() == from->id_ ) \
		{ \
			to->TO_MEMBER.removeAll( (*i) ); \
			i = to->TO_MEMBER.begin(); \
		} \
	} \
} \

#define DATABASEOBJECT_IMPLEMENT_LINK_MANYTOONE( FROM, FROM_NAME, FROM_MEMBER, TO, TO_NAME, TO_MEMBER ) \
void FROM::link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	if( to->TO_MEMBER ) \
	{\
		FROM::unlink##FROM_NAME( to->TO_MEMBER, to );\
	}\
	for( QList< QLazyWeakPointer<TO> >::const_iterator i = from->FROM_MEMBER.begin(); i != from->FROM_MEMBER.end(); ++i ) \
	{ \
		if( (*i).objectId<TO>() == to->id_ ) \
			goto otherSide; \
	} \
	from->FROM_MEMBER.push_back( to ); \
otherSide: \
	to->TO_MEMBER = from; \
} \
void FROM::unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	for( QList< QLazyWeakPointer<TO> >::const_iterator i = from->FROM_MEMBER.begin(); i != from->FROM_MEMBER.end(); ++i ) \
	{ \
		if( (*i).objectId<TO>() == to->id_ ) \
		{ \
			from->FROM_MEMBER.removeAll( (*i) ); \
			i = from->FROM_MEMBER.begin(); \
		} \
	} \
	to->TO_MEMBER = QSharedPointer<FROM>(); \
} \

#define DATABASEOBJECT_IMPLEMENT_LINK_ONETOONE( FROM, FROM_NAME, FROM_MEMBER, TO, TO_NAME, TO_MEMBER ) \
void FROM::link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	if( to->TO_MEMBER ) \
	{\
		FROM::unlink##FROM_NAME( to->TO_MEMBER, to );\
	}\
	if( from->FROM_MEMBER ) \
	{\
		FROM::unlink##FROM_NAME( from, from->FROM_MEMBER );\
	}\
	from->FROM_MEMBER = to; \
	to->TO_MEMBER = from; \
} \
void FROM::unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	from->FROM_MEMBER = QSharedPointer<TO>(); \
	to->TO_MEMBER = QSharedPointer<FROM>(); \
} \


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
		static QList< QSharedPointer<T> > loadAll( const QSharedPointer<drkv::connection> & connection );
	};
}


#endif // DATABASEOBJECT_HXX
