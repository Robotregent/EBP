#include "zuordnung.h"
#include "ui_zuordnung.h"

Zuordnung::Zuordnung(QAbstractTableModel *_model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zuordnung),
    model(_model)
{
    ui->setupUi(this);
}

Zuordnung::~Zuordnung()
{
    delete ui;
}

void Zuordnung::on_pushButton_clicked()
{

}
