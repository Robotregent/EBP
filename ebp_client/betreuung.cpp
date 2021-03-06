#include "betreuung.h"
#include "ui_betreuung.h"
#include <QDebug>
#include <QMessageBox>

Betreuung::Betreuung(SessionContext &_context, QWidget *parent) :
    QWidget(parent),   
    ui(new Ui::Betreuung),
    conntext(_context)
{
    ui->setupUi(this);
    init();
}

Betreuung::~Betreuung()
{
    delete ui;
}

void Betreuung::init()
{
    if ( !conntext.curBewohner.isNull())
    {

	    QSharedPointer< ebp::Betreuung > b = conntext.curBewohner->betreuung();

	    if(!b.isNull())
	    {
		this->ui->vornameLineEdit->setText(b->vorname());

		this->ui->nameLineEdit->setText(b->nachname());

		this->ui->eMailLineEdit->setText(b->email());

		this->ui->faxLineEdit->setText(b->fax());

		this->ui->ortLineEdit->setText(b->ort());

		this->ui->pLZLineEdit->setText(b->plz());

		this->ui->telefonLineEdit->setText(b->telefon());

		this->ui->straELineEdit->setText(b->strasse());

		this->ui->vereinVerbandLineEdit->setText(b->verein());

		if(b->aufenthaltsbestimmung())
		    this->ui->aufentahltsbestimmungComboBox->setCurrentIndex(1);
		else
		    this->ui->aufentahltsbestimmungComboBox->setCurrentIndex(0);

		if(b->gesundheitsfuersorge())
		    this->ui->gesundheitsfRsorgeComboBox->setCurrentIndex(1);
		else
		    this->ui->gesundheitsfRsorgeComboBox->setCurrentIndex(0);

		if(b->vermoegensfuersorge())
		    this->ui->vermGensfRsorgeComboBox->setCurrentIndex(1);
		else
		    this->ui->vermGensfRsorgeComboBox->setCurrentIndex(0);
	    }

    }
    else
	qDebug()<<"Kein Bewohner";
}
/**
  * \brief Speichert Inhalt von Betreuung
  */
bool Betreuung::saveContent()
{
    bool result = false;
    if ( !conntext.curBewohner.isNull())
    {
        QSharedPointer< ebp::Betreuung > b = conntext.curBewohner->betreuung();

        if(!b.isNull())
        {
            b->vorname(this->ui->vornameLineEdit->text());

            b->nachname(this->ui->nameLineEdit->text());

            b->email(this->ui->eMailLineEdit->text());

            b->fax(this->ui->faxLineEdit->text());

            b->ort(this->ui->ortLineEdit->text());

            b->plz(this->ui->pLZLineEdit->text());

            b->telefon(this->ui->telefonLineEdit->text());

            b->strasse(this->ui->straELineEdit->text());

            b->verein(this->ui->vereinVerbandLineEdit->text());

            if(this->ui->aufentahltsbestimmungComboBox->currentIndex()==0)
                b->aufenthaltsbestimmung(false);
            else
                b->aufenthaltsbestimmung(true);

            if(this->ui->gesundheitsfRsorgeComboBox->currentIndex()==0)
                b->gesundheitsfuersorge(false);
            else
                b->gesundheitsfuersorge(true);

            if(this->ui->vermGensfRsorgeComboBox->currentIndex()==0)
                b->vermoegensfuersorge(false);
            else
                b->vermoegensfuersorge(true);

            if(b->update(conntext.curConnection))
            {
                result = true;
                conntext.curBewohner->reload(conntext.curConnection);
            }
            else
            {
                result = false;
            }
        }
    }
    return result;
}
bool Betreuung::hasPendingChanges()
{
    bool result = pendingChanges;

    if(!result)
    {
        if(this->ui->vornameLineEdit->isUndoAvailable())
            result=true;

        if(this->ui->nameLineEdit->isUndoAvailable())
            result=true;

        if(this->ui->eMailLineEdit->isUndoAvailable())
            result=true;

        if(this->ui->faxLineEdit->isUndoAvailable())
            result=true;

        if(this->ui->ortLineEdit->isUndoAvailable())
            result=true;

        if(this->ui->pLZLineEdit->isUndoAvailable())
            result=true;

        if(this->ui->telefonLineEdit->isUndoAvailable())
            result=true;

        if(this->ui->straELineEdit->isUndoAvailable())
            result=true;

        if(this->ui->vereinVerbandLineEdit->isUndoAvailable())
            result=true;
    }
    return result;
}

void Betreuung::on_gesundheitsfRsorgeComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges = true;
}

void Betreuung::on_vermGensfRsorgeComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges = true;
}

void Betreuung::on_aufentahltsbestimmungComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges = true;
}
