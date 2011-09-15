#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "../drkv/Mitarbeiter.hxx"
#include "../drkv/database.hxx"

using namespace drkv;

namespace Ui {
    class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = 0);
    ~AdminDialog();

private slots:
    void on_button_MA_suchen_clicked();

private:
    Ui::AdminDialog *ui;
    void init();
    database *db;
    QStringList
};

#endif // ADMINDIALOG_H
