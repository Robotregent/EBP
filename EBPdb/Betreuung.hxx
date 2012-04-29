#ifndef BETREUUNG_HXX
#define BETREUUNG_HXX


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
	/// Betreuungen
	class Betreuung : public databaseObject<Betreuung>
	{
		Q_DECLARE_TR_FUNCTIONS( Betreuung )

	public:
		Betreuung
		(
		) :
			gesundheitsfuersorge_(false),
			vermoegensfuersorge_(false),
			aufenthaltsbestimmung_(false)
		{
		}

		bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const;

		const QString & vorname() const { return vorname_; }
		void vorname( const QString & vorname ) { vorname_ = vorname; }

		const QString & nachname() const { return nachname_; }
		void nachname( const QString & nachname ) { nachname_ = nachname; }

		const QString & verein() const { return verein_; }
		void verein( const QString & verein ) { verein_ = verein; }

		const QString & strasse() const { return strasse_; }
		void strasse( const QString & strasse ) { strasse_ = strasse; }

		const QString & plz() const { return plz_; }
		void plz( const QString & plz ) { plz_ = plz; }

		const QString & ort() const { return ort_; }
		void ort( const QString & ort ) { ort_ = ort; }

		const QString & telefon() const { return telefon_; }
		void telefon( const QString & telefon ) { telefon_ = telefon; }

		const QString & fax() const { return fax_; }
		void fax( const QString & fax ) { fax_ = fax; }

		const QString & email() const { return email_; }
		void email( const QString & email ) { email_ = email; }

		const bool & gesundheitsfuersorge() const { return gesundheitsfuersorge_; }
		void gesundheitsfuersorge( const bool & gesundheitsfuersorge ) { gesundheitsfuersorge_ = gesundheitsfuersorge; }

		const bool & vermoegensfuersorge() const { return vermoegensfuersorge_; }
		void vermoegensfuersorge( const bool & vermoegensfuersorge ) { vermoegensfuersorge_ = vermoegensfuersorge; }

		const bool & aufenthaltsbestimmung() const { return aufenthaltsbestimmung_; }
		void aufenthaltsbestimmung( const bool & aufenthaltsbestimmung ) { aufenthaltsbestimmung_ = aufenthaltsbestimmung; }

		const QSharedPointer<Bewohner> bewohner() const { return bewohner_; }
		DATABASEOBJECT_DECLARE_LINK( Betreuung, Bewohner, Bewohner )

	private:
		friend class odb::access;

		#pragma db id auto
		unsigned long id_;

		QString vorname_;

		QString nachname_;

		QString verein_;

		QString strasse_;

		QString plz_;

		QString ort_;

		QString telefon_;

		QString fax_;

		QString email_;

		bool gesundheitsfuersorge_;

		bool vermoegensfuersorge_;

		bool aufenthaltsbestimmung_;

		QSharedPointer<Bewohner> bewohner_;
	};
}


#endif // BETREUUNG_HXX
