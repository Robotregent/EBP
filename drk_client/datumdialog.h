#ifndef DATUMDIALOG_H
#define DATUMDIALOG_H

#include <QDialog>

namespace Ui {
    class DatumDialog;
}

class DatumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatumDialog(QWidget *parent = 0);
    ~DatumDialog();

private:
    Ui::DatumDialog *ui;
};

#endif // DATUMDIALOG_H
