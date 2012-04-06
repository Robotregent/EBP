#ifndef TEXTTRANSFERAGENT_H
#define TEXTTRANSFERAGENT_H

#include <QFrame>
#include "sessioncontext.h"
#include "texttransferinterface.h"

namespace Ui {
    class TextTransferAgent;
}

class TextTransferAgent : public QFrame
{
    Q_OBJECT

public:
    explicit TextTransferAgent(QList<TextTransferInterface *>Interfaces,const SessionContext &context, QWidget *parent = 0);
    ~TextTransferAgent();
    void registerNewInterface(TextTransferInterface *newInterface);

private slots:
    void on_bewohnerBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::TextTransferAgent *ui;
    QList<TextTransferInterface *> textInterfaces;
    const SessionContext &_context;
};

#endif // TEXTTRANSFERAGENT_H
