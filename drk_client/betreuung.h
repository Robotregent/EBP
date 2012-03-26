#ifndef BETREUUNG_H
#define BETREUUNG_H

#include <QWidget>
#include "sessioncontext.h"
#include "savecontentinterface.h"

namespace Ui {
    class Betreuung;
}

class Betreuung : public QWidget
{
    Q_OBJECT
     const SessionContext &con;
public:
    explicit Betreuung(const SessionContext &context,QWidget *parent = 0);
    ~Betreuung();
    bool saveContent();


private:
    Ui::Betreuung *ui;
};

#endif // BETREUUNG_H
