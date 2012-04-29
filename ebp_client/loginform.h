#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/connection.hxx>
#include "mainwindow.h"

namespace Ui {
    class LoginForm;
}
/**
  * \brief Maske: "Login"
  */
class LoginForm : public QWidget
{
    Q_OBJECT
signals:
    void validLogin(QSharedPointer<ebp::Mitarbeiter> newMitarbeiter, QSharedPointer<ebp::connection> newConnection);

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private slots:
    void on_pushButton_clicked();
    void on_passwortLineEdit_returnPressed();

private:
    Ui::LoginForm *ui;
    QString dbName;
    QString dbHost;
    unsigned int dbPort;
};

#endif // LOGINFORM_H
