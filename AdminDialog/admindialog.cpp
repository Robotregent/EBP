#include "admindialog.h"
#include "ui_admindialog.h"
#include "chooseemployee.h"
#include "employeelistmodel.h"
#include "costumdeletedialog.h"
#include "zuordnung.h"
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Wohngruppe.hxx>
#include <EBPdb/Wohnheim.hxx>
#include <QList>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <EBPdb/Dokumentation.hxx>
#include <EBPdb/Verfuegung.hxx>
#include <EBPdb/Betreuung.hxx>

using namespace ebp;

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    this->init();
}

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
/**
  * \brief Dialog initialisieren
  */
void AdminDialog::init()
{
    this->model=NULL;
    this->ui->passwortLineEdit->setEchoMode(QLineEdit::Password);
    this->ui->passwortWiederholenLineEdit->setEchoMode(QLineEdit::Password);
    this->ui->passwortLineEdit_2->setEchoMode(QLineEdit::Password);

    QSettings settings("AdminDialog.ini", QSettings::IniFormat);
    this->dbName = settings.value("db",QVariant("ebp")).toString();
    this->dbHost = settings.value("host",QVariant("localhost")).toString();
    this->dbPort = settings.value("port",QVariant(3306)).toUInt();


    this->setLogin();

}
/**
  * \brief Startet den Löschlialog für die Mitarbeiter
  */
void AdminDialog::on_button_MA_suchen_clicked()
{
    ChooseEmployee *e=new ChooseEmployee(this->model,this);
    e->setModal(true);
    e->setVisible(true);
}
/**
  * \brief Mitarbeiter mit den angegebenen Verknüpfungen speichern und neu erstellen
  */
void AdminDialog::on_button_MA_speichern_clicked()
{
    if(this->isPasswordValid())
    {
        QList<QSharedPointer<Wohngruppe> > w = QList<QSharedPointer<Wohngruppe> >();
        QList<QSharedPointer<Bewohner> > b = QList<QSharedPointer<Bewohner> >();

        //Bei leeren Feldern ein leerzeichen mitgeben
        QSharedPointer<Mitarbeiter> ma
        (
                new Mitarbeiter
                (
                this->ui->loginNameLineEdit_2->text().isEmpty() ? " " : this->ui->loginNameLineEdit_2->text(),
                this->setBerechtigung(),
                this->ui->nameLineEdit->text().isEmpty() ?  " " : this->ui->nameLineEdit->text()
                 )
        );
        ma->email(this->ui->eMailLineEdit->text().isEmpty() ?  " " : this->ui->eMailLineEdit->text());
        ma->email(this->ui->telefonLineEdit->text().isEmpty() ? " " : this->ui->telefonLineEdit->text());

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
                bg->update(this->PointerToConnection);
            }
            if(ma->update(this->PointerToConnection))
                QMessageBox::information(this,tr("Mitarbeiter erfolgreich angelegt"),tr("Mitarbeiter erfolgreich angelegt"));
            else
                QMessageBox::critical(this,tr("Fehler"),tr("Mitarbeiter konnte nicht angelegt werden"));
            this->model->addMitarbeiter(ma);
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
/**
  * \brief Loggin
  */
void AdminDialog::on_ButtonLogin_clicked()
{
    this->PointerToConnection = QSharedPointer<connection>(new connection(this->ui->loginNameLineEdit->text(),this->dbName,this->dbHost,this->dbPort));
    if (this->PointerToConnection->establish(this->ui->passwortLineEdit->text()))
    {
        this->setContent();
        this->model = new EmployeeTableModel(Mitarbeiter::loadAll(this->PointerToConnection));
        this->setMitarbiterVerwalten();
        this->setBewohnerVerwalten();
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
/**
  * \brief Passwort überprüfen
  */
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
/**
  * \brief Mitarbeiter löschen
  */
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
/**
  * \brief Setzt Berechtigung für neuen Mitarbeiter
  */
Mitarbeiter::Berechtigungen AdminDialog::setBerechtigung()
{
    Mitarbeiter::Berechtigungen res = Mitarbeiter::WohngruppenRecht;
    switch (this->ui->BerechtigungenBox->currentIndex())
    {
    case 0:
        res = Mitarbeiter::WohngruppenRecht;
        break;
    case 1:
        res = Mitarbeiter::AdminRecht;
        break;
    default:
        break;
    }
    return res;
}
/**
  * \brief Auslogen
  */
void AdminDialog::on_ButtonAusloggen_clicked()
{
    this->setLogin();
}
/**
  * \brief Widget Wohngruppen initialisieren
  */
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
/**
  * \brief Widget Bewohner initialisieren
  */
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
    QList < QSharedPointer<Bewohner> > bList = ebp::Bewohner::loadAll(this->PointerToConnection);
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
/**
  * \brief Daten für Widget Bewohner verwalten laden
  */
void AdminDialog::setBewohnerVerwalten()
{
    if(!this->WohngruppeTreeItems.isEmpty())
    {
	foreach (CostumListWidget<Wohngruppe> *i,this->WohngruppeTreeItems)
	{
	    this->ui->WohngruppeTree->removeItemWidget(i);
	    delete i;
	}
	this->WohngruppeTreeItems.clear();
    }
    QList < QSharedPointer<Wohngruppe> > bList = Wohngruppe::loadAll(this->PointerToConnection);
    this->WohngruppeTreeItems.clear();

    foreach (QSharedPointer<Wohngruppe> b, bList )
    {
        this->WohngruppeTreeItems.append(new CostumListWidget<Wohngruppe>(b,this->ui->WohngruppeTree));
    }
    foreach (CostumListWidget<Wohngruppe> *i,this->WohngruppeTreeItems)
    {
        this->ui->WohngruppeTree->addItem(i);
    }

}

void AdminDialog::on_button_O_speichern_clicked()
{ 
	this->createWohngruppe();
}
/**
  * \brief Neue Wohngruppe anlegen
  */
void AdminDialog::createWohngruppe()
{
    if (this->ui->lineEdit_O->text().isEmpty()||this->ui->lineEdit_O->text().isNull())
	return;
    QSharedPointer<Wohngruppe> tmpwg
    (
	    new Wohngruppe
	    (
		    this->ui->lineEdit_O->text()
	    )
    );
    if (tmpwg->create( this->PointerToConnection ))
    {
        CostumListWidget<Wohngruppe> *newWG1 =new CostumListWidget<Wohngruppe>(tmpwg,this->ui->O_list);
        newWG1->setFlags(newWG1->flags()|Qt::ItemIsUserCheckable);
        newWG1->setCheckState(Qt::Unchecked);
        this->WohngruppenItems.append(newWG1);
        this->ui->O_list->addItem(newWG1);

        CostumListWidget<Wohngruppe> *newWG2 =new CostumListWidget<Wohngruppe>(tmpwg,this->ui->WohngruppeTree);

        this->WohngruppeTreeItems.append(newWG2);
        this->ui->WohngruppeTree->addItem(newWG2);

        //qDebug()<<"Erfolg!";
        QMessageBox::about(this, tr("Erfolg"),tr("Wohngruppe wurde erfolgreich angelegt"));
        this->ui->lineEdit_O->setText("");
    }
    else
    {
        QMessageBox::critical(this, tr("Warnung"),tr("Wohngruppe konnte nicht angeleg"));
    }
}

/**
* \brief Neuen Bewohner anlegen
**/
void AdminDialog::on_button_B_speichern_clicked()
{
    //Werte testen
    if (this->ui->Bewohnernummer->text().isEmpty()||this->ui->Bewohnernummer->text().isNull())
        return;
    if (this->ui->vornameLineEdit->text().isEmpty()||this->ui->vornameLineEdit->text().isNull())
        return;
    if (this->ui->nachnameLineEdit->text().isEmpty()||this->ui->nachnameLineEdit->text().isNull())
        return;
    if (!this->ui->WohngruppeTree->currentIndex().isValid())
        return;

    //
    QSharedPointer<Bewohner> tmpBew
    (
        new Bewohner (this->ui->Bewohnernummer->value())
    );
    tmpBew->vorname(this->ui->vornameLineEdit->text());
    tmpBew->nachname(this->ui->nachnameLineEdit->text());
    if (tmpBew->create( this->PointerToConnection ))
    {
        CostumListWidget<Bewohner> *newBew=new CostumListWidget<Bewohner>(tmpBew,this->ui->B_list);
        if (newBew!= NULL)
        {
            this->BewohnerItems.append(newBew);
            newBew->setFlags(newBew->flags()|Qt::ItemIsUserCheckable);
            newBew->setCheckState(Qt::Unchecked);
            this->ui->B_list->addItem(newBew);
        }

        QSharedPointer<Wohngruppe> tmpWg = this->WohngruppeTreeItems.at(this->ui->WohngruppeTree->currentIndex().row())->getCitem();
        tmpBew->linkWohngruppe(tmpBew,tmpWg);

        //Betreuungsplanung anlegen
        ebp::Dokumentation::Typ typs[6] = {ebp::Dokumentation::einkaufen, ebp::Dokumentation::waeschepflege, ebp::Dokumentation::koerperpflege,
                           ebp::Dokumentation::aufstehenUndZuBettgehen, ebp::Dokumentation::partnerschaften, ebp::Dokumentation::freundschaften };

        QSharedPointer < ebp::Dokumentation > tmpDoku[6];
        for (int i=0; i<6; i++)
        {
            tmpDoku[i] = QSharedPointer < ebp::Dokumentation >(new ebp::Dokumentation(typs[i],ebp::Dokumentation::bekommeKeineHilfe));
            tmpDoku[i]->create(PointerToConnection);
            ebp::Dokumentation::linkBewohner(tmpDoku[i],tmpBew);
            tmpDoku[i]->update(PointerToConnection);
        }

        QSharedPointer < ebp::Betreuung > betreuung = QSharedPointer < ebp::Betreuung > (new ebp::Betreuung());
        if (!betreuung.isNull())
        {
            betreuung->create(PointerToConnection);
            ebp::Betreuung::linkBewohner(betreuung,tmpBew);
            betreuung->update(PointerToConnection);
        }

        tmpBew->seit(QDate::currentDate());

        if(tmpBew->update(PointerToConnection))
            QMessageBox::information(this,tr("Erfolg"),tr("Bewohner erfolgreich angelegt"));
        else
            QMessageBox::critical(this,tr("Fehler"),tr("Bewohner konnte nicht angelegt werden"));
        //Masken leeren
        this->ui->vornameLineEdit->clear();
        this->ui->nachnameLineEdit->clear();

        this->ui->Bewohnernummer->cleanText();
        this->ui->Bewohnernummer->clear();
    }
    else
    {
        QMessageBox::critical(this,tr("Fehler"),tr("Bewohner konnte nicht angelegt werden"));
    }

}

void AdminDialog::on_button_O_eingabeloeschen_clicked()
{
    this->ui->lineEdit_O->text().clear();
}

/**
  * \brief Wohngruppelöschen Dialog anzeigen
  */
void AdminDialog::on_button_O_waehlen_clicked()
{
    WohngruppenDeleteDialog *wgdd = new WohngruppenDeleteDialog(this->WohngruppenItems,this);
    wgdd->show();
}
/**
  * \brief Wohngruppe löschen
  */
bool AdminDialog::deleteWohngruppe(int index)
{
    bool ret = false;
    QSharedPointer<Wohngruppe> tmpWg= this->WohngruppenItems.at(index)->getCitem();
    if(tmpWg->remove(this->PointerToConnection))
    {
        //Aus der aktuellen Ansicht löschen
        QMessageBox::about(this,"Erfolg",this->WohngruppenItems.at(index)->text() + tr(" erfolgreich gelöscht!"));
        delete this->ui->O_list->takeItem(index);
        this->WohngruppenItems.removeAt(index);

        delete this->ui->WohngruppeTree->takeItem(index);
        this->WohngruppeTreeItems.removeAt(index);
        ret = true;
    }
    else
    {
        QMessageBox::critical(this,tr("Fehlschlag"),tr("Löschen fehlgeschlagen"));
    }
    return ret;
}
/**
  * \brief Bewohner löschen
  */
bool AdminDialog::deleteBewohner(int index)
{
    bool ret = false;

    QSharedPointer<ebp::Bewohner> tmpBW= this->BewohnerItems.at(index)->getCitem();
    if(tmpBW->remove(this->PointerToConnection))
    {
        //Aus der aktuellen Ansicht löschen
        QMessageBox::about(this,tr("Erfolg"),this->BewohnerItems.at(index)->text() + tr(" erfolgreich gelöscht!"));
        delete this->ui->B_list->takeItem(index);
        this->BewohnerItems.removeAt(index);
        ret = true;
    }
    else
    {
        QMessageBox::critical(this,tr("Fehlschlag"),tr("Löschen fehlgeschlagen"));
    }
    return ret;
}
/**
  * \brief Bewohnerlöschen Dialog anzeigen
  */
void AdminDialog::on_button_B_waelen_clicked()
{
    BewohnerDeleteDialog *_bewohnerDeleteDialog = new BewohnerDeleteDialog(this->BewohnerItems,this);
    _bewohnerDeleteDialog->show();
}
/**
  * \brief Mitarbeiter mit Wohngruppen verknüpfen
  */
void AdminDialog::on_pushButton_2_clicked()
{
    WohngruppenZuordnung *WohngruppenZuordnungsDialog = new WohngruppenZuordnung(this->model,this);
    WohngruppenZuordnungsDialog->show();
}
/**
  * \brief Mitarbeiter mit Bewohner verknüpfen (Bezugsbetreuung)
  */
void AdminDialog::on_pushButton_clicked()
{
    BezugsbetreuungZuordnung *bezugsbetreuungsZuordnungsDialog = new BezugsbetreuungZuordnung(this->model,this);
    bezugsbetreuungsZuordnungsDialog->show();
}
