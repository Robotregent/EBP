#ifndef WOHNGRUPPENEREIGNIS_HXX
#define WOHNGRUPPENEREIGNIS_HXX


#include "Mitarbeiter.hxx"
#include "Wohngruppe.hxx"
#include "databaseObject.hxx"

#include <QCoreApplication>
#include <QString>
#include <QDateTime>
#include <QList>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace ebp
{
	class Mitarbeiter;
	class Wohngruppe;
	class connection;

	#pragma db object
	/// Wohngruppenereignisse
	class Wohngruppenereignis : public databaseObject<Wohngruppenereignis>
	{
		Q_DECLARE_TR_FUNCTIONS( Wohngruppenereignis )

	public:
		Wohngruppenereignis
		(
			const QDateTime & zeitpunkt,
			const QString & text
		) :
			zeitpunkt_(zeitpunkt),
			text_(text)
		{
		}

		bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const;

		const QDateTime & zeitpunkt() const { return zeitpunkt_; }
		void zeitpunkt( const QDateTime & zeitpunkt ) { zeitpunkt_ = zeitpunkt; }

		const QString & text() const { return text_; }
		void text( const QString & text ) { text_ = text; }

		const QSharedPointer<Wohngruppe> & wohngruppe() const { return wohngruppe_; }
		DATABASEOBJECT_DECLARE_LINK( Wohngruppenereignis, Wohngruppe, Wohngruppe )

//		const QList< QSharedPointer<Mitarbeiter> > & loadSchreiber( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Schreiber, Mitarbeiter )
		DATABASEOBJECT_DECLARE_LINK( Wohngruppenereignis, Schreiber, Mitarbeiter )

	private:
		friend class odb::access;
		Wohngruppenereignis() {}

		#pragma db id auto
		unsigned long id_;

		QDateTime zeitpunkt_;

		QString text_;

		QSharedPointer<Wohngruppe> wohngruppe_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > schreiber_;
	};
}


#endif // WOHNGRUPPENEREIGNIS_HXX
