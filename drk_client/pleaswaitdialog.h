#ifndef PLEASWAITDIALOG_H
#define PLEASWAITDIALOG_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
    class PleasWaitDialog;
}

class PleasWaitDialog : public QDialog
{
    Q_OBJECT
    MainWindow *_mw;
public:
    explicit PleasWaitDialog(MainWindow *mw, QWidget *parent = 0);
    ~PleasWaitDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PleasWaitDialog *ui;
};

#endif // PLEASWAITDIALOG_H
