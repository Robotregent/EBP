#ifndef PROJEKT_H
#define PROJEKT_H

#include <QWidget>
#include "texttransferinterface.h"
#include <projekt.h>
#include "sessioncontext.h"
#include "savecontentinterface.h"

namespace Ui {
    class Projekt;
}

class Projekt : public QWidget, public TextTransferInterface, public SaveContentInterface
{
    Q_OBJECT

public:
    explicit Projekt(SessionContext &_curContext, QWidget *parent = 0);
    TextTransferInformation getSelectedText();
    bool saveContent();
    ~Projekt();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void setChosenMa(QSharedPointer< ebp::Mitarbeiter > chosenMa);

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::Projekt *ui;
    SessionContext curContext;
    QList< QSharedPointer < ebp::Projekt > > projects;
    QSharedPointer < ebp::Projekt > curProject;
    QSharedPointer < ebp::Mitarbeiter > potentiallyNewMa;
    void setProjekt();

};

#endif // PROJEKT_H




