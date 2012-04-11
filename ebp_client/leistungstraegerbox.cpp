#include "leistungstraegerbox.h"
#include "ui_leistungstraegerbox.h"
#include <QString>
#include <QSharedPointer>
#include <EBPdb/Leistungstraeger.hxx>
#include <EBPdb/Bewohner.hxx>
#include <QTextEdit>
#include <QTextBlock>

LeistungstraegerBox::LeistungstraegerBox(const SessionContext &context,QWidget *parent,QSharedPointer< ebp::Leistungstraeger > currentLeistungstraeger) :
    QGroupBox(parent),
    con(context),
    Ltraeger(currentLeistungstraeger),
    ui(new Ui::LeistungstraegerBox)
{
    ui->setupUi(this);
    if(Ltraeger!=0);
        this->initField();
}
/*LeistungstraegerBox::LeistungstraegerBox(const SessionContext &context,QWidget *parent) :
    QGroupBox(parent),
    con(context),
    Ltraeger(currentLeistungstraeger),
    ui(new Ui::LeistungstraegerBox)
{
    ui->setupUi(this);
}*/

LeistungstraegerBox::~LeistungstraegerBox()
{
    delete ui;
}

void LeistungstraegerBox::initField()
{
    ui->leistungstrGerLineEdit->setText(Ltraeger->name());
    ui->straELineEdit->setText(Ltraeger->strasse());
    ui->pLZLineEdit->setText(Ltraeger->plz());
    ui->ortLineEdit->setText(Ltraeger->ort());
    ui->vornameLineEdit->setText(Ltraeger->ansprechpartner().section("*:*",0,0));
    ui->nachnameLineEdit->setText(Ltraeger->ansprechpartner().section("*:*",1,1));
    ui->telefonLineEdit->setText(Ltraeger->telefon());
    ui->faxLineEdit->setText(Ltraeger->fax());
    ui->eMailLineEdit->setText(Ltraeger->email());
    ui->textEdit->setText(Ltraeger->anmerkung());
}

bool LeistungstraegerBox::saveContent()
{
    if (con.curBewohner!=NULL)
    {
        if (Ltraeger == 0)
            createLeistungstraeger();
        Ltraeger->name(ui->leistungstrGerLineEdit->text());
        Ltraeger->strasse(ui->straELineEdit->text());
        Ltraeger->plz(ui->pLZLineEdit->text());
        Ltraeger->ort(ui->ortLineEdit->text());
        Ltraeger->ansprechpartner(ui->vornameLineEdit->text()+"*:*"+ui->nachnameLineEdit->text());
        Ltraeger->telefon(ui->telefonLineEdit->text());
        Ltraeger->fax(ui->faxLineEdit->text());
        Ltraeger->email(ui->eMailLineEdit->text());
        Ltraeger->anmerkung(ui->textEdit->toPlainText());

        Ltraeger->update(this->con.curConnection);
        return true;
    }
    return false;
}
void LeistungstraegerBox::createLeistungstraeger()
{
    if(con.curBewohner!=NULL)
    {
        this->bewohner_leistungstraeger=con.curBewohner->loadLeistungstraeger(con.curConnection);
        QSharedPointer< ebp::Leistungstraeger > tmpPointer(new ebp::Leistungstraeger("Neuer Leistungsträger"));
        tmpPointer->create(con.curConnection);
        QSharedPointer<ebp::Bewohner> tempB = con.allBewohner.at(con.allBewohner.indexOf(con.curBewohner));;

        ebp::Leistungstraeger::linkBewohner(tmpPointer,tempB);
        //bewohner_verfuegungen.clear();
        tmpPointer->update(this->con.curConnection);
        con.curBewohner->update((this->con.curConnection));
        bewohner_leistungstraeger.append(tmpPointer);
    }
}
