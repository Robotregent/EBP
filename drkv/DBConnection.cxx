#include "DBConnection.hxx"

#include "Mitarbeiter-odb.hxx"

#include <odb/core.hxx>
#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

#include <QString>
#include <QDebug>


using namespace drkv;


DBConnection::DBConnection( QString user, QString password, QString database, QString host, unsigned int port )
{
	this->db = new odb::mysql::database( user.toStdString(), password.toStdString(), database.toStdString(), host.toStdString(), port );
}


bool DBConnection::addMitarbeiter( Mitarbeiter m )
{
	odb::transaction t( db->begin () );
	db->persist( m );
	t.commit();
	return true;
}
