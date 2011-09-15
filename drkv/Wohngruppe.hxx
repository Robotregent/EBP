#ifndef WOHNGRUPPE_HXX
#define WOHNGRUPPE_HXX


#include "Mitarbeiter.hxx"
#include "Bewohner.hxx"

#include <QString>
#include <QList>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	class Mitarbeiter;
	class Bewohner;
	class database;

	#pragma db object
	class Wohngruppe
	{
		Q_DECLARE_TR_FUNCTIONS( Wohngruppe )

	public:
		Wohngruppe
		(
			const QString & name,
			const QLazyWeakPointer<Mitarbeiter> & bezugsbetreuer,
			const QList< QLazyWeakPointer<Mitarbeiter> > & mitarbeiter,
			const QList< QLazyWeakPointer<Bewohner> > & bewohner
		) :
			name_(name),
			bezugsbetreuer_(bezugsbetreuer),
			mitarbeiter_(mitarbeiter),
			bewohner_(bewohner)
		{
		}

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const QLazyWeakPointer<Mitarbeiter> & bezugsbetreuer() const { return bezugsbetreuer_; }
		void bezugsbetreuer( const QLazyWeakPointer<Mitarbeiter> & bezugsbetreuer ) { bezugsbetreuer_ = bezugsbetreuer; }

		const QList< QLazyWeakPointer<Mitarbeiter> > & mitarbeiter() const { return mitarbeiter_; }
		void mitarbeiter( const QList< QLazyWeakPointer<Mitarbeiter> > & mitarbeiter ) { mitarbeiter_ = mitarbeiter; }

		const QList< QLazyWeakPointer<Bewohner> > & bewohner() const { return bewohner_; }
		void bewohner( const QList< QLazyWeakPointer<Bewohner> > & bewohner ) { bewohner_ = bewohner; }

	private:
		friend class odb::access;
		Wohngruppe() {}

		#pragma db id auto
		unsigned long id_;

		QString name_;

		QLazyWeakPointer<Mitarbeiter> bezugsbetreuer_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > mitarbeiter_;

		#pragma db unordered
		QList< QLazyWeakPointer<Bewohner> > bewohner_;
	};
}


#endif // WOHNGRUPPE_HXX
