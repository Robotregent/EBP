#ifndef WOHNGRUPPE_HXX
#define WOHNGRUPPE_HXX


#include "Mitarbeiter.hxx"

#include <QString>
#include <QSharedPointer>
#include <QList>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	// forward declarations - in case of mutual inclusions
	class Mitarbeiter;

	#pragma db object
	class Wohngruppe
	{
	public:
		Wohngruppe
		(
			QList< QLazyWeakPointer<Mitarbeiter> > mitarbeiter,
			const QString & name
		) :
			mitarbeiter_(mitarbeiter),
			name_(name)
		{
		}

		const QList< QLazyWeakPointer<Mitarbeiter> > & mitarbeiter() const { return mitarbeiter_; }
		void mitarbeiter( QList< QLazyWeakPointer<Mitarbeiter> > mitarbeiter ) { mitarbeiter_ = mitarbeiter; }

		const QString & name() const { return name_; }
		void name( QString name ) { name_ = name; }

	private:
		friend class odb::access;
		Wohngruppe() {}

		#pragma db id auto
		unsigned long id_;

		#pragma db unordered inverse(wohngruppe_)
		QList< QLazyWeakPointer<Mitarbeiter> > mitarbeiter_;

		QString name_;
	};
}


#endif // WOHNGRUPPE_HXX
