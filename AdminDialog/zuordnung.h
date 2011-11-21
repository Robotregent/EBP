#ifndef ZUORDNUNG_H
#define ZUORDNUNG_H

#include <QDialog>

namespace Ui {
    class Zuordnung;
}

class Zuordnung : public QDialog
{
    Q_OBJECT

public:
    explicit Zuordnung(QWidget *parent = 0);
    ~Zuordnung();

private:
    Ui::Zuordnung *ui;
};

#endif // ZUORDNUNG_H
