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

/////////////////// wähle Mitarbeiter ///////////////////

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

/////////////////// wähle Bewohner ///////////////////

ChooseBwDialog::ChooseBwDialog(QList < QSharedPointer < ebp::Bewohner > > bwList, QString typ, QWidget *parent) :
    ChooseDialog(typ, parent)
{
    this->bwItemsList = QList < CustomListWidgetItem <  ebp::Bewohner >  *>();
    foreach ( QSharedPointer < ebp::Bewohner > bw, bwList )
    {
	bwItemsList.append(new CustomListWidgetItem<ebp::Bewohner>(bw,this->ui->listWidget));
    }
}

void ChooseBwDialog::on_buttonBox_accepted()
{
    int i = this->ui->listWidget->currentIndex().row();
    QSharedPointer< ebp::Bewohner > chosenBw = this->bwItemsList.at(i)->getCitem();
    if (!chosenBw.isNull())
	emit chosen(chosenBw);
}

/////////////////// wähle Wohngruppe ///////////////////

ChooseWgDialog::ChooseWgDialog(QList < QSharedPointer < ebp::Wohngruppe > > wgList, QString typ, QWidget *parent) :
    ChooseDialog(typ, parent)
{
    this->wgItemsList = QList < CustomListWidgetItem <  ebp::Wohngruppe >  *>();
    foreach ( QSharedPointer < ebp::Wohngruppe > wg, wgList )
    {
	wgItemsList.append(new CustomListWidgetItem<ebp::Wohngruppe>(wg,this->ui->listWidget));
    }
}

void ChooseWgDialog::on_buttonBox_accepted()
{
    int i = this->ui->listWidget->currentIndex().row();
    QSharedPointer< ebp::Wohngruppe > chosenWg = this->wgItemsList.at(i)->getCitem();
    if (!chosenWg.isNull())
	emit chosen(chosenWg);
}
