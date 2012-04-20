#ifndef EINZELEREIGNIS_H
#define EINZELEREIGNIS_H

#include <QFrame>
#include <QDateTime>
#include <texttransferinterface.h>

namespace Ui {
    class EinzelEreignis;
}
/**
  *\brief Einzelnes "Ereignis"
  */
class EinzelEreignis : public QFrame, public TextTransferInterface
{
    Q_OBJECT

public:
    explicit EinzelEreignis(QWidget *parent = 0);
    void setContent(QDateTime datum, QString mitarbeiter, QString text);
    QDateTime getDatum();
    ~EinzelEreignis();
    TextTransferInformation getSelectedText();

private:
    Ui::EinzelEreignis *ui;

};

#endif // EINZELEREIGNIS_H
