#ifndef LEISTUNGSTRAEGERBOX_H
#define LEISTUNGSTRAEGERBOX_H

#include <QGroupBox>
#include <QSharedPointer>
#include "sessioncontext.h"
#include <QList>

namespace Ui {
    class LeistungstraegerBox;
}
/**
  * \brief Einzelner Leistungsträger
  */
class LeistungstraegerBox : public QGroupBox
{
    Q_OBJECT
    void initField();
    QSharedPointer< ebp::Leistungstraeger > leistungstraeger;
    SessionContext &context;
public:
    explicit LeistungstraegerBox(SessionContext &_context, QWidget *parent = 0,QSharedPointer< ebp::Leistungstraeger > currentLeistungstraeger = QSharedPointer< ebp::Leistungstraeger >());
    static const int fixedWidth = 670;	    ///< constante für das Ausrichten des Layouts
    ~LeistungstraegerBox();
    bool saveContent();			    ///< Speichern den Inhalts

private:
    Ui::LeistungstraegerBox *ui;
    void createLeistungstraeger();
};

#endif // LEISTUNGSTRAEGERBOX_H
