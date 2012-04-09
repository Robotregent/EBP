#ifndef EREIGNIS_H
#define EREIGNIS_H

#include <QWidget>
#include <QVBoxLayout>
#include "sessioncontext.h"
#include "einzelereignis.h"
#include "texttransferagent.h"

namespace Ui {
    class Ereignis;
}

class Ereignis : public QWidget
{
    Q_OBJECT

public:
    explicit Ereignis(SessionContext _context, TextTransferAgent *agent,QWidget *parent = 0);
    ~Ereignis();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Ereignis *ui;
    QList<EinzelEreignis *> EreignisListe;
    TextTransferAgent *transferAgent;
    SessionContext context;
    QVBoxLayout *pufferLayout;
    void initEreignisse();
};

#endif // EREIGNIS_H
