#ifndef MELDELISTE_H
#define MELDELISTE_H

#include <QWidget>
#include <QDate>
#include <QString>
#include <EBPdb/Abwesenheit.hxx>
#include "sessioncontext.h"
#include "savecontentinterface.h"
#include <QAbstractItemModel>

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

public slots:
    void stateChanged(int row, int col);

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
