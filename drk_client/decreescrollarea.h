#ifndef DECREESCROLLAREA_H
#define DECREESCROLLAREA_H

#include <QScrollArea>
#include "sessioncontext.h"
#include "savecontentinterface.h"

namespace Ui {
    class DecreeScrollArea;
}

class DecreeScrollArea : public QScrollArea
{
    Q_OBJECT
     const SessionContext &con;

public:
    explicit DecreeScrollArea(const SessionContext &context,QWidget *parent = 0);
    ~DecreeScrollArea();
    bool saveContent();


private:
    Ui::DecreeScrollArea *ui;
};

#endif // DECREESCROLLAREA_H
