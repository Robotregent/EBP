#ifndef PROTOKOLL_HXX
#define PROTOKOLL_HXX


#include "Bewohner.hxx"
#include "Mitarbeiter.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QDate>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	class Bewohner;
	class Mitarbeiter;
	class database;

	#pragma db object
	class Protokoll
	{
		Q_DECLARE_TR_FUNCTIONS( Protokoll )

	public:
		Protokoll
		(
			const QString & inhalt,
			const QDate & datum,
			const QLazyWeakPointer<Bewohner> & bewohner,
			const QList< QLazyWeakPointer<Mitarbeiter> > & teilnehmer,
			const QList< QLazyWeakPointer<Mitarbeiter> > & schreiber
		) :
			inhalt_(inhalt),
			datum_(datum),
			bewohner_(bewohner),
			teilnehmer_(teilnehmer),
			schreiber_(schreiber)
		{
		}

		const QString & inhalt() const { return inhalt_; }
		void inhalt( const QString & inhalt ) { inhalt_ = inhalt; }

		const QDate & datum() const { return datum_; }
		void datum( const QDate & datum ) { datum_ = datum; }

		const QLazyWeakPointer<Bewohner> & bewohner() const { return bewohner_; }
		void bewohner( const QLazyWeakPointer<Bewohner> & bewohner ) { bewohner_ = bewohner; }

		const QList< QLazyWeakPointer<Mitarbeiter> > & teilnehmer() const { return teilnehmer_; }
		void teilnehmer( const QList< QLazyWeakPointer<Mitarbeiter> > & teilnehmer ) { teilnehmer_ = teilnehmer; }

		const QList< QLazyWeakPointer<Mitarbeiter> > & schreiber() const { return schreiber_; }
		void schreiber( const QList< QLazyWeakPointer<Mitarbeiter> > & schreiber ) { schreiber_ = schreiber; }

		bool create( const QSharedPointer<drkv::database> & db );
		bool remove( const QSharedPointer<drkv::database> & db );
		bool update( const QSharedPointer<drkv::database> & db );

	private:
		friend class odb::access;
		Protokoll() {}

		#pragma db id auto
		unsigned long id_;

		QString inhalt_;

		QDate datum_;

		QLazyWeakPointer<Bewohner> bewohner_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > teilnehmer_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > schreiber_;
	};
}


#endif // PROTOKOLL_HXX
