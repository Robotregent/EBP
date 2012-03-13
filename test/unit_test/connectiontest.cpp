#include <QObject>
#include <QtTest/QtTest>
#include <EBPdb/connection.hxx>
#include <EBPdb/Mitarbeiter.hxx>
#include <exception>

//Declaration
class ConnectionTest : public QObject
{
    Q_OBJECT
    ebp::connection *testCon;
private slots:
    void initTestCase();
    void establishCon();
    void cleanupTestCase();
    void loginMitarbeiter();
    void getAttributes();


};

//Implementation
void ConnectionTest::initTestCase()
{
    this->testCon = NULL;
    this->testCon= new ebp::connection("testUser","testDB");
    QVERIFY(this->testCon!=NULL);
}
void ConnectionTest::establishCon()
{
    //this->testCon= new ebp::connection("testUser","testDB");
    QVERIFY(this->testCon->establish("")!=true);
    delete this->testCon;

    this->testCon= new ebp::connection("testUser","testDB");
    QVERIFY(this->testCon->establish("falschesPasswort")!=true);
    delete this->testCon;

    this->testCon= new ebp::connection("testUser","testDB");
    QVERIFY(this->testCon->establish("testPasswort")==true);

}

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
  * \brief
  */
void ConnectionTest::cleanupTestCase()
{

    try
    {
	delete this->testCon;
	QVERIFY(true);
    }
    catch (std::exception ex)
    {
	QVERIFY(false);
    }
}
/**
  * \brief testUser muss als Mitarbeiter eingetragen sein, um Test bestehen zu können
  */
void ConnectionTest::loginMitarbeiter()
{
    //testUser muss Als mitarbeiter eingetragen sein
    QSharedPointer<ebp::Mitarbeiter> tmpMA = this->testCon->mitarbeiter();
    QVERIFY(!tmpMA.isNull());
}

QTEST_MAIN(ConnectionTest)
#include "connectiontest.moc"
