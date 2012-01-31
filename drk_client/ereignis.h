#ifndef EREIGNIS_H
#define EREIGNIS_H

#include <QWidget>

namespace Ui {
    class Ereignis;
}

class Ereignis : public QWidget
{
    Q_OBJECT

public:
    explicit Ereignis(QWidget *parent = 0);
    ~Ereignis();

private:
    Ui::Ereignis *ui;
};

#endif // EREIGNIS_H
