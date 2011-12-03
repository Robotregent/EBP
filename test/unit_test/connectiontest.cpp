#include <QObject>
#include <QtTest/QtTest>
#include "../../EBPdb/connection.cxx"

//Declaration
class ConnectionTest : public QObject
{
    Q_OBJECT
    ebp::connection *testCon;
private slots:
    void initTestCase();
    void establishCon();
    void createConnection();
    void cleanupTestCase();


};

//Implementation
void ConnectionTest::initTestCase()
{
    this->testCon= new ebp::connection("testUser","testDB");
    //this->testCon->establish("testPasswort");
}
void ConnectionTest::establishCon()
{
    QVERIFY(this->testCon->establish("testPasswort")==true);
    QVERIFY(this->testCon->establish("")!=true);
    QVERIFY(this->testCon->establish("falschesPasswort")!=true);


}

void ConnectionTest::createConnection()
{

}

void ConnectionTest::cleanupTestCase()
{
    delete this->testCon;
}

QTEST_MAIN(ConnectionTest)
#include "connectiontest.moc"
