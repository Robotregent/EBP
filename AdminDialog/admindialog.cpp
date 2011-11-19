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
//Komentar
AdminDialog::~AdminDialog()
{
    if(!this->WohngruppenItems.isEmpty())
    {
	foreach (CostumListWidget<Wohngruppe> *i,this->WohngruppenItems)
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
	QList<QSharedPointer<Bewohner> > b = QList<QSharedPointer<Bewohner> >();

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
		    QSharedPointer<Wohngruppe> wg = ((CostumListWidget<Wohngruppe> *)this->ui->O_list->item(i))->getCitem();
		    w.append(wg);
		    qDebug()<<wg->name();
		}
	    }
	    //WG mit MA verknüpfen
	    foreach(QSharedPointer<Wohngruppe> wg, w)
	    {
		Wohngruppe::linkMitarbeiter(wg,ma);
		//Mitarbeiter::linkWohngruppe(ma,wg);
		wg->update(this->PointerToConnection);
	    }
	    //Bezugsbetreuuer auslesen
	    for (int i = 0; i < this->ui->B_list->count(); i++)
	    {
		if(this->ui->B_list->item(i)->checkState()==Qt::Checked)
		{
		    QSharedPointer<Bewohner> bg = ((CostumListWidget<Bewohner> *)this->ui->B_list->item(i))->getCitem();
		    b.append(bg);
		    qDebug()<<bg->name();
		}
	    }
	    //Bezugsbetreuuer verknüpfen
	    foreach(QSharedPointer<Bewohner> bg, b)
	    {
		Bewohner::linkBezugsbetreuer(bg,ma);
		//Mitarbeiter::linkBezugsbetreuer(ma,bg);

		bg->update(this->PointerToConnection);
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
    this->setMitarbiterVerwalten();
    this->setBewohnerVerwalten();

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

    for (int i = 0; i < this->ui->O_list->count();i++)
    {
	this->ui->O_list->itemAt(i,0)->setCheckState(Qt::Unchecked);
    }
    for (int i = 0; i < this->ui->B_list->count();i++)
    {
	this->ui->B_list->itemAt(i,0)->setCheckState(Qt::Unchecked);
    }
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
    if(!this->WohngruppenItems.isEmpty())
    {
	foreach (CostumListWidget<Wohngruppe> *i,this->WohngruppenItems)
	{
	    this->ui->O_list->removeItemWidget(i);
	    delete i;
	}
	this->WohngruppenItems.clear();
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

void AdminDialog::setBWidget()
{
    if(!this->BewohnerItems.isEmpty())
    {
	foreach (CostumListWidget<Bewohner> *i,this->BewohnerItems)
	{
	    this->ui->B_list->removeItemWidget(i);
	    delete i;
	}
	this->BewohnerItems.clear();
    }
    QList < QSharedPointer<Bewohner> > bList = Bewohner::loadAll(this->PointerToConnection);
    this->BewohnerItems.clear();

    foreach (QSharedPointer<Bewohner> b, bList )
    {
	this->BewohnerItems.append(new CostumListWidget<Bewohner>(b,this->ui->B_list));
    }
    foreach (CostumListWidget<Bewohner> *i,this->BewohnerItems)
    {
	i->setFlags(i->flags()|Qt::ItemIsUserCheckable);
	i->setCheckState(Qt::Unchecked);
	this->ui->B_list->addItem(i);
    }
}


void AdminDialog::on_passwortLineEdit_returnPressed()
{
    this->ui->ButtonLogin->setFocus();
}
void AdminDialog::setMitarbiterVerwalten()
{
    this->setOEWidget();
    this->setBWidget();
}
void AdminDialog::setBewohnerVerwalten()
{
    if(!this->WohngruppeTreeItems.isEmpty())
    {
	foreach (CostumTreeWidget<Wohngruppe> *i,this->WohngruppeTreeItems)
	{
	    this->ui->WohngruppeTree->removeItemWidget(i,0);
	    delete i;
	}
	this->WohngruppeTreeItems.clear();
    }
    QList < QSharedPointer<Wohngruppe> > bList = Wohngruppe::loadAll(this->PointerToConnection);
    this->WohngruppeTreeItems.clear();

    foreach (QSharedPointer<Wohngruppe> b, bList )
    {
	this->WohngruppeTreeItems.append(new CostumTreeWidget<Wohngruppe>(b,this->ui->WohngruppeTree));
    }
    foreach (CostumTreeWidget<Wohngruppe> *i,this->WohngruppeTreeItems)
    {
	/*i->setFlags(i->flags()|Qt::ItemIsUserCheckable);
	i->setCheckState(0,Qt::Unchecked);*/
	this->ui->WohngruppeTree->addTopLevelItem(i);
    }

}

void AdminDialog::on_button_O_speichern_clicked()
{
    switch (this->ui->box_O_kategorie->currentIndex())
    {
    case 0:
	QSharedPointer<Wohngruppe> tmpwg
	(
		new Wohngruppe
		(
			this->ui->lineEdit_O_name->text()
		)
	);
	if (tmpwg->create( this->PointerToConnection ))
	{
	    CostumListWidget<Wohngruppe> *newWG1 =new CostumListWidget<Wohngruppe>(tmpwg,this->ui->O_list);
	    newWG1->setFlags(newWG1->flags()|Qt::ItemIsUserCheckable);
	    newWG1->setCheckState(Qt::Unchecked);
	    this->WohngruppenItems.append(newWG1);
	    this->ui->O_list->addItem(newWG1);

	    CostumTreeWidget<Wohngruppe> *newWG2 =new CostumTreeWidget<Wohngruppe>(tmpwg,this->ui->WohngruppeTree);
	    this->WohngruppeTreeItems.append(newWG2);
	    this->ui->WohngruppeTree->addTopLevelItem(newWG2);
	    qDebug()<<"Erfolg!";
	}
	else
	{
	    qDebug()<<"Fehler!";
	}
	break;
    }
}

void AdminDialog::on_button_B_speichern_clicked()
{
    QSharedPointer<Bewohner> tmpBew
    (
		new Bewohner (this->ui->Bewohnernummer->text().toULong(),this->ui->Bewohnernummer->text(), QDate(), " ", " ", " ")
    );
    if (tmpBew->create( this->PointerToConnection ))
    {
	CostumListWidget<Bewohner> *newBew=new CostumListWidget<Bewohner>(tmpBew,this->ui->B_list);
	this->BewohnerItems.append(newBew);
	newBew->setFlags(newBew->flags()|Qt::ItemIsUserCheckable);
	newBew->setCheckState(Qt::Unchecked);
	this->ui->B_list->addItem(newBew);
	qDebug()<<"Erfolg!";
    }
    else
    {
	qDebug()<<"Fehler!";
    }
    QSharedPointer<Wohngruppe> tmpWg = this->WohngruppeTreeItems.at(this->ui->WohngruppeTree->currentIndex().row())->getCitem();
    tmpBew->linkWohngruppe(tmpBew,tmpWg);
    tmpBew->update(this->PointerToConnection);
}
