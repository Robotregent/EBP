#include "Bewohnerereignis.hxx"
#include "Bewohnerereignis-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Bewohnerereignis>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Bewohnerereignis, Bewohner, bewohner_, Bewohner, Ereignis, ereignisse_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Bewohnerereignis, Schreiber, schreiber_, Mitarbeiter, Bewohnerereignis, bewohnerereignisse_ )


DATABASEOBJECT_IMPLEMENT_LOAD( Bewohnerereignis, Schreiber, Mitarbeiter, schreiber_ )


QList< QSharedPointer< Bewohnerereignis > > Bewohnerereignis::loadAll( const QSharedPointer<ebp::connection> & connection )
{
	QList< QSharedPointer<Bewohnerereignis> > list;

	try
	{
		odb::transaction t( connection->getDB()->begin() );
		odb::result<Bewohnerereignis> r( connection->getDB()->query<Bewohnerereignis>() );
		for( typename odb::result<Bewohnerereignis>::iterator i( r.begin() ); i != r.end(); ++i )
		{
			QSharedPointer<Bewohnerereignis> be = i.load();
			if( be->bewohner()->wohngruppe() )
			{
				if( be->bewohner()->wohngruppe()->hasPermission( connection ) )
				{
					list.push_back( be );
				}
				else
				{
					qWarning() << tr("Zugriff auf Bewohnerereignis von Bewohner \"%1\" verweigert.").arg(be->bewohner()->nummer_);
				}
			}
			else
			{
				list.push_back( be );
			}
		}
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return QList< QSharedPointer<Bewohnerereignis> >();
	}
	return list;
}
