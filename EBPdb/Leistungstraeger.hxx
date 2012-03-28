#ifndef LEISTUNGSTRAEGER_HXX
#define LEISTUNGSTRAEGER_HXX


#include "Mitarbeiter.hxx"
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
	class Leistungstraeger : public databaseObject<Leistungstraeger>
	{
		Q_DECLARE_TR_FUNCTIONS( Leistungstraeger )

	public:
		Leistungstraeger
		(
			const QString & name
		) :
			name_(name)
		{
		}

		bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const;

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const QString & strasse() const { return strasse_; }
		void strasse( const QString & strasse ) { strasse_ = strasse; }

		const QString & plz() const { return plz_; }
		void plz( const QString & plz ) { plz_ = plz; }

		const QString & ort() const { return ort_; }
		void ort( const QString & ort ) { ort_ = ort; }

		const QString & ansprechpartner() const { return ansprechpartner_; }
		void ansprechpartner( const QString & ansprechpartner ) { ansprechpartner_ = ansprechpartner; }

		const QString & telefon() const { return telefon_; }
		void telefon( const QString & telefon ) { telefon_ = telefon; }

		const QString & fax() const { return fax_; }
		void fax( const QString & fax ) { fax_ = fax; }

		const QString & email() const { return email_; }
		void email( const QString & email ) { email_ = email; }

		const QString & anmerkung() const { return anmerkung_; }
		void anmerkung( const QString & anmerkung ) { anmerkung_ = anmerkung; }

		DATABASEOBJECT_DECLARE_LOAD( Bewohner, Bewohner )
		DATABASEOBJECT_DECLARE_LINK( Leistungstraeger, Bewohner, Bewohner )

	private:
		friend class odb::access;
		Leistungstraeger() {}

		#pragma db id auto
		unsigned long id_;

		QString name_;

		QString strasse_;

		QString plz_;

		QString ort_;

		QString ansprechpartner_;

		QString telefon_;

		QString fax_;

		QString email_;

		QString anmerkung_;

		#pragma db unordered
		QList< QLazyWeakPointer<Bewohner> > bewohner_;

	};
}


#endif // LEISTUNGSTRAEGER_HXX
