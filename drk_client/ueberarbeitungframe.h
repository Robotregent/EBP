#ifndef UEBERARBEITUNGFRAME_H
#define UEBERARBEITUNGFRAME_H

#include <QFrame>

namespace Ui {
    class UeberarbeitungFrame;
}

class UeberarbeitungFrame : public QFrame
{
    Q_OBJECT

public:
    explicit UeberarbeitungFrame(QWidget *parent = 0);
    ~UeberarbeitungFrame();

private:
    Ui::UeberarbeitungFrame *ui;
};

#endif // UEBERARBEITUNGFRAME_H
