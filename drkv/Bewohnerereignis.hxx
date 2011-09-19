#ifndef BEWOHNEREREIGNIS_HXX
#define BEWOHNEREREIGNIS_HXX


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


namespace drkv
{
	class Mitarbeiter;
	class Bewohner;
	class connection;

	#pragma db object
	class Bewohnerereignis : databaseObject<Bewohnerereignis>
	{
		Q_DECLARE_TR_FUNCTIONS( Bewohnerereignis )

	public:
		Bewohnerereignis
		(
			const QDateTime & zeitpunkt,
			const QString & text,
			const QSharedPointer<Bewohner> & bewohner
		) :
			zeitpunkt_(zeitpunkt),
			text_(text),
			bewohner_(bewohner)
		{
		}

		const QDateTime & zeitpunkt() const { return zeitpunkt_; }
		void zeitpunkt( const QDateTime & zeitpunkt ) { zeitpunkt_ = zeitpunkt; }

		const QString & text() const { return text_; }
		void text( const QString & text ) { text_ = text; }

	private:
		friend class odb::access;
		Bewohnerereignis() {}

		#pragma db id auto
		unsigned long id_;

		QDateTime zeitpunkt_;

		QString text_;

		QSharedPointer<Bewohner> bewohner_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > schreiber_;

	};
}


#endif // BEWOHNEREREIGNIS_HXX
