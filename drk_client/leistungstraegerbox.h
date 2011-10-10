#ifndef LEISTUNGSTRAEGERBOX_H
#define LEISTUNGSTRAEGERBOX_H

#include <QGroupBox>

namespace Ui {
    class LeistungstraegerBox;
}

class LeistungstraegerBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit LeistungstraegerBox(QWidget *parent = 0);
    ~LeistungstraegerBox();

private:
    Ui::LeistungstraegerBox *ui;
};

#endif // LEISTUNGSTRAEGERBOX_H
