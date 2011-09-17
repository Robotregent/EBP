#include "admindialog.h"
#include "ui_admindialog.h"
#include "chooseemployee.h"
#include "employeelistmodel.h"
#include "../drkv/Mitarbeiter.hxx"
#include <QList>
#include <QMessageBox>
AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    this->init();
}

AdminDialog::~AdminDialog()
{
    delete ui;
}
void AdminDialog::init()
{
    this->con = NULL;
    this->ui->passwortLineEdit->setEchoMode(QLineEdit::Password);
    this->ui->passwortWiederholenLineEdit->setEchoMode(QLineEdit::Password);
    this->ui->passwortLineEdit_2->setEchoMode(QLineEdit::Password);
    this->ui->berechtigungComboBox->addItems(QStringList()
					     <<tr("WohngruppenRecht")
					     <<tr("WohnheimRecht")
					     <<tr("WohnverbundRecht")
					     <<tr("AdminRecht"));

    this->setLogin();

}

void AdminDialog::on_button_MA_suchen_clicked()
{
    ChooseEmployee *e=new ChooseEmployee(this->model,this);
    e->setModal(true);
    e->setVisible(true);
}

void AdminDialog::on_button_MA_speichern_clicked()
{
    if(this->isPasswordValid())
    {
	QList<QLazyWeakPointer<Wohngruppe> > w = QList<QLazyWeakPointer<Wohngruppe> >();
	QList<QLazyWeakPointer<Projekt> > p = QList<QLazyWeakPointer<Projekt> >();
	QList<QLazyWeakPointer<Bewohner> > b = QList<QLazyWeakPointer<Bewohner> >();

	Mitarbeiter ma(this->ui->loginNameLineEdit_2->text(),
		       this->setBerechtigung(),
		       this->ui->nameLineEdit->text(),
		       this->ui->eMailLineEdit->text(),
		       this->ui->telefonLineEdit->text(),
		       w,
		       p,
		       b);

	if (ma.create(this->PointerToConnection,this->ui->passwortLineEdit_2->text()))
	{
	    QMessageBox::information(this,tr("Mitarbeiter erfolgreich angelegt"),tr("Mitarbeiter erfolgreich angelegt"));
	}
	else
	{
	    QMessageBox::critical(this,tr("Fehler"),tr("Mitarbeiter konnte nicht angelegt werden"));
	}
	this->on_button_MA_eingabeloeschen_clicked();
	//QMessageBox::information(this,tr("Mitarbeiter erfolgreich angelegt"),tr("Mitarbeiter erfolgreich angelegt"));
    }
    else
    {
	this->ui->passwortLineEdit_2->clear();
	this->ui->passwortWiederholenLineEdit->clear();
    }
}

void AdminDialog::on_button_abbrechen_clicked()
{
    this->close();
}

void AdminDialog::setLogin()
{
    this->ui->tabWidget->setCurrentWidget(this->ui->tab_login);
    this->ui->tab_login->setEnabled(true);
    this->ui->tab_Bewohner->setEnabled(false);
    this->ui->tab_Mitarbeiter->setEnabled(false);
    this->ui->tab_Organisationseinheiten->setEnabled(false);

}
void AdminDialog::setContent()
{
    this->ui->tabWidget->setCurrentWidget(this->ui->tab_Mitarbeiter);
    this->ui->tab_login->setEnabled(false);
    this->ui->tab_Bewohner->setEnabled(true);
    this->ui->tab_Mitarbeiter->setEnabled(true);
    this->ui->tab_Organisationseinheiten->setEnabled(true);
}

void AdminDialog::on_ButtonLogin_clicked()
{
    this->con=new connection(this->ui->loginNameLineEdit->text(),"drk");
    if (this->con->establish(this->ui->passwortLineEdit->text()))
    {
	this->setContent();

	this->PointerToConnection = QSharedPointer<connection>(this->con);
	this->model = new EmployeeTableModel(Mitarbeiter::getAll(this->PointerToConnection));
    }
    else
    {
	QMessageBox::critical(this,tr("Fehlerhafter Login"),tr("Es konnte keine Veerbindung zur Datenbank hergestellt werden. Überprüfen Sie bitte ihre Logindaten"));
    }
    this->clearLogin();
}
void AdminDialog::clearLogin()
{
    this->ui->loginNameLineEdit->clear();
    this->ui->passwortLineEdit->clear();
}
void AdminDialog::removeTabWidgets()
{
    foreach (const int &toRemove , TabPages)
    {
	this->ui->tabWidget->removeTab(toRemove);
    }
    TabPages.clear();
}
 bool AdminDialog::isPasswordValid()
 {
     bool res = true;
     QString p1, p2;
     p1 = this->ui->passwortLineEdit_2->text();
     p2 = this->ui->passwortWiederholenLineEdit->text();
     if(p1.isEmpty() || p2.isEmpty()||(p1 == " ")||(p2 == " "))
     {
	 QMessageBox::critical(this,tr("Leeres Passwort"),tr("Bitte Passwort eingeben"));
	 res = false;
     }

     else if (p1!=p2)
     {
	 QMessageBox::critical(this,tr("Passwörter stimmen nicht überein"),tr("Bitte zweimal das gleiche Passwort eingeben"));
	 res = false;
     }
     return res;
 }

void AdminDialog::on_button_MA_eingabeloeschen_clicked()
{
    this->ui->loginNameLineEdit_2->clear();
    this->ui->passwortLineEdit_2->clear();
    this->ui->passwortWiederholenLineEdit->clear();
    this->ui->nameLineEdit->clear();
    this->ui->telefonLineEdit->clear();
    this->ui->eMailLineEdit->clear();
}
Mitarbeiter::Berechtigungen AdminDialog::setBerechtigung()
{
    Mitarbeiter::Berechtigungen res = Mitarbeiter::WohngruppenRecht;
    switch (this->ui->berechtigungComboBox->currentIndex())
    {
    case 0:
	res = Mitarbeiter::WohngruppenRecht;
	break;
    case 1:
	res = Mitarbeiter::WohnheimRecht;
	break;
    case 2:
	res = Mitarbeiter::WohnverbundRecht;
	break;
    case 3:
	res = Mitarbeiter::AdminRecht;
	break;
    default:
	break;
    }

    return res;
}

void AdminDialog::on_ButtonAusloggen_clicked()
{
    if (this->con!=NULL)
	delete this->con;
    this->setLogin();
}
