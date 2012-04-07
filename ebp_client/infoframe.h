#ifndef INFOFRAME_H
#define INFOFRAME_H

#include <QFrame>
#include "choosedialog.h"
namespace Ui {
    class InfoFrame;
}

class InfoFrame : public QFrame
{
    Q_OBJECT

public:
    explicit InfoFrame(ChooseBwDialog *_bewohner, ChooseWgDialog *_wohngruppe, QWidget *parent = 0);
    ~InfoFrame();
    void setCurBewohner(QString Bew);
    void setCurWohngruppe(QString group);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::InfoFrame *ui;
    ChooseBwDialog *bewohner;
    ChooseWgDialog *wohngruppe;
    //QString _curWohngruppe;
};

#endif // INFOFRAME_H
