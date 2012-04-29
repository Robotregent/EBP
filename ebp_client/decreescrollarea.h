#ifndef DECREESCROLLAREA_H
#define DECREESCROLLAREA_H

#include <QScrollArea>
#include <QList>
#include <EBPdb/Verfuegung.hxx>
#include "sessioncontext.h"
#include "savecontentinterface.h"

namespace Ui {
    class DecreeScrollArea;
}
/**
  * \brief Maske: "Verfügungen"
  */
class DecreeScrollArea : public QScrollArea, public SaveContentInterface
{
    Q_OBJECT
    const SessionContext &con;
    QList <QSharedPointer< ebp::Verfuegung > > bewohner_verfuegungen;
    QSharedPointer< ebp::Verfuegung > Fixierung;
    QSharedPointer< ebp::Verfuegung > Bettgitter;
    QSharedPointer< ebp::Verfuegung > Psychopharmaka;
    QSharedPointer< ebp::Verfuegung > Patientenverfuegung;
    QDate voidDate;
    void initField();

public:
    explicit DecreeScrollArea(const SessionContext &context,QWidget *parent = 0);
    ~DecreeScrollArea();
    bool saveContent();			    ///< Speichern den Inhalts
    bool hasPendingChanges();
    enum enumTypes{Fix, Bet, Psy, Pat};


private slots:
    void on_FixierungBescheid_currentIndexChanged(int index);

    void on_FixierungAktiv_currentIndexChanged(int index);

    void on_BettGitterBescheid_currentIndexChanged(int index);

    void on_BettGitterAktiv_currentIndexChanged(int index);

    void on_PsychoAktiv_currentIndexChanged(int index);

    void on_PsychoBescheid_currentIndexChanged(int index);

    void on_PatientenAktiv_currentIndexChanged(int index);

    void on_PatientenBescheid_currentIndexChanged(int index);

private:
    Ui::DecreeScrollArea *ui;
    void createVerfuegung(ebp::Verfuegung::Typ verfuegungTyp);
    void getCurrentVerfuegungen();

};

#endif // DECREESCROLLAREA_H
