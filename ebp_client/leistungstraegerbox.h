#ifndef LEISTUNGSTRAEGERBOX_H
#define LEISTUNGSTRAEGERBOX_H

#include <QGroupBox>
#include <QSharedPointer>
#include "sessioncontext.h"
#include <QList>

namespace Ui {
    class LeistungstraegerBox;
}

class LeistungstraegerBox : public QGroupBox
{
    Q_OBJECT
    void initField();
    QSharedPointer< ebp::Leistungstraeger > leistungstraeger;
    SessionContext &context;
public:
    explicit LeistungstraegerBox(SessionContext &_context, QWidget *parent = 0,QSharedPointer< ebp::Leistungstraeger > currentLeistungstraeger = 0);
   // explicit LeistungstraegerBox(const SessionContext &context,QWidget *parent = 0);
    static const int fixedWidth = 670;
    ~LeistungstraegerBox();
    bool saveContent();

private:
    Ui::LeistungstraegerBox *ui;
    void createLeistungstraeger();
};

#endif // LEISTUNGSTRAEGERBOX_H
