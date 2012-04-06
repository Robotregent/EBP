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
    bool saveContent();
    enum enumTypes{Fix, Bet, Psy, Pat};


private:
    Ui::DecreeScrollArea *ui;
    void createVerfuegung(ebp::Verfuegung::Typ verfuegungTyp);
    void getCurrentVerfuegungen();

};

#endif // DECREESCROLLAREA_H
