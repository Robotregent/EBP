#ifndef PROJEKT_H
#define PROJEKT_H

#include <QWidget>
#include "texttransferinterface.h"

namespace Ui {
    class Projekt;
}

class Projekt : public QWidget, public TextTransferInterface
{
    Q_OBJECT

public:
    explicit Projekt(QWidget *parent = 0);
    TextTransferInformation getSelectedText();
    ~Projekt();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Projekt *ui;
};

#endif // PROJEKT_H
