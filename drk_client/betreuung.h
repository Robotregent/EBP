#ifndef BETREUUNG_H
#define BETREUUNG_H

#include <QWidget>

namespace Ui {
    class Betreuung;
}

class Betreuung : public QWidget
{
    Q_OBJECT
public:
    explicit Betreuung(QWidget *parent = 0);
    ~Betreuung();

private:
    Ui::Betreuung *ui;
};

#endif // BETREUUNG_H
