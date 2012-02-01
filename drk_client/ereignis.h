#ifndef EREIGNIS_H
#define EREIGNIS_H

#include <QWidget>
#include <QVBoxLayout>
#include "einzelereignis.h"

namespace Ui {
    class Ereignis;
}

class Ereignis : public QWidget
{
    Q_OBJECT

public:
    explicit Ereignis(QWidget *parent = 0);
    ~Ereignis();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Ereignis *ui;
    QList<EinzelEreignis *> EreignisListe;
    //QWidget *puffer;
    QVBoxLayout *pufferLayout;
};

#endif // EREIGNIS_H
