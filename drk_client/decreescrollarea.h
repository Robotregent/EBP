#ifndef DECREESCROLLAREA_H
#define DECREESCROLLAREA_H

#include <QScrollArea>

namespace Ui {
    class DecreeScrollArea;
}

class DecreeScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit DecreeScrollArea(QWidget *parent = 0);
    ~DecreeScrollArea();

private:
    Ui::DecreeScrollArea *ui;
};

#endif // DECREESCROLLAREA_H
