#ifndef INFOFRAME_H
#define INFOFRAME_H

#include <QFrame>

namespace Ui {
    class InfoFrame;
}

class InfoFrame : public QFrame
{
    Q_OBJECT

public:
    explicit InfoFrame(QWidget *parent = 0);
    ~InfoFrame();

private:
    Ui::InfoFrame *ui;
};

#endif // INFOFRAME_H
