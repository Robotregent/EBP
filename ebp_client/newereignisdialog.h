#ifndef NEWEREIGNISDIALOG_H
#define NEWEREIGNISDIALOG_H

#include <QDialog>
#include "einzelereignis.h"
#include "ereignis.h"
/**
  *\brief Hält alle notwendigen Informationen, wen ein neues Ereignis erzeugt wird
  */
typedef struct
{
    bool isEmpty;
    QDateTime time;
    QString EreignisText;
} EreignisInformation;


namespace Ui {
    class NewEreignisDialog;
}

/**
  * \brief Diealog, zum erfassen eines neuen Ereignisses
  */
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
