#ifndef VERFUEGUNG_HXX
#define VERFUEGUNG_HXX


#include "Bewohner.hxx"
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
	class Bewohner;
	class connection;

	#pragma db object
	class Verfuegung : public databaseObject<Verfuegung>
	{
		Q_DECLARE_TR_FUNCTIONS( Verfuegung )

	public:
		enum Typ
		{
			Fixierung,
			Bettgitter,
			Psychopharmaka,
			Patientenverfuegung
		};

		Verfuegung
		(
			const bool & aktiv,
			const Typ & typ,
			const QDate & gerichtsbescheid,
			const QString & grund
		) :
			aktiv_(aktiv),
			typ_(typ),
			gerichtsbescheid_(gerichtsbescheid),
			grund_(grund)
		{
		}

		bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const;

		const bool & aktiv() const { return aktiv_; }
		void aktiv( const bool & aktiv ) { aktiv_ = aktiv; }
		
		const Typ & typ() const { return typ_; }
		void typ( const Typ & typ ) { typ_ = typ; }

		const QDate & gerichtsbescheid() const { return gerichtsbescheid_; }
		void gerichtsbescheid( const QDate & gerichtsbescheid ) { gerichtsbescheid_ = gerichtsbescheid; }

		const QString & grund() const { return grund_; }
		void grund( const QString & grund ) { grund_ = grund; }

		const QSharedPointer<Bewohner> & bewohner() const { return bewohner_; }
		DATABASEOBJECT_DECLARE_LINK( Verfuegung, Bewohner, Bewohner )

	private:
		friend class odb::access;
		Verfuegung() {}

		#pragma db id auto
		unsigned long id_;

		bool aktiv_;

		Typ typ_;

		QDate gerichtsbescheid_;

		QString grund_;

		QSharedPointer<Bewohner> bewohner_;
	};
}


#endif // VERFUEGUNG_HXX
