#ifndef CHOOSEDIALOG_H
#define CHOOSEDIALOG_H

#include <QDialog>
#include "customlistwidgetitem.h"
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Bewohner.hxx>

namespace Ui {
    class ChooseDialog;
}

class ChooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDialog(QString typ, QWidget *parent = 0);
    ~ChooseDialog();


private slots:
    virtual void on_buttonBox_accepted();

protected:
    Ui::ChooseDialog *ui;

};
/////////////////////////////////////// Mitarbeiter wählen ////////////////////////////////////////////////////

class ChooseMaDialog : public ChooseDialog
{
    Q_OBJECT
private:
    QList < CustomListWidgetItem <  ebp::Mitarbeiter >  *> maItemsList;
private slots:
    void on_buttonBox_accepted();
public:
    explicit ChooseMaDialog(QList < QSharedPointer < ebp::Mitarbeiter > > maList, QString typ, QWidget *parent);
signals:
    void chosen(QSharedPointer < ebp::Mitarbeiter > chosenMa);

};

////////////////////////////////////// Bewohner wählen /////////////////////////////////////////////////////////
class ChooseBwDialog : public ChooseDialog
{
    Q_OBJECT
private:
    QList < CustomListWidgetItem <  ebp::Bewohner >  *> bwItemsList;
private slots:
    void on_buttonBox_accepted();
public:
    explicit ChooseBwDialog(QList < QSharedPointer < ebp::Bewohner > > bwList, QString typ, QWidget *parent);
signals:
    void chosen(QSharedPointer < ebp::Bewohner > chosenBw);

};

////////////////////////////////////// Wohngruppe wählen /////////////////////////////////////////////////////////
class ChooseWgDialog : public ChooseDialog
{
    Q_OBJECT
private:
    QList < CustomListWidgetItem <  ebp::Wohngruppe >  *> wgItemsList;
private slots:
    void on_buttonBox_accepted();
public:
    explicit ChooseWgDialog(QList < QSharedPointer < ebp::Wohngruppe > > wgList, QString typ, QWidget *parent);
signals:
    void chosen(QSharedPointer < ebp::Wohngruppe > chosenWg);

};

#endif // CHOOSEDIALOG_H
