#include "admindialog.h"
#include "ui_admindialog.h"
#include "chooseemployee.h"
#include "employeelistmodel.h"
#include "../drkv/Mitarbeiter.hxx"
#include "../drkv/Wohngruppe.hxx"
#include <QList>
#include <QMessageBox>
#include <QDebug>
AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    this->init();
}

AdminDialog::~AdminDialog()
{
    if(!this->OEWidgets.isEmpty())
    {
	foreach (OEListWidgetItem *i,this->OEWidgets)
	{
	    this->ui->O_list->removeItemWidget(i);
	    delete i;
	}
    }
    if(model!=NULL)
	delete model;
    delete ui;
}
void AdminDialog::init()
{
    this->model=NULL;
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
	QList<QSharedPointer<Wohngruppe> > w = QList<QSharedPointer<Wohngruppe> >();


	//QList<QSharedPointer<Projekt> > p = QList<QSharedPointer<Projekt> >();
	//QList<QSharedPointer<Bewohner> > b = QList<QSharedPointer<Bewohner> >();

	QSharedPointer<Mitarbeiter> ma
	(
		    new Mitarbeiter
		    (
			this->ui->loginNameLineEdit_2->text(),
			this->setBerechtigung(),
			this->ui->nameLineEdit->text(),
			this->ui->eMailLineEdit->text(),
			this->ui->telefonLineEdit->text()
		     )
	);

	if (ma->create(this->PointerToConnection,this->ui->passwortLineEdit_2->text()))
	{
	    //Alle WG die mit dem MA assoziiert werden sollen auslesen
	    for (int i = 0; i < this->ui->O_list->count(); i++)
	    {
		if(this->ui->O_list->item(i)->checkState()==Qt::Checked)
		{
		    QSharedPointer<Wohngruppe> wg = ((OEListWidgetItem *)this->ui->O_list->item(i))->getWG();
		    w.append(wg);
		    qDebug()<<wg->name();
		}
	    }
	    //WG mit MA verknüpfen
	    foreach(QSharedPointer<Wohngruppe> wg, w)
	    {
		Wohngruppe::linkMitarbeiter(wg,ma);
		Mitarbeiter::linkWohngruppe(ma,wg);
		wg->update(this->PointerToConnection);
	    }
	    ma->update(this->PointerToConnection);
	    QMessageBox::information(this,tr("Mitarbeiter erfolgreich angelegt"),tr("Mitarbeiter erfolgreich angelegt"));
	}
	else
	{
	    QMessageBox::critical(this,tr("Fehler"),tr("Mitarbeiter konnte nicht angelegt werden"));
	}
	this->on_button_MA_eingabeloeschen_clicked();
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
    this->PointerToConnection = QSharedPointer<connection>(new connection(this->ui->loginNameLineEdit->text(),"drk"));
    if (this->PointerToConnection->establish(this->ui->passwortLineEdit->text()))
    {
	this->setContent();
	this->model = new EmployeeTableModel(Mitarbeiter::loadAll(this->PointerToConnection));
    }
    else
    {
	QMessageBox::critical(this,tr("Fehlerhafter Login"),tr("Es konnte keine Veerbindung zur Datenbank hergestellt werden. Überprüfen Sie bitte ihre Logindaten"));
    }
    this->clearLogin();
    this->setOEWidget();

}
void AdminDialog::clearLogin()
{
    this->ui->loginNameLineEdit->clear();
    this->ui->passwortLineEdit->clear();
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
    this->setLogin();
}

void AdminDialog::setOEWidget()
{
    if(!this->OEWidgets.isEmpty())
    {
	foreach (OEListWidgetItem *i,this->OEWidgets)
	{
	    this->ui->O_list->removeItemWidget(i);
	    delete i;
	}
	this->OEWidgets.clear();
    }
    QList < QSharedPointer<Wohngruppe> > wgList = Wohngruppe::loadAll(this->PointerToConnection);
    this->OEWidgets.clear();

    foreach (QSharedPointer<Wohngruppe> wg, wgList )
    {
	this->OEWidgets.append(new OEListWidgetItem(wg,this->ui->O_list));
    }
    foreach (OEListWidgetItem *i,this->OEWidgets)
    {
	i->setFlags(i->flags()|Qt::ItemIsUserCheckable);
	i->setCheckState(Qt::Unchecked);
	this->ui->O_list->addItem(i);
    }
}
/*
void AdminDialog::setOEWidget()
{
    if(!this->WohngruppenItems.isEmpty())
    {
	foreach (CostumListWidget<Wohngruppe> *i,this->WohngruppenItems)
	{
	    this->ui->O_list->removeItemWidget(i);
	    delete i;
	}
	this->OEWidgets.clear();
    }
    QList < QSharedPointer<Wohngruppe> > wgList = Wohngruppe::loadAll(this->PointerToConnection);
    this->WohngruppenItems.clear();

    foreach (QSharedPointer<Wohngruppe> wg, wgList )
    {
	this->WohngruppenItems.append(new CostumListWidget<Wohngruppe>(wg,this->ui->O_list));
    }
    foreach (CostumListWidget<Wohngruppe> *i,this->WohngruppenItems)
    {
	i->setFlags(i->flags()|Qt::ItemIsUserCheckable);
	i->setCheckState(Qt::Unchecked);
	this->ui->O_list->addItem(i);
    }
}
*/
