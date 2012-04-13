#ifndef BEWOHNERPROTOKOLL_H
#define BEWOHNERPROTOKOLL_H

#include <QScrollArea>
#include <EBPdb/Mitarbeiter.hxx>


#include "sessioncontext.h"
#include "texttransferinterface.h"
#include "savecontentinterface.h"
#include "choosedialog.h"
namespace Ui {
    class BewohnerProtokoll;
}

class BewohnerProtokoll : public QScrollArea, public TextTransferInterface, public SaveContentInterface
{
    Q_OBJECT

public:
    explicit BewohnerProtokoll(SessionContext &_conntext, QWidget *parent = 0);
    TextTransferInformation getSelectedText();
    bool saveContent();
    ~BewohnerProtokoll();

private slots:
    void on_addTeilnehmer_clicked();
    void chosenMitarbeiter(QSharedPointer< ebp::Mitarbeiter > chosenMa);

    void on_ProtokollListe_currentRowChanged(int currentRow);

private:
    Ui::BewohnerProtokoll *ui;
    SessionContext &context;
    void init();
    void initHeader();
    ChooseMaDialog *maDialog;
    QList< QSharedPointer <ebp::Mitarbeiter> > schreiber;
    QList< QSharedPointer <ebp::Mitarbeiter> > teilnehmer;
    QList< QSharedPointer <ebp::Protokoll> > protokolle;
    QSharedPointer <ebp::Protokoll> curProtokoll;
    void fillFields();
    void fillParticipants(QList< QSharedPointer < ebp::Mitarbeiter > > ma, Qt::CheckState state);

};

#endif // BEWOHNERPROTOKOLL_H
