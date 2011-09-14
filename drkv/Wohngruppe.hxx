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
			QList< QLazyWeakPointer<Mitarbeiter> > mitarbeiter
		) :
			name_(name),
			mitarbeiter_(mitarbeiter)
		{
		}

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const QList< QLazyWeakPointer<Mitarbeiter> > & mitarbeiter() const { return mitarbeiter_; }
		void mitarbeiter( const QList< QLazyWeakPointer<Mitarbeiter> > & mitarbeiter ) { mitarbeiter_ = mitarbeiter; }

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
