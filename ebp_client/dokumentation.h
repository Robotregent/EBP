#ifndef DOKUMENTATION_H
#define DOKUMENTATION_H

#include <QWidget>
#include <EBPdb/Dokumentation.hxx>
#include "savecontentinterface.h"
#include "sessioncontext.h"

namespace Ui {
    class Dokumentation;
}

class Dokumentation : public QWidget, public SaveContentInterface
{
    Q_OBJECT

public:
    explicit Dokumentation(SessionContext &context, ebp::Dokumentation::Typ typ, QWidget *parent = 0);
    ~Dokumentation();
    bool saveContent();

private:
    Ui::Dokumentation *ui;
    SessionContext &curContext;
    QSharedPointer< ebp::Dokumentation > curDoku;

};

#endif // DOKUMENTATION_H