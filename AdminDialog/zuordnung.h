#ifndef ZUORDNUNG_H
#define ZUORDNUNG_H

#include <QDialog>
#include <QAbstractTableModel>
namespace Ui {
    class Zuordnung;
}

class Zuordnung : public QDialog
{
    Q_OBJECT

public:
    explicit Zuordnung(QAbstractTableModel *_model,QWidget *parent = 0);
    ~Zuordnung();

private:
    Ui::Zuordnung *ui;
    QAbstractTableModel *model;
};

#endif // ZUORDNUNG_H
