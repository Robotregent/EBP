#ifndef DOKUMENTATION_H
#define DOKUMENTATION_H

#include <QWidget>

namespace Ui {
    class Dokumentation;
}

class Dokumentation : public QWidget
{
    Q_OBJECT

public:
    explicit Dokumentation(QString name,QWidget *parent = 0);
    ~Dokumentation();

private:
    Ui::Dokumentation *ui;
};

#endif // DOKUMENTATION_H
