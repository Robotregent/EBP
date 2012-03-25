#ifndef DOKUMENTATION_HXX
#define DOKUMENTATION_HXX


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
	class Dokumentation : public databaseObject<Dokumentation>
	{
		Q_DECLARE_TR_FUNCTIONS( Dokumentation )

	public:
		enum Typ
		{
			einkaufen,
			waeschepflege,
			koerperpflege,
			aufstehenUndZuBettgehen,
			partnerschaften,
			freundschaften
		};

		enum Einstufung
		{
			bekommeKeineHilfe,
			bekommeBeratung,
			bekommeAssistenz,
			machtMitarbeiter,
			istWichtig,
			willLernen
		};

		Dokumentation
		(
			const Typ & typ,
			const Einstufung & einstufung
		) :
			typ_(typ),
			einstufung_(einstufung)
		{
		}

		bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const;

		const Typ & typ() const { return typ_; }
		void typ( const Typ & typ ) { typ_ = typ; }

		const Einstufung & einstufung() const { return einstufung_; }
		void einstufung( const Einstufung & einstufung ) { einstufung_ = einstufung; }

		const QString & beschreibung() const { return beschreibung_; }
		void beschreibung( const QString & beschreibung ) { beschreibung_ = beschreibung; }

		const QString & erlaeuterungen() const { return erlaeuterungen_; }
		void erlaeuterungen( const QString & erlaeuterungen ) { erlaeuterungen_ = erlaeuterungen; }

		const QString & ziele() const { return ziele_; }
		void ziele( const QString & ziele ) { ziele_ = ziele; }

		const QSharedPointer<Bewohner> & bewohner() const { return bewohner_; }
		DATABASEOBJECT_DECLARE_LINK( Dokumentation, Bewohner, Bewohner )

	private:
		friend class odb::access;
		Dokumentation() {}

		#pragma db id auto
		unsigned long id_;

		Typ typ_;

		Einstufung einstufung_;

		QString beschreibung_;

		QString erlaeuterungen_;

		QString ziele_;

		QSharedPointer<Bewohner> bewohner_;
	};
}


#endif // DOKUMENTATION_HXX
