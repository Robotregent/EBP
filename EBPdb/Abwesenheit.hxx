#ifndef ABWESENHEIT_HXX
#define ABWESENHEIT_HXX


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
	/// Abwesenheiten
	class Abwesenheit : public databaseObject<Abwesenheit>
	{
		Q_DECLARE_TR_FUNCTIONS( Abwesenheit )

	public:
		Abwesenheit
		(
			const QDate & tag,
			const QString & grund
		) :
			tag_(tag),
			grund_(grund)
		{
		}

		bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const;

		const QDate & tag() const { return tag_; }
		void tag( const QDate & tag ) { tag_ = tag; }

		const QString & grund() const { return grund_; }
		void grund( const QString & grund ) { grund_ = grund; }

		const QSharedPointer<Bewohner> & bewohner() const { return bewohner_; }
		DATABASEOBJECT_DECLARE_LINK( Abwesenheit, Bewohner, Bewohner )

	private:
		friend class odb::access;
		Abwesenheit() {}

		#pragma db id auto
		unsigned long id_;

		QDate tag_;

		QString grund_;

		QSharedPointer<Bewohner> bewohner_;
	};
}


#endif // ABWESENHEIT_HXX
