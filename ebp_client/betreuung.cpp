#include "betreuung.h"
#include "ui_betreuung.h"
#include <QDebug>

Betreuung::Betreuung(SessionContext &_context, QWidget *parent) :
    QWidget(parent),
    conntext(_context),
    ui(new Ui::Betreuung)
{
    ui->setupUi(this);
    //this->ui->mitarbeiternrLabel->resize(this->ui->aufentahltsbestimmungLabel->size());
}

Betreuung::~Betreuung()
{
    delete ui;
}

void Betreuung::init()
{
    QSharedPointer< ebp::Betreuung > b = conntext.curBewohner->betreuung();

    this->ui->vornameLineEdit->setText(b->vorname());

    this->ui->nameLineEdit->setText(b->nachname());

    this->ui->eMailLineEdit->setText(b->email());

    this->ui->faxLineEdit->setText(b->fax());

    this->ui->ortLineEdit->setText(b->ort());

    this->ui->pLZLineEdit->setText(b->plz());

    this->ui->telefonLineEdit->setText(b->telefon());

    this->ui->straELineEdit->setText(b->strasse());

    //this->ui->vereinVerbandLineEdit->setText();

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
