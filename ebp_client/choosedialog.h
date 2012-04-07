#ifndef CHOOSEDIALOG_H
#define CHOOSEDIALOG_H

#include <QDialog>
#include "custumlistwidgetitem.h"
#include <EBPdb/Mitarbeiter.hxx>

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
///////////////////////////////////////

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


#endif // CHOOSEDIALOG_H
