#include "decreescrollarea.h"
#include "ui_decreescrollarea.h"
#include <QDebug>
#include <EBPdb/Verfuegung.hxx>
#include <EBPdb/Bewohner.hxx>
#include <QVariant>
#include <QString>
#include <QMessageBox>
#include <QDate>

DecreeScrollArea::DecreeScrollArea(const SessionContext &context,QWidget *parent) :
    QScrollArea(parent),
    con(context),
    ui(new Ui::DecreeScrollArea)
{
    ui->setupUi(this);
    if (con.curBewohner!=NULL)
    {
        this->voidDate.setDate(2000,1,1);
        this->getCurrentVerfuegungen();
        this->initField();
    }
}


DecreeScrollArea::~DecreeScrollArea()
{
    delete ui;
}

void DecreeScrollArea::getCurrentVerfuegungen()
{
    int entryCount;
    this->bewohner_verfuegungen=con.curBewohner->loadVerfuegungen(con.curConnection);

    entryCount=bewohner_verfuegungen.count();
    for(int i = 0; i <entryCount; i++)
    {
        switch(bewohner_verfuegungen.at(i)->typ())
            {
            case ebp::Verfuegung::Fixierung:
                Fixierung = this->Fixierung=bewohner_verfuegungen.at(i);
                break;
            case ebp::Verfuegung::Bettgitter:
                Bettgitter = this->Bettgitter=bewohner_verfuegungen.at(i);
                break;
            case ebp::Verfuegung::Psychopharmaka:
                Psychopharmaka = this->Psychopharmaka=bewohner_verfuegungen.at(i);
                break;
            case ebp::Verfuegung::Patientenverfuegung:
                Patientenverfuegung = this->Patientenverfuegung=bewohner_verfuegungen.at(i);
                break;
            }
    }
}

void DecreeScrollArea::initField()
{
    if (con.curBewohner!=NULL)
    {

        if (this->Fixierung!=NULL)
        {
            ui->FixierungAktiv->setCurrentIndex(Fixierung->aktiv());
            ui->FixierungDate->setDate(Fixierung->gerichtsbescheid());
            ui->FixierungReason->setHtml(Fixierung->grund());
            if ((Fixierung->gerichtsbescheid() == voidDate)||
                    (Fixierung->gerichtsbescheid().isNull()))
                ui->FixierungBescheid->setCurrentIndex(0);
            else
            {
                ui->FixierungBescheid->setCurrentIndex(1);
            }
        }

        if (this->Bettgitter!=NULL)
        {
            ui->BettGitterAktiv->setCurrentIndex(Bettgitter->aktiv());
            ui->BettGitterDate->setDate(Bettgitter->gerichtsbescheid());
            ui->BettGitterReason->setHtml(Bettgitter->grund());
            if ((Bettgitter->gerichtsbescheid() == voidDate)||
                    (Bettgitter->gerichtsbescheid().isNull()))
                ui->BettGitterBescheid->setCurrentIndex(0);
            else
            {
                ui->BettGitterBescheid->setCurrentIndex(1);
            }
        }

        if(this->Psychopharmaka!=NULL)
        {
            ui->PsychoAktiv->setCurrentIndex(Psychopharmaka->aktiv());
            ui->PsychoDate->setDate(Psychopharmaka->gerichtsbescheid());
            ui->PsychoReason->setHtml(Psychopharmaka->grund());
            if ((Psychopharmaka->gerichtsbescheid() == voidDate)||
                    (Psychopharmaka->gerichtsbescheid().isNull()))
                ui->PsychoBescheid->setCurrentIndex(0);
            else
            {
                ui->PsychoBescheid->setCurrentIndex(1);
            }
        }

        if(this->Patientenverfuegung!=NULL)
        {
            ui->PatientenAktiv->setCurrentIndex(Patientenverfuegung->aktiv());
            ui->PatientenDate->setDate(Patientenverfuegung->gerichtsbescheid());
            ui->PatientenReason->setHtml(Patientenverfuegung->grund());
            if ((Patientenverfuegung->gerichtsbescheid() == voidDate)||
                    (Patientenverfuegung->gerichtsbescheid().isNull()))
                ui->PsychoBescheid->setCurrentIndex(0);
            else
            {
                ui->PsychoBescheid->setCurrentIndex(1);
            }
        }

    }

}


bool DecreeScrollArea::saveContent()
{
    if (con.curBewohner!=NULL)
    {

        if (ui->FixierungAktiv->currentIndex()==1)
        {
            if (this->Fixierung==NULL)
            {
                createVerfuegung(ebp::Verfuegung::Fixierung);
            }
            Fixierung->aktiv(ui->FixierungAktiv->currentIndex());
            Fixierung->grund(ui->FixierungReason->toHtml());
            if(ui->FixierungBescheid->currentIndex())
                Fixierung->gerichtsbescheid(ui->FixierungDate->date());
            else
                Fixierung->gerichtsbescheid(voidDate);
            Fixierung->update(this->con.curConnection);
        }
        else
        {
            if (this->Fixierung!=NULL)
            {
                Fixierung->remove(con.curConnection);
                Fixierung.clear();
            }
        }
        if (ui->BettGitterAktiv->currentIndex()==1)
        {
            if (this->Bettgitter==NULL)
            {
                createVerfuegung(ebp::Verfuegung::Bettgitter);
            }
            Bettgitter->aktiv(ui->BettGitterAktiv->currentIndex());
            Bettgitter->grund(ui->BettGitterReason->toHtml());
            if(ui->BettGitterBescheid->currentIndex())
                Bettgitter->gerichtsbescheid(ui->BettGitterDate->date());
            else
                Bettgitter->gerichtsbescheid(voidDate);
            Bettgitter->update(this->con.curConnection);
        }
        else
        {
            if (this->Bettgitter!=NULL)
            {
                Bettgitter->remove(con.curConnection);
                Bettgitter.clear();
            }
        }
        if (ui->PsychoAktiv->currentIndex()==1)
        {
            if(this->Psychopharmaka==NULL)
            {
                createVerfuegung(ebp::Verfuegung::Psychopharmaka);
            }
            Psychopharmaka->aktiv(ui->PsychoAktiv->currentIndex());
            Psychopharmaka->grund(ui->PsychoReason->toHtml());
            if(ui->PsychoBescheid->currentIndex())
                Psychopharmaka->gerichtsbescheid(ui->PsychoDate->date());
            else
                Psychopharmaka->gerichtsbescheid(voidDate);
            Psychopharmaka->update(this->con.curConnection);
        }
        else
        {
            if(this->Psychopharmaka!=NULL)
            {
                Psychopharmaka->remove(con.curConnection);

                Psychopharmaka.clear();
            }
        }
        if (ui->PatientenAktiv->currentIndex()==1)
        {

            if(this->Patientenverfuegung==NULL)
            {
                createVerfuegung(ebp::Verfuegung::Patientenverfuegung);
            }
            Patientenverfuegung->aktiv(ui->PatientenAktiv->currentIndex());
            Patientenverfuegung->grund(ui->PatientenReason->toHtml());
            if(ui->PatientenBescheid->currentIndex())
                Patientenverfuegung->gerichtsbescheid(ui->PatientenDate->date());
            else
                Patientenverfuegung->gerichtsbescheid(voidDate);
            Patientenverfuegung->update(this->con.curConnection);
        }
        else
        {

            if(this->Patientenverfuegung!=NULL)
            {
                Patientenverfuegung->remove(con.curConnection);

                Patientenverfuegung.clear();
            }
        }
        con.curConnection->flushCache();
        con.curBewohner->reload(con.curConnection);
        return true;
    }
    return false;
}

void DecreeScrollArea::createVerfuegung(ebp::Verfuegung::Typ verfuegungTyp)
{
    if(con.curBewohner!=NULL)
    {
        QSharedPointer< ebp::Verfuegung > tmpVerfuegung(new ebp::Verfuegung(0,verfuegungTyp,QDate(),""));
        tmpVerfuegung->create(con.curConnection);
        QSharedPointer<ebp::Bewohner> tempB = con.allBewohner.at(con.allBewohner.indexOf(con.curBewohner));

        ebp::Verfuegung::linkBewohner(tmpVerfuegung,tempB);
        tmpVerfuegung->update(this->con.curConnection);
        con.curBewohner->update((this->con.curConnection));
        bewohner_verfuegungen.append(tmpVerfuegung);
        switch(verfuegungTyp)
        {
        case ebp::Verfuegung::Fixierung:
            Fixierung = tmpVerfuegung;
            break;
        case ebp::Verfuegung::Bettgitter:
            Bettgitter = tmpVerfuegung;
            break;
        case ebp::Verfuegung::Psychopharmaka:
            Psychopharmaka = tmpVerfuegung;
            break;
        case ebp::Verfuegung::Patientenverfuegung:
            Patientenverfuegung = tmpVerfuegung;
            break;
        }
    }
}

bool DecreeScrollArea::hasPendingChanges()
{
    bool result = pendingChanges;
    if(this->ui->PatientenReason->document()->isUndoAvailable())
        result=true;
    if(this->ui->PsychoReason->document()->isUndoAvailable())
        result=true;
    if(this->ui->FixierungReason->document()->isUndoAvailable())
        result=true;
    if(this->ui->BettGitterReason->document()->isUndoAvailable())
        result=true;
    return result;
}

void DecreeScrollArea::on_FixierungBescheid_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges=true;
}

void DecreeScrollArea::on_FixierungAktiv_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges=true;
}

void DecreeScrollArea::on_BettGitterBescheid_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges=true;
}

void DecreeScrollArea::on_BettGitterAktiv_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges=true;
}

void DecreeScrollArea::on_PsychoAktiv_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges=true;
}

void DecreeScrollArea::on_PsychoBescheid_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges=true;
}

void DecreeScrollArea::on_PatientenAktiv_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges=true;
}

void DecreeScrollArea::on_PatientenBescheid_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges=true;
}
