#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
    class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private slots:
    void on_pushButton_clicked();

    void on_passwortLineEdit_returnPressed();

private:
    Ui::LoginForm *ui;
    MainWindow *_parent;
    QString dbName;
};

#endif // LOGINFORM_H
