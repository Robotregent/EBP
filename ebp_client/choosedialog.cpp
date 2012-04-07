#include "choosedialog.h"
#include "ui_choosedialog.h"

ChooseDialog::ChooseDialog(QString typ, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDialog)
{
    ui->setupUi(this);
    this->ui->labelType->setText(typ);
}

ChooseDialog::~ChooseDialog()
{
    delete ui;
}

void ChooseDialog::on_buttonBox_accepted()
{
    // nothing
}

/////////////////// Choose a MA ///////////////////

ChooseMaDialog::ChooseMaDialog(QList < QSharedPointer < ebp::Mitarbeiter > > maList, QString typ, QWidget *parent) :
    ChooseDialog(typ, parent)
{
    this->maItemsList = QList < CustomListWidgetItem <  ebp::Mitarbeiter >  *>();
    foreach ( QSharedPointer < ebp::Mitarbeiter > ma, maList )
    {
	maItemsList.append(new CustomListWidgetItem<ebp::Mitarbeiter>(ma,this->ui->listWidget));
    }
}

void ChooseMaDialog::on_buttonBox_accepted()
{
    int i = this->ui->listWidget->currentIndex().row();
    QSharedPointer< ebp::Mitarbeiter > chosenMa = this->maItemsList.at(i)->getCitem();
    if (!chosenMa.isNull())
	emit chosen(chosenMa);
}
