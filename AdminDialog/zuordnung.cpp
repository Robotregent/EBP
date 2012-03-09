#include "zuordnung.h"
#include "ui_zuordnung.h"
#include "admindialog.h"
//#include "QDebug"
#include <QMessageBox>
Zuordnung::Zuordnung(EmployeeTableModel *_model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zuordnung)
{
    ui->setupUi(this);
    if (parent != NULL)
	this->connectionPointer = ((AdminDialog *) parent)->dbPointer();

    if (_model != NULL)
    {
	this->model = _model;
	this->ui->MitarbeiterView->setModel(_model);

	//this->on_MitarbeiterView_activated(model->index(0,0));
    }


}

Zuordnung::~Zuordnung()
{
    delete ui;
}
void Zuordnung::on_MitarbeiterView_clicked(const QModelIndex &index)
{
    this->setList(index);
}

void Zuordnung::on_buttonBox_accepted()
{
    this->close();
}

/////////////////////Wohngruppe///////////////////////////////

WohngruppenZuordnung::WohngruppenZuordnung(EmployeeTableModel *_model, QWidget *parent) :
    Zuordnung(_model,parent)
{

    this->alleWohngruppen = ebp::Wohngruppe::loadAll(connectionPointer);
    CostumListWidget<ebp::Wohngruppe> *clw;
    foreach (QSharedPointer<ebp::Wohngruppe> wg , this->alleWohngruppen)
    {
	clw = new CostumListWidget<ebp::Wohngruppe>(wg, this->ui->ZuordnungsListe);
	clw->setFlags(clw->flags()|Qt::ItemIsUserCheckable);
	clw->setCheckState(Qt::Unchecked);
    }

}
/**
  *\brief läd die Liste aller Wohngruppen, die momentan dem ausgewählten Mitarbeiter zugeordnet sind
  */
bool WohngruppenZuordnung::setList(const QModelIndex &index)
{
    QSharedPointer<ebp::Mitarbeiter> ma = this->model->getMitarbeiter(index.row());
    QList < QSharedPointer<ebp::Wohngruppe> > zugeordneteWohngruppen = ma->loadWohngruppen(connectionPointer);
    CostumListWidget<ebp::Wohngruppe> *clw;

    for (int k = 0; k< alleWohngruppen.count();k++)
    {
	clw = (CostumListWidget<ebp::Wohngruppe> *) this->ui->ZuordnungsListe->item(k);
	clw->setCheckState(Qt::Unchecked);
	for (int i = 0; i< zugeordneteWohngruppen.count(); i++)
	{
	    if(clw->getCitem()->name()==zugeordneteWohngruppen.at(i)->name())
	    {
		clw->setCheckState(Qt::Checked);
	    }

	}

    }
    return true;

}

void WohngruppenZuordnung::on_buttonBox_accepted()
{
    if (this->saveMapping())
	this->close();
    else
	QMessageBox::critical(this,"Fehlschlag", "Speichern der neuen Zuordnung hat leider nicht geklappt");
}
/**
  *\brief Zuordnung abspeichern
  */
bool WohngruppenZuordnung::saveMapping()
{
    bool res = true;
    QSharedPointer<ebp::Mitarbeiter> ma = this->model->getMitarbeiter(this->ui->MitarbeiterView->currentIndex().row());
    //Bisherzugeordnete Gruppen
    QList < QSharedPointer<ebp::Wohngruppe> > zugeordneteWohngruppen = ma->loadWohngruppen(connectionPointer);
    CostumListWidget<ebp::Wohngruppe> *clw;
    //Alle Gruppen durchlaufen
    for (int k = 0; k< alleWohngruppen.count();k++)
    {
	bool hadMatch = false;
	clw = (CostumListWidget<ebp::Wohngruppe> *) this->ui->ZuordnungsListe->item(k);
	//für jede Wohngruppe prüfen, ob sie schon gemappt ist
	for (int i = 0; i< zugeordneteWohngruppen.count(); i++)
	{
	    //Ist diese Gruppe gemappt?
	    if(clw->getCitem()->name()==zugeordneteWohngruppen.at(i)->name())
	    {
		//Wenn sie abgehackt wurde link löschen
		if (clw->checkState()==Qt::Unchecked)
		{
		    QSharedPointer<ebp::Wohngruppe> wg = clw->getCitem();
		    ebp::Wohngruppe::unlinkMitarbeiter(wg,ma);
		    if(!clw->getCitem()->update(this->connectionPointer))
			res=false;
		}
		hadMatch = true;
	    }
	}
	if(!hadMatch)
	{
	    //War Gruppe bisher nicht gemappt, ist jetzt aber gemappt: link herstellen
	    if(clw->checkState()==Qt::Checked)
	    {
		QSharedPointer<ebp::Wohngruppe> wg = clw->getCitem();
		ebp::Wohngruppe::linkMitarbeiter(wg,ma);
		if(!clw->getCitem()->update(this->connectionPointer))
		    res=false;
	    }

	}
    }
    return res;
}

////////Bezugsbetreuung///////////////////////////////

BezugsbetreuungZuordnung::BezugsbetreuungZuordnung(EmployeeTableModel *_model, QWidget *parent) :
    Zuordnung(_model,parent)
{

    this->alleBezugsbetreuungen = ebp::Bewohner::loadAll(connectionPointer);
    CostumListWidget<ebp::Bewohner> *clw;
    foreach (QSharedPointer<ebp::Bewohner> bw , this->alleBezugsbetreuungen)
    {
	clw = new CostumListWidget<ebp::Bewohner>(bw, this->ui->ZuordnungsListe);
	clw->setFlags(clw->flags()|Qt::ItemIsUserCheckable);
	clw->setCheckState(Qt::Unchecked);
    }

}
/**
  *\brief läd die Liste aller Bezugsbetreuung, die momentan dem ausgewählten Mitarbeiter zugeordnet sind
  */
bool BezugsbetreuungZuordnung::setList(const QModelIndex &index)
{
    QSharedPointer<ebp::Mitarbeiter> ma = this->model->getMitarbeiter(index.row());
    QList < QSharedPointer<ebp::Bewohner> > zugeordneteBezugsbetreuung = ma->loadBezugsbetreuer(connectionPointer);
    CostumListWidget<ebp::Bewohner> *clw;

    for (int k = 0; k< alleBezugsbetreuungen.count();k++)
    {
	clw = (CostumListWidget<ebp::Bewohner> *) this->ui->ZuordnungsListe->item(k);
	clw->setCheckState(Qt::Unchecked);
	for (int i = 0; i< zugeordneteBezugsbetreuung.count(); i++)
	{
	    if(clw->getCitem()->nummer()==zugeordneteBezugsbetreuung.at(i)->nummer())
	    {
		clw->setCheckState(Qt::Checked);
	    }

	}

    }
    return true;

}

void BezugsbetreuungZuordnung::on_buttonBox_accepted()
{
    if (this->saveMapping())
	this->close();
    else
	QMessageBox::critical(this,"Fehlschlag", "Speichern der neuen Zuordnung hat leider nicht geklappt");
}
/**
  *\brief Zuordnung abspeichern
  */
bool BezugsbetreuungZuordnung::saveMapping()
{
    bool res = true;
    QSharedPointer<ebp::Mitarbeiter> ma = this->model->getMitarbeiter(this->ui->MitarbeiterView->currentIndex().row());
    //Bisherzugeordnete Gruppen
    QList < QSharedPointer<ebp::Bewohner> > zugeordneteBezugsbetreuung = ma->loadBezugsbetreuer(connectionPointer);
    CostumListWidget<ebp::Bewohner> *clw;
    //Alle Gruppen durchlaufen
    for (int k = 0; k< alleBezugsbetreuungen.count();k++)
    {
	bool hadMatch = false;
	clw = (CostumListWidget<ebp::Bewohner> *) this->ui->ZuordnungsListe->item(k);

	//für jede Bewohner prüfen, ob sie schon gemappt ist
	for (int i = 0; i< zugeordneteBezugsbetreuung.count(); i++)
	{
	    //Ist diese Gruppe gemappt?
	    if(clw->getCitem()->nummer()==zugeordneteBezugsbetreuung.at(i)->nummer())
	    {
		//Wenn sie abgehackt wurde link löschen
		if (clw->checkState()==Qt::Unchecked)
		{
		    QSharedPointer<ebp::Bewohner> bw = clw->getCitem();
		    ebp::Bewohner::unlinkBezugsbetreuer(bw,ma);
		    if(!clw->getCitem()->update(this->connectionPointer))
			res=false;
		}
		hadMatch = true;
	    }
	}
	if(!hadMatch)
	{
	    //War Gruppe bisher nicht gemappt, ist jetzt aber gemappt: link herstellen
	    if(clw->checkState()==Qt::Checked)
	    {
		QSharedPointer<ebp::Bewohner> bw = clw->getCitem();
		ebp::Bewohner::linkBezugsbetreuer(bw,ma);
		if(!clw->getCitem()->update(this->connectionPointer))
		    res=false;
	    }

	}
    }
    return res;
}
