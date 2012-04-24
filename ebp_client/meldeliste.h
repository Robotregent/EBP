#ifndef MELDELISTE_H
#define MELDELISTE_H

#include <QWidget>
#include <QDate>
#include <QString>
#include <EBPdb/Abwesenheit.hxx>
#include "sessioncontext.h"
#include "savecontentinterface.h"
#include <QAbstractItemModel>
#define DATECALCCONVSCHEME "yyyyMMdd"
#define DATEOUTPUTCONVSCHEME "d. MMMM yyyy"
#define DATEOUTPUTLISTSCHEME "MM/dd/yyyy"
#define OUTPUTGRUNDLENGTH 35
#define OUTPUTNAMELENGTH 30
#define OUTPUTDATELENGTH 14

namespace Ui {
    class MeldeListe;
}

/**
  * \brief Maske: "Meldeliste"
  */
class MeldeListe : public QWidget, public SaveContentInterface
{
    Q_OBJECT

public:
    explicit MeldeListe(const SessionContext &_curContext,QWidget *parent = 0);
    ~MeldeListe();
    bool saveContent();
    static bool dateLessThan(const QSharedPointer< ebp::Abwesenheit > s1, const QSharedPointer< ebp::Abwesenheit > s2);

public slots:
    void stateChanged(int row, int col);
    void changeList();
    void exportFile();
    void csvExport();

private:

    QString isAbwesend(QSharedPointer < ebp::Bewohner > tmpBewohner,QDate tmpDate);
    void createAbwesenheit(QSharedPointer <ebp::Bewohner> tmpBewohner,QString tempGrund);
    QList <QSharedPointer< ebp::Abwesenheit > > bewohner_abwesenheit;
    QList< QSharedPointer <ebp::Bewohner> > curWgBewohner;
    const SessionContext curContext;
    Ui::MeldeListe *ui;
    void createList();    
};


#endif // MELDELISTE_H
