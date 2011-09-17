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


namespace drkv
{
	class Mitarbeiter;
	class Wohngruppe;
	class connection;

	#pragma db object
	class Wohngruppenereignis : public databaseObject<Wohngruppenereignis>
	{
		Q_DECLARE_TR_FUNCTIONS( Wohngruppenereignis )

	public:
		Wohngruppenereignis
		(
			const QDateTime & zeitpunkt,
			const QString & text,
			const QList< QLazyWeakPointer<Mitarbeiter> > & schreiber,
			const QLazyWeakPointer<Wohngruppe> & wohngruppe
		) :
			zeitpunkt_(zeitpunkt),
			text_(text),
			schreiber_(schreiber),
			wohngruppe_(wohngruppe)
		{
		}

		const QDateTime & zeitpunkt() const { return zeitpunkt_; }
		void zeitpunkt( const QDateTime & zeitpunkt ) { zeitpunkt_ = zeitpunkt; }

		const QString & text() const { return text_; }
		void text( const QString & text ) { text_ = text; }

		const QList< QLazyWeakPointer<Mitarbeiter> > & schreiber() const { return schreiber_; }
		void schreiber( const QList< QLazyWeakPointer<Mitarbeiter> > & schreiber ) { schreiber_ = schreiber; }

		const QLazyWeakPointer<Wohngruppe> & wohngruppe() const { return wohngruppe_; }
		void wohngruppe( const QLazyWeakPointer<Wohngruppe> & wohngruppe ) { wohngruppe_ = wohngruppe; }

	private:
		friend class odb::access;
		Wohngruppenereignis() {}

		#pragma db id auto
		unsigned long id_;

		QDateTime zeitpunkt_;

		QString text_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > schreiber_;

		QLazyWeakPointer<Wohngruppe> wohngruppe_;
	};
}


#endif // WOHNGRUPPENEREIGNIS_HXX
