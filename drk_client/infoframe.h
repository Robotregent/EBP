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
    void setCurBewohner(QString Bew);
    void setCurWohngruppe(QString group);

private:
    Ui::InfoFrame *ui;
    //QString _curBewohner;
    //QString _curWohngruppe;
};

#endif // INFOFRAME_H
