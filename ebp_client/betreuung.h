#ifndef BETREUUNG_H
#define BETREUUNG_H

#include <QWidget>
#include "sessioncontext.h"
#include "savecontentinterface.h"

namespace Ui {
    class Betreuung;
}
/**
  * \brief Maske: "Gesetzliche Betreuung"
  */
class Betreuung : public QWidget, public SaveContentInterface
{
    Q_OBJECT
public:
    explicit Betreuung(SessionContext &_context,QWidget *parent = 0);
    ~Betreuung();
    bool saveContent();	///< Speichert den Inhalts
    bool hasPendingChanges();


private slots:
    void on_gesundheitsfRsorgeComboBox_currentIndexChanged(int index);

    void on_vermGensfRsorgeComboBox_currentIndexChanged(int index);

    void on_aufentahltsbestimmungComboBox_currentIndexChanged(int index);

private:
    Ui::Betreuung *ui;
    SessionContext &conntext;
    void init();
};

#endif // BETREUUNG_H
