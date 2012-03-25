#include "MitarbeiterTest.h"
/**
  * \brief Initialisiert Connection und Mitarbeiter
  */
void MitarbeiterTest::initTestCase()
{
    //testCon = NULL;
    testCon = QSharedPointer<ebp::connection> (new ebp::connection("testUser","testDB"));
    QVERIFY(!testCon.isNull());
    testCon->establish("test");
}

/**
  * \brief Testet das Erstellen eines neuen Mitarbeiters
  */
void MitarbeiterTest::testCreateNewMitarbeiter()
{
    aMitarbeiter = QSharedPointer<ebp::Mitarbeiter> ();
    QSharedPointer<ebp::Mitarbeiter> tmpMa (
		new ebp::Mitarbeiter(
		    "testLogin",
		    ebp::Mitarbeiter::AdminRecht,
		    "Hans Test",
		    "test@mail.test",
		    "0123456"
		    )
		);
    aMitarbeiter = tmpMa;
    QVERIFY(!aMitarbeiter.isNull());

    bool test = aMitarbeiter->create(testCon,"testPasswort");
    QVERIFY(test);

}
/**
  * \brief Testet das Setzen und Lesen der Datenbankfelder.
  */
void MitarbeiterTest::testSetAndGetAttributes()
{
    //login
    QString testLogin = aMitarbeiter->login();
    QCOMPARE(testLogin, QString("testLogin"));

    //name
    aMitarbeiter->name("Peter Test");
    QString testName = aMitarbeiter->name();
    QCOMPARE(testName, QString("Peter Test"));

    //Berechtigung
    aMitarbeiter->berechtigung(ebp::Mitarbeiter::WohngruppenRecht);
    ebp::Mitarbeiter::Berechtigungen recht = aMitarbeiter->berechtigung();
    QCOMPARE(recht, ebp::Mitarbeiter::WohngruppenRecht);

    //email
    aMitarbeiter->email("OTHER@TEST.MAIL");
    QString testEmail = aMitarbeiter->email();
    QCOMPARE(testEmail, QString("OTHER@TEST.MAIL"));

    //telefon
    aMitarbeiter->telefon("9876");
    QString testTelefon = aMitarbeiter->telefon();
    QCOMPARE(testTelefon, QString("9876"));
}
/**
  * \brief Testet das Updaten des Passworts des neuen Mitarbeiters
  */
void MitarbeiterTest::updatePasswort()
{
    bool test = aMitarbeiter->updatePassword(testCon,"newPasswort");
    QVERIFY(test);

}
/**
  * \brief Löscht angelegten Mitarbeiter wieder.
  */
void MitarbeiterTest::cleanupTestCase()
{
    bool test = aMitarbeiter->remove(testCon);
    QVERIFY(test);
}


