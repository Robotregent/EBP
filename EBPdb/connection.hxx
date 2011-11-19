#ifndef CONNECTION_HXX
#define CONNECTION_HXX


#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/database.hxx>
#include <odb/mysql/database.hxx>


namespace ebp
{
	class Mitarbeiter;

	class connection
	{
		Q_DECLARE_TR_FUNCTIONS( connection )

	public:
		connection
		(
			const QString & user,
			const QString & database,
			const QString & host = "localhost",
			unsigned int port = 3306
		);
		~connection();

		bool establish( const QString & password );
		bool isEstablished() const { return db; }
		void flushCache();
		const QString & user() const { return dbUser; }
		const QString & database() const { return dbDatabase; }
		const QString & host() const { return dbHost; }
		unsigned int port() const { return dbPort; }
		odb::mysql::database * getDB() const { return db; }
		unsigned long long execute( const QString & statement ) { return db->execute( statement.toStdString() ); }
		void executeCreateUser( const Mitarbeiter & mitarbeiter, const QString & from, const QString & password );
		void executeCreateUser( const Mitarbeiter & mitarbeiter, const QString & password );
		void executeDropUser( const Mitarbeiter & mitarbeiter, const QString & from );
		void executeDropUser( const Mitarbeiter & mitarbeiter );
		void executeSetPassword( const Mitarbeiter & mitarbeiter, const QString & from, const QString & password );
		void executeSetPassword( const Mitarbeiter & mitarbeiter, const QString & password );

	private:
		QString dbUser;
		QString dbDatabase;
		QString dbHost;
		unsigned int dbPort;
		odb::mysql::database * db;
		odb::session * s;
		QSharedPointer<Mitarbeiter> connectedUser;
	};
}


#endif // CONNECTION_HXX
