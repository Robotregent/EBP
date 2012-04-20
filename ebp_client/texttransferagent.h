#ifndef TEXTTRANSFERAGENT_H
#define TEXTTRANSFERAGENT_H

#include <QFrame>
#include "sessioncontext.h"
#include "texttransferinterface.h"

namespace Ui {
    class TextTransferAgent;
}

/**
  * \brief Mediatorklasse für den Transfer von Textfragmenten zwischen Betreuungsplanung und Klassen die das TextTransferInterface implementiert haben.
  */
class TextTransferAgent : public QFrame
{
    Q_OBJECT

public:
    explicit TextTransferAgent(QList<TextTransferInterface *>Interfaces,const SessionContext &context, QWidget *parent = 0);
    ~TextTransferAgent();
    void registerNewInterface(TextTransferInterface *newInterface);			///< Fügt dem Mediator Objekt ein neus Kollegen objekt hinzu

private slots:
    void on_bewohnerBox_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_helpButton_clicked();

private:
    const SessionContext &_context;
    Ui::TextTransferAgent *ui;
    QSharedPointer< ebp::Bewohner > selectedBewohner;
    QList < QSharedPointer < ebp::Dokumentation > > dokus;
    QList<TextTransferInterface *> textInterfaces;
};

#endif // TEXTTRANSFERAGENT_H
