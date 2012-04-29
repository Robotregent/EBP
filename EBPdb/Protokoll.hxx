#ifndef PROTOKOLL_HXX
#define PROTOKOLL_HXX


#include "Bewohner.hxx"
#include "Mitarbeiter.hxx"
#include "databaseObject.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QDate>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace ebp
{
	class Bewohner;
	class Mitarbeiter;
	class connection;

	#pragma db object
	/// Protokollierung
	class Protokoll : public databaseObject<Protokoll>
	{
		Q_DECLARE_TR_FUNCTIONS( Protokoll )

	public:
		Protokoll
		(
			const QString & inhalt,
			const QDateTime & datum
		) :
			inhalt_(inhalt),
			datum_(datum)
		{
		}

		bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const;

		const QString & inhalt() const { return inhalt_; }		///< Inhalt des Protokolls lesen
		void inhalt( const QString & inhalt ) { inhalt_ = inhalt; }	///< Inhalt des Protokolls schreiben

		const QDateTime & datum() const { return datum_; }		///< Erstellungsdatum lesen
		void datum( const QDateTime & datum ) { datum_ = datum; }	///< Erstellungsdatum schreiben

		const QSharedPointer<Bewohner> & bewohner() const { return bewohner_; }
		DATABASEOBJECT_DECLARE_LINK( Protokoll, Bewohner, Bewohner )

//		QList< QSharedPointer<Mitarbeiter> > loadTeilnehmer( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Teilnehmer, Mitarbeiter )
		DATABASEOBJECT_DECLARE_LINK( Protokoll, Teilnehmer, Mitarbeiter )

//		QList< QSharedPointer<Mitarbeiter> > loadSchreiber( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Schreiber, Mitarbeiter )
		DATABASEOBJECT_DECLARE_LINK( Protokoll, Schreiber, Mitarbeiter )

	private:
		friend class odb::access;
		Protokoll() {}

		#pragma db id auto
		unsigned long id_;

		QString inhalt_;

		QDateTime datum_;

		QSharedPointer<Bewohner> bewohner_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > teilnehmer_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > schreiber_;
	};
}


#endif // PROTOKOLL_HXX
