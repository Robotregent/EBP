#ifndef PROJEKT_H
#define PROJEKT_H

#include <QWidget>

namespace Ui {
    class Projekt;
}

class Projekt : public QWidget
{
    Q_OBJECT

public:
    explicit Projekt(QWidget *parent = 0);
    ~Projekt();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Projekt *ui;
};

#endif // PROJEKT_H
