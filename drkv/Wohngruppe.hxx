#ifndef WOHNGRUPPE_HXX
#define WOHNGRUPPE_HXX


#include "Mitarbeiter.hxx"
#include "Bewohner.hxx"
#include "Wohngruppenereignis.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	class Mitarbeiter;
	class Bewohner;
	class Wohngruppenereignis;
	class connection;

	#pragma db object
	class Wohngruppe
	{
		Q_DECLARE_TR_FUNCTIONS( Wohngruppe )

	public:
		Wohngruppe
		(
			const QString & name,
			const QList< QLazyWeakPointer<Mitarbeiter> > & mitarbeiter,
			const QList< QLazyWeakPointer<Bewohner> > & bewohner,
			const QList< QLazyWeakPointer<Wohngruppenereignis> > & ereignisse
		) :
			name_(name),
			mitarbeiter_(mitarbeiter),
			bewohner_(bewohner),
			ereignisse_(ereignisse)
		{
		}

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const QList< QLazyWeakPointer<Mitarbeiter> > & mitarbeiter() const { return mitarbeiter_; }
		void mitarbeiter( const QList< QLazyWeakPointer<Mitarbeiter> > & mitarbeiter ) { mitarbeiter_ = mitarbeiter; }

		const QList< QLazyWeakPointer<Bewohner> > & bewohner() const { return bewohner_; }
		void bewohner( const QList< QLazyWeakPointer<Bewohner> > & bewohner ) { bewohner_ = bewohner; }

		const QList< QLazyWeakPointer<Wohngruppenereignis> > & ereignisse() const { return ereignisse_; }
		void ereignisse( const QList< QLazyWeakPointer<Wohngruppenereignis> > & ereignisse ) { ereignisse_ = ereignisse; }

		bool create( const QSharedPointer<drkv::connection> & connection );
		bool remove( const QSharedPointer<drkv::connection> & connection );
		bool update( const QSharedPointer<drkv::connection> & connection );
		static QList< QSharedPointer<Wohngruppe> > getAll( const QSharedPointer<drkv::connection> & connection );

	private:
		friend class odb::access;
		Wohngruppe() {}

		#pragma db id auto
		unsigned long id_;

		QString name_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > mitarbeiter_;

		#pragma db unordered
		QList< QLazyWeakPointer<Bewohner> > bewohner_;

		#pragma db unordered inverse(wohngruppe_)
		QList< QLazyWeakPointer<Wohngruppenereignis> > ereignisse_;
	};
}


#endif // WOHNGRUPPE_HXX
