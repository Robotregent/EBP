#ifndef EINZELEREIGNIS_H
#define EINZELEREIGNIS_H

#include <QFrame>
#include <QDateTime>

namespace Ui {
    class EinzelEreignis;
}

class EinzelEreignis : public QFrame
{
    Q_OBJECT

public:
    explicit EinzelEreignis(QWidget *parent = 0);
    void setContent(QDateTime datum, QString mitarbeiter, QString text);
    ~EinzelEreignis();

private:
    Ui::EinzelEreignis *ui;

};

#endif // EINZELEREIGNIS_H
