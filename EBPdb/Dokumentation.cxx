#include "Dokumentation.hxx"
#include "Dokumentation-odb.hxx"
#include "Bewohner-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Dokumentation>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Dokumentation, Bewohner, bewohner_, Bewohner, Dokumentation, dokumentationen_ )
/*
void Dokumentation::linkBewohner( QSharedPointer<Dokumentation> & from, QSharedPointer<Bewohner> & to )
{
	if( from && to )
	{
		if( from->bewohner_ )
		{
			Dokumentation::unlinkBewohner( from, from->bewohner_ );
		}
		for( QList< QLazyWeakPointer<Dokumentation> >::const_iterator i = to->dokumentationen_.begin(); i != to->dokumentationen_.end(); ++i )
		{
			if( !(*i) )
			{
				qWarning() << tr("Null-pointer in Bewohner::dokumentationen_!");
				continue;
			}
			if( (*i).objectId<Dokumentation>() == from->id_ )
				goto otherSide;
		}
		to->dokumentationen_.push_back( from );
	otherSide:
		from->bewohner_ = to;
	}
}
void Dokumentation::unlinkBewohner( QSharedPointer<Dokumentation> & from, QSharedPointer<Bewohner> & to )
{
	if( from && to )
	{
		for( QList< QLazyWeakPointer<Dokumentation> >::const_iterator i = to->dokumentationen_.begin(); i != to->dokumentationen_.end(); ++i )
		{
			if( (*i).objectId<Dokumentation>() == from->id_ )
			{
				to->dokumentationen_.removeAll( (*i) );
				break;
			}
		}
		from->bewohner_ = QSharedPointer<Bewohner>(); \
	}
}
*/
bool Dokumentation::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
{
	if( bewohner() )
		return bewohner()->hasPermission( connection );
	return true;
}
