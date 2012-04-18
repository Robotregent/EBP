#include "leistungstraegerbox.h"
#include "ui_leistungstraegerbox.h"
#include <QString>
#include <QSharedPointer>
#include <EBPdb/Leistungstraeger.hxx>
#include <EBPdb/Bewohner.hxx>
#include <QTextEdit>
#include <QTextBlock>

LeistungstraegerBox::LeistungstraegerBox(SessionContext &_context, QWidget *parent,QSharedPointer< ebp::Leistungstraeger > currentLeistungstraeger) :
    QGroupBox(parent),
    leistungstraeger(currentLeistungstraeger),
    context(_context),
    ui(new Ui::LeistungstraegerBox)
{
    ui->setupUi(this);
    if (leistungstraeger.isNull())
	createLeistungstraeger();

    this->initField();
}


LeistungstraegerBox::~LeistungstraegerBox()
{
    delete ui;
}

void LeistungstraegerBox::initField()
{
    ui->leistungstrGerLineEdit->setText(leistungstraeger->name());
    ui->straELineEdit->setText(leistungstraeger->strasse());
    ui->pLZLineEdit->setText(leistungstraeger->plz());
    ui->ortLineEdit->setText(leistungstraeger->ort());
    ui->vornameLineEdit->setText(leistungstraeger->ansprechpartner().section("*:*",0,0));
    ui->nachnameLineEdit->setText(leistungstraeger->ansprechpartner().section("*:*",1,1));
    ui->telefonLineEdit->setText(leistungstraeger->telefon());
    ui->faxLineEdit->setText(leistungstraeger->fax());
    ui->eMailLineEdit->setText(leistungstraeger->email());
    ui->textEdit->setHtml(leistungstraeger->anmerkung());
}
/**
  * \brief Speichern des Inhalts
  */
bool LeistungstraegerBox::saveContent()
{
    bool result = false;
    if (context.curBewohner!=NULL)
    {
        if (!leistungstraeger.isNull())
        {
            leistungstraeger->name(ui->leistungstrGerLineEdit->text());
            leistungstraeger->strasse(ui->straELineEdit->text());
            leistungstraeger->plz(ui->pLZLineEdit->text());
            leistungstraeger->ort(ui->ortLineEdit->text());
            leistungstraeger->ansprechpartner(ui->vornameLineEdit->text()+"*:*"+ui->nachnameLineEdit->text());
            leistungstraeger->telefon(ui->telefonLineEdit->text());
            leistungstraeger->fax(ui->faxLineEdit->text());
            leistungstraeger->email(ui->eMailLineEdit->text());
            leistungstraeger->anmerkung(ui->textEdit->toHtml());

            if(leistungstraeger->update(this->context.curConnection))
                result = true;
            else
                result =false;
        }
    }
    return result;
}
void LeistungstraegerBox::createLeistungstraeger()
{
    if(context.curBewohner!=NULL)
    {
	leistungstraeger = QSharedPointer<ebp::Leistungstraeger>(new ebp::Leistungstraeger("Neuer Leistungsträger"));
	leistungstraeger->create(context.curConnection);
	ebp::Leistungstraeger::linkBewohner(leistungstraeger,context.curBewohner);
	leistungstraeger->update(this->context.curConnection);
    }
}
