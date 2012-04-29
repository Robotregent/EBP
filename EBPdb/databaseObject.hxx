#ifndef DATABASEOBJECT_HXX
#define DATABASEOBJECT_HXX


#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QDate>
#include <QSharedPointer>


#if DATABASEOBJECT_ENABLE_INVERSE

#	define DATABASEOBJECT_DECLARE_LINK_INVERSE( FROM, FROM_NAME, TO ) \
		static void link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ); \
		static void unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ); \

#	define DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( FROM, FROM_NAME, TO, TO_NAME ) \
		void FROM::link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) { TO::link##TO_NAME( to, from ); } \
		void FROM::unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) { TO::unlink##TO_NAME( to, from ); } \

#else
#	define DATABASEOBJECT_DECLARE_LINK_INVERSE( FROM, FROM_NAME, TO )
#	define DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( FROM, FROM_NAME, TO, TO_NAME )
#endif // DATABASEOBJECT_ENABLE_INVERSE


#define DATABASEOBJECT_DECLARE_LINK( FROM, FROM_NAME, TO ) \
	static void link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ); \
	static void unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ); \

#define DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( FROM, FROM_NAME, FROM_MEMBER, TO, TO_NAME, TO_MEMBER ) \
void FROM::link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	if( from && to ) \
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
} \
void FROM::unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	if( from && to ) \
	{ \
		for( QList< QLazyWeakPointer<TO> >::const_iterator i = from->FROM_MEMBER.begin(); i != from->FROM_MEMBER.end(); ++i ) \
		{ \
			if( (*i).objectId<TO>() == to->id_ ) \
			{ \
				from->FROM_MEMBER.removeAll( (*i) ); \
				break; \
			} \
		} \
		for( QList< QLazyWeakPointer<FROM> >::const_iterator i = to->TO_MEMBER.begin(); i != to->TO_MEMBER.end(); ++i ) \
		{ \
			if( (*i).objectId<FROM>() == from->id_ ) \
			{ \
				to->TO_MEMBER.removeAll( (*i) ); \
				break; \
			} \
		} \
	} \
} \

#define DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( FROM, FROM_NAME, FROM_MEMBER, TO, TO_NAME, TO_MEMBER ) \
void FROM::link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	if( from && to ) \
	{ \
		if( from->FROM_MEMBER ) \
		{ \
			FROM::unlink##FROM_NAME( from, from->FROM_MEMBER ); \
		} \
		for( QList< QLazyWeakPointer<FROM> >::const_iterator i = to->TO_MEMBER.begin(); i != to->TO_MEMBER.end(); ++i ) \
		{ \
			if( !(*i) ) \
			{ \
				qWarning() << tr("Null-Pointer in "#TO_NAME"::"#TO_MEMBER"!"); \
				continue; \
			} \
			if( (*i).objectId<FROM>() == from->id_ ) \
				goto otherSide; \
		} \
		to->TO_MEMBER.push_back( from ); \
	otherSide: \
		from->FROM_MEMBER = to; \
	} \
} \
void FROM::unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	if( from && to ) \
	{ \
		for( QList< QLazyWeakPointer<FROM> >::const_iterator i = to->TO_MEMBER.begin(); i != to->TO_MEMBER.end(); ++i ) \
		{ \
			if( (*i).objectId<FROM>() == from->id_ ) \
			{ \
				to->TO_MEMBER.removeAll( (*i) ); \
				break; \
			} \
		} \
		from->FROM_MEMBER = QSharedPointer<TO>(); \
	} \
} \

#define DATABASEOBJECT_IMPLEMENT_LINK_ONEONE( FROM, FROM_NAME, FROM_MEMBER, TO, TO_NAME, TO_MEMBER ) \
void FROM::link##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	if( from && to ) \
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
} \
void FROM::unlink##FROM_NAME( QSharedPointer<FROM> & from, QSharedPointer<TO> & to ) \
{ \
	if( from && to ) \
	{ \
		from->FROM_MEMBER = QSharedPointer<TO>(); \
		to->TO_MEMBER = QSharedPointer<FROM>(); \
	} \
} \

#define DATABASEOBJECT_IMPLEMENT_LOAD( CLASS, NAME, MEMBER_CLASS, MEMBER_NAME ) \
QList< QSharedPointer<MEMBER_CLASS> > CLASS::load##NAME( const QSharedPointer<ebp::connection> & connection ) const \
{ \
	QList< QSharedPointer<MEMBER_CLASS> > ret; \
	if( !connection ) \
	{ \
		qWarning() << tr("Connection is a Null-Pointer in "#CLASS"::load"#NAME"!"); \
		return ret; \
	} \
	odb::transaction t( connection->getDB()->begin() ); \
	for( QList< QLazyWeakPointer<MEMBER_CLASS> >::const_iterator i = MEMBER_NAME.begin(); i != MEMBER_NAME.end(); ++i ) \
	{ \
		if( !(*i) ) \
		{ \
			qWarning() << tr("Null-Pointer in "#CLASS"::"#MEMBER_NAME"!"); \
			continue; \
		} \
		QSharedPointer<MEMBER_CLASS> p = (*i).load(); \
		if( !p ) \
		{ \
			qWarning() << tr("ODB returned Null-Pointer in "#CLASS"::load"#NAME"!"); \
			continue; \
		} \
		if( p->hasPermission( connection ) ) \
		{ \
			ret.push_back( p ); \
		} \
		else \
		{ \
			qWarning() << tr("Zugriff auf \"%1\" verweigert.").arg( typeid(MEMBER_CLASS).name() ); \
		} \
	} \
	t.commit(); \
	return ret; \
} \

#define DATABASEOBJECT_DECLARE_LOAD( NAME, MEMBER_CLASS ) \
QList< QSharedPointer<MEMBER_CLASS> > load##NAME( const QSharedPointer<ebp::connection> & connection ) const; \


namespace ebp
{
	class connection;

	/// Interfacedefinition für persistente Objekte
	class databaseObjectIFace
	{
		public:
			virtual bool create( const QSharedPointer<ebp::connection> & connection ) = 0;
			virtual bool remove( const QSharedPointer<ebp::connection> & connection ) = 0;
			virtual bool update( const QSharedPointer<ebp::connection> & connection ) = 0;
			virtual bool reload( const QSharedPointer<ebp::connection> & connection ) = 0;
	};

	/// Basisklasse aller persistenten Objekte
	template< class T > class databaseObject : public databaseObjectIFace
	{
		Q_DECLARE_TR_FUNCTIONS( databaseObject )
		public:
			virtual bool create( const QSharedPointer<ebp::connection> & connection );
			virtual bool remove( const QSharedPointer<ebp::connection> & connection );
			virtual bool update( const QSharedPointer<ebp::connection> & connection );
			virtual bool reload( const QSharedPointer<ebp::connection> & connection );
			virtual bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const = 0;
			static QList< QSharedPointer<T> > loadAll( const QSharedPointer<ebp::connection> & connection );
	};
}


#endif // DATABASEOBJECT_HXX
