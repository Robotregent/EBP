#ifndef ZUORDNUNG_H
#define ZUORDNUNG_H

#include <QDialog>
#include <QAbstractTableModel>
#include <EBPdb/Wohngruppe.hxx>
#include <EBPdb/Bewohner.hxx>
#include "costumlistwidget.h"
#include "employeelistmodel.h"

namespace Ui {
    class Zuordnung;
}
class Zuordnung : public QDialog
{
    Q_OBJECT

public:
    explicit Zuordnung(EmployeeTableModel *_model,QWidget *parent = 0);
    ~Zuordnung();

protected:
    QSharedPointer<ebp::connection> connectionPointer;
    Ui::Zuordnung *ui;
    EmployeeTableModel *model;
    virtual bool saveMapping() = 0;
    virtual bool setList(const QModelIndex &index)
    {
	Q_UNUSED(index)
	return false;
    }

private:
    //void set
private slots:
    virtual void on_buttonBox_accepted();
    void on_MitarbeiterView_clicked(const QModelIndex &index);
};
///////Wohngruppenzuordnung///////////////

class WohngruppenZuordnung : public Zuordnung
{
    Q_OBJECT
public:
    explicit WohngruppenZuordnung(EmployeeTableModel *_model, QWidget *parent);
private:
    QList<  QSharedPointer< ebp::Wohngruppe > > zugeordneteWohngruppen;
    QList<  QSharedPointer< ebp::Wohngruppe > > alleWohngruppen;
protected:
    virtual bool setList(const QModelIndex &index);
    bool saveMapping();
private slots:
    void on_buttonBox_accepted();
};
//////Bewohnerzuordnung/////////////////////
class BezugsbetreuungZuordnung : public Zuordnung
{
    Q_OBJECT
public:
    explicit BezugsbetreuungZuordnung(EmployeeTableModel *_model, QWidget *parent);
private:
    QList<  QSharedPointer< ebp::Bewohner > > zugeordneteBezugsbetreuung;
    QList<  QSharedPointer< ebp::Bewohner > > alleBezugsbetreuungen;
protected:
    virtual bool setList(const QModelIndex &index);
    bool saveMapping();
private slots:
    void on_buttonBox_accepted();
};
#endif // ZUORDNUNG_H
