#ifndef BETREUUNG_H
#define BETREUUNG_H

#include <QWidget>
#include "sessioncontext.h"
#include "savecontentinterface.h"

namespace Ui {
    class Betreuung;
}

class Betreuung : public QWidget, public SaveContentInterface
{
    Q_OBJECT
public:
    explicit Betreuung(SessionContext &_context,QWidget *parent = 0);
    ~Betreuung();
    bool saveContent();


private:
    Ui::Betreuung *ui;
    SessionContext &conntext;
    void init();
};

#endif // BETREUUNG_H
