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
    qDebug() << "Verfügung";
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
            case 0:
                Fixierung = this->Fixierung=bewohner_verfuegungen.at(i);
                break;
            case 1:
                Bettgitter = this->Bettgitter=bewohner_verfuegungen.at(i);
                break;
            case 2:
                Psychopharmaka = this->Psychopharmaka=bewohner_verfuegungen.at(i);
                break;
            case 3:
                Patientenverfuegung = this->Patientenverfuegung=bewohner_verfuegungen.at(i);
                break;
            }
    }
}

void DecreeScrollArea::initField()
{
    if (con.curBewohner!=NULL)
    {

    //    if (~(Fixierung.isNull()))
        if (this->Fixierung!=NULL)
        {
            ui->FixierungAktiv->setCurrentIndex(Fixierung->aktiv());
            ui->FixierungDate->setDate(Fixierung->gerichtsbescheid());
            ui->FixierungReason->setText(Fixierung->grund());
            if ((Fixierung->gerichtsbescheid() == voidDate)||
                    (Fixierung->gerichtsbescheid().isNull()))
                ui->FixierungBescheid->setCurrentIndex(0);
            else
            {
                ui->FixierungBescheid->setCurrentIndex(1);
            }
        }

        //if (~(Bettgitter.isNull()))
        if (this->Bettgitter!=NULL)
        {
            ui->BettGitterAktiv->setCurrentIndex(Bettgitter->aktiv());
            ui->BettGitterDate->setDate(Bettgitter->gerichtsbescheid());
            ui->BettGitterReason->setText(Bettgitter->grund());
            if ((Bettgitter->gerichtsbescheid() == voidDate)||
                    (Bettgitter->gerichtsbescheid().isNull()))
                ui->BettGitterBescheid->setCurrentIndex(0);
            else
            {
                ui->BettGitterBescheid->setCurrentIndex(1);
            }
        }

        //if (~(Psychopharmaka.isNull()))
        if(this->Psychopharmaka!=NULL)
        {
            ui->PsychoAktiv->setCurrentIndex(Psychopharmaka->aktiv());
            ui->PsychoDate->setDate(Psychopharmaka->gerichtsbescheid());
            ui->PsychoReason->setText(Psychopharmaka->grund());
            if ((Psychopharmaka->gerichtsbescheid() == voidDate)||
                    (Psychopharmaka->gerichtsbescheid().isNull()))
                ui->PsychoBescheid->setCurrentIndex(0);
            else
            {
                ui->PsychoBescheid->setCurrentIndex(1);
            }
        }

        //if (~(Patientenverfuegung.isNull()))
        if(this->Patientenverfuegung!=NULL)
        {
            ui->PatientenAktiv->setCurrentIndex(Patientenverfuegung->aktiv());
            ui->PatientenDate->setDate(Patientenverfuegung->gerichtsbescheid());
            ui->PatientenReason->setText(Patientenverfuegung->grund());
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
            //if (Fixierung.isNull())
            if (this->Fixierung==NULL)
            {
                createVerfuegung(ebp::Verfuegung::Fixierung);
            }
            Fixierung->aktiv(ui->FixierungAktiv->currentIndex());
            Fixierung->grund(ui->FixierungReason->toPlainText());
            if(ui->FixierungBescheid->currentIndex())
                Fixierung->gerichtsbescheid(ui->FixierungDate->date());
            else
                Fixierung->gerichtsbescheid(voidDate);
            Fixierung->update(this->con.curConnection);
        }
        else
        {
            //if (~(Fixierung.isNull()))
            if (this->Fixierung!=NULL)
            {
                Fixierung->remove(con.curConnection);
                Fixierung.clear();
            }
        }
        if (ui->BettGitterAktiv->currentIndex()==1)
        {
            //if (Bettgitter.isNull())
            if (this->Bettgitter==NULL)
            {
                createVerfuegung(ebp::Verfuegung::Bettgitter);
            }
            Bettgitter->aktiv(ui->BettGitterAktiv->currentIndex());
            Bettgitter->grund(ui->BettGitterReason->toPlainText());
            if(ui->BettGitterBescheid->currentIndex())
                Bettgitter->gerichtsbescheid(ui->BettGitterDate->date());
            else
                Bettgitter->gerichtsbescheid(voidDate);
            Bettgitter->update(this->con.curConnection);
        }
        else
        {
            //if (~(Bettgitter.isNull()))
            if (this->Bettgitter!=NULL)
            {
                Bettgitter->remove(con.curConnection);
                Bettgitter.clear();
            }
        }
        if (ui->PsychoAktiv->currentIndex()==1)
        {
           //if (Psychopharmaka.isNull())
            if(this->Psychopharmaka==NULL)
            {
                createVerfuegung(ebp::Verfuegung::Psychopharmaka);
            }
            Psychopharmaka->aktiv(ui->PsychoAktiv->currentIndex());
            Psychopharmaka->grund(ui->PsychoReason->toPlainText());
            if(ui->PsychoBescheid->currentIndex())
                Psychopharmaka->gerichtsbescheid(ui->PsychoDate->date());
            else
                Psychopharmaka->gerichtsbescheid(voidDate);
            Psychopharmaka->update(this->con.curConnection);
        }
        else
        {
            //if (~(Psychopharmaka.isNull()))
            if(this->Psychopharmaka!=NULL)
            {
                Psychopharmaka->remove(con.curConnection);
                Psychopharmaka.clear();
            }
        }
        if (ui->PatientenAktiv->currentIndex()==1)
        {
            //if (Patientenverfuegung.isNull())
            if(this->Patientenverfuegung==NULL)
            {
                createVerfuegung(ebp::Verfuegung::Patientenverfuegung);
            }
            Patientenverfuegung->aktiv(ui->PatientenAktiv->currentIndex());
            Patientenverfuegung->grund(ui->PatientenReason->toPlainText());
            if(ui->PatientenBescheid->currentIndex())
                Patientenverfuegung->gerichtsbescheid(ui->PatientenDate->date());
            else
                Patientenverfuegung->gerichtsbescheid(voidDate);
            Patientenverfuegung->update(this->con.curConnection);
        }
        else
        {
            //if (~(Patientenverfuegung.isNull()))
            if(this->Patientenverfuegung!=NULL)
            {
                Patientenverfuegung->remove(con.curConnection);
                Patientenverfuegung.clear();
            }
        }


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
        bewohner_verfuegungen.append(tmpVerfuegung);
        tmpVerfuegung->update(this->con.curConnection);

        switch(verfuegungTyp)
            {
            case 0:
                Fixierung = tmpVerfuegung;
                break;
            case 1:
                Bettgitter = tmpVerfuegung;
                break;
            case 2:
                Psychopharmaka = tmpVerfuegung;
                break;
            case 3:
                Patientenverfuegung = tmpVerfuegung;
                break;
            }
      /*  if (tmpVerfuegung->create( con.curConnection ))
        {
            //qDebug()<<"Erfolg!";
            QMessageBox::about(this, tr("Erfolg"),tr("Verfuegung wurde erfolgreich angelegt"));
        }
        else
        {
            QMessageBox::critical(this, tr("Warnung"),tr("Verfuegung konnte nicht angelegt werden"));
        }*/
    }
}
