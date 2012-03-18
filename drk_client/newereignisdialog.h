#ifndef NEWEREIGNISDIALOG_H
#define NEWEREIGNISDIALOG_H

#include <QDialog>
#include "einzelereignis.h"
#include "ereignis.h"
typedef struct
{
    bool isEmpty;
    QDateTime time;
    QString MitarbeiterZeichen;
    QString EreignisText;
} EreignisInformation;


namespace Ui {
    class NewEreignisDialog;
}

class NewEreignisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewEreignisDialog(EreignisInformation *_ereignis,QWidget *parent = 0);
    ~NewEreignisDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewEreignisDialog *ui;
    EreignisInformation *ereignis;
};


#endif // NEWEREIGNISDIALOG_H
