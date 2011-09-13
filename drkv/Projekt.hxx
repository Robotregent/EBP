#ifndef PROJEKT_HXX
#define PROJEKT_HXX


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
	class Mitarbeiter;
	class database;

	#pragma db object
	class Projekt
	{
		Q_DECLARE_TR_FUNCTIONS( Projekt )

	public:
		enum Typen
		{
			typ1,
			typ2,
			typ3,
			typ4
		};

		Projekt
		(
			const QString & name,
			const QString & beschreibung,
			const QDate & beginn,
			const QDate & ende,
			const Typen & typ,
			const QList< QLazyWeakPointer<Mitarbeiter> > & verantwortliche
		) :
			name_(name),
			beschreibung_(beschreibung),
			beginn_(beginn),
			ende_(ende),
			typ_(typ),
			verantwortliche_(verantwortliche)
		{
		}

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const QString & beschreibung() const { return beschreibung_; }
		void beschreibung( const QString & beschreibung ) { beschreibung_ = beschreibung; }

		const QDate & beginn() const { return beginn_; }
		void beginn( const QDate & beginn ) { beginn_ = beginn; }

		const QDate & ende() const { return ende_; }
		void ende( const QDate & ende ) { ende_ = ende; }

		const Typen typ() const { return typ_; }
		void typ( const Typen & typ ) { typ_ = typ; }

		const QList< QLazyWeakPointer<Mitarbeiter> > & verantwortliche() const { return verantwortliche_; }
		void verantwortliche( const QList< QLazyWeakPointer<Mitarbeiter> > & verantwortliche ) { verantwortliche_ = verantwortliche; }

	private:
		friend class odb::access;
		Projekt() {}

		#pragma db id auto
		unsigned long id_;

		QString name_;

		QString beschreibung_;

		QDate beginn_;

		QDate ende_;

		Typen typ_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > verantwortliche_;
	};
}


#endif // PROJEKT_HXX
