#include "connectiontest.h"
//Implementation
/**
  * \brief Initialisiert die Connection
  */
void ConnectionTest::initTestCase()
{
    this->testCon= QSharedPointer<ebp::connection> (new ebp::connection("testUser","testDB"));
    QVERIFY(!this->testCon.isNull());
    //testCon->establish("test");
}
void ConnectionTest::establishCon()
{
    this->testCon.clear();
    this->testCon= QSharedPointer<ebp::connection> (new ebp::connection("testUser","testDB"));
    QVERIFY(this->testCon->establish("test"));

    this->testCon.clear();
    this->testCon= QSharedPointer<ebp::connection> (new ebp::connection("testUser","testDB"));
    QVERIFY(this->testCon->establish("")!=true);

    this->testCon.clear();
    this->testCon= QSharedPointer<ebp::connection> (new ebp::connection("testUser","testDB"));
    QVERIFY(this->testCon->establish("falschesPasswort")!=true);
}
/**
  * \brief Testet das Setzen und Lesen der Datenbankfelder
  */
void ConnectionTest::getAttributes()
{
    //User
    QString userName;
    userName=this->testCon->user();
    QVERIFY(!userName.isEmpty());

    //database
    QString database = this->testCon->database();
    QVERIFY(!database.isEmpty());

    //host
    QString host = this->testCon->host();
    QVERIFY(!host.isEmpty());

    //Port
    int port = 0;
    port = this->testCon->port();
    QVERIFY(port!=0);

    //database
    odb::mysql::database *db = NULL;
    db = this->testCon->getDB();
    QVERIFY(db!=NULL);

}
/**
  * \brief Löscht die TestConnection
  */
void ConnectionTest::cleanupTestCase()
{
    this->testCon.clear();
}
/**
  * \brief testUser muss als Mitarbeiter eingetragen sein, um Test bestehen zu können
  */
void ConnectionTest::loginMitarbeiter()
{
    this->testCon.clear();
    this->testCon= QSharedPointer<ebp::connection> (new ebp::connection("testUser","testDB"));
    QVERIFY(this->testCon->establish("test"));
    //testUser muss Als mitarbeiter eingetragen sein
    QSharedPointer<ebp::Mitarbeiter> tmpMA = this->testCon->mitarbeiter();
    QVERIFY(!tmpMA.isNull());
}

