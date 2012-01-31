#ifndef GRUPPENBUCH_H
#define GRUPPENBUCH_H

#include <QWidget>

namespace Ui {
    class Gruppenbuch;
}

class Gruppenbuch : public QWidget
{
    Q_OBJECT

public:
    explicit Gruppenbuch(QWidget *parent = 0);
    ~Gruppenbuch();

private:
    Ui::Gruppenbuch *ui;
};

#endif // GRUPPENBUCH_H
