#ifndef WOHNHEIM_HXX
#define WOHNHEIM_HXX


#include "Wohngruppe.hxx"
#include "databaseObject.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace ebp
{
	class Wohngruppe;
	class connection;

	#pragma db object
	/// Wohnheime
	class Wohnheim : public databaseObject<Wohnheim>
	{
		Q_DECLARE_TR_FUNCTIONS( Wohnheim )

	public:
		Wohnheim
		(
			const QString & name
		) :
			name_(name)
		{
		}

		bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const;

		const QString & name() const { return name_; }
		QString & name() { return name_; }

//		QList< QSharedPointer<Wohngruppe> > loadWohngruppen( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Wohngruppen, Wohngruppe )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Wohnheim, Wohngruppe, Wohngruppe )

	private:
		friend class odb::access;
		friend class Wohngruppe;
		Wohnheim() {}

		#pragma db id auto
		unsigned long id_;

		QString name_;

		#pragma db unordered inverse(wohnheim_)
		QList< QLazyWeakPointer<Wohngruppe> > wohngruppen_;
	};
}


#endif // WOHNHEIM_HXX
