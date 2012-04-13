#include "bewohnerprotokoll.h"
#include "ui_bewohnerprotokoll.h"
#include <QDebug>
#include "customtablewidgetitem.h"

BewohnerProtokoll::BewohnerProtokoll(SessionContext &_conntext, QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::BewohnerProtokoll),
    context(_conntext)
{
    ui->setupUi(this);

    this->maDialog =NULL;

    initHeader();

    init();
}

BewohnerProtokoll::~BewohnerProtokoll()
{
    if(this->maDialog!=NULL)
    {
	maDialog->disconnect(this);
	delete maDialog;
    }

    delete ui;
}

void BewohnerProtokoll::on_addTeilnehmer_clicked()
{
    this->maDialog->show();

}

TextTransferInformation BewohnerProtokoll::getSelectedText()
{
    TextTransferInformation result;
    result.isEmpty = true;
    if (this->ui->ProtokollText->textCursor().hasSelection())
    {
	result.information = "Texttransfer aus Protokoll vom "+this->ui->ProtokollDatum->dateTime().toString()+":";
	result.textTransferFragment = this->ui->ProtokollText->textCursor().selection();
	result.isEmpty = false;
    }
    return result;
}

/**
  * \brief Speichert das aktuelle Protokoll
  */
bool BewohnerProtokoll::saveContent()
{
    bool result = false;

    if (!curProtokoll.isNull())
    {
	curProtokoll->inhalt(this->ui->ProtokollText->toPlainText());

	curProtokoll->datum(this->ui->ProtokollDatum->date());

	ebp::Protokoll::linkBewohner(curProtokoll,context.curBewohner);

	if (curProtokoll->update(context.curConnection))
	    result = true;
    }

    return result;
}
void BewohnerProtokoll::initHeader()
{
    //initialize Header
    QTableWidgetItem *writer = new QTableWidgetItem(QIcon(":/costumer/protokollf.png"),tr(""));
    writer->setToolTip(tr("Wer ist Protokollführer?"));
    this->ui->tableWidget->setHorizontalHeaderItem(0,writer);
    QTableWidgetItem *participant = new QTableWidgetItem(tr("Teilnehmer"));
    participant->setTextAlignment(Qt::AlignLeft);
    participant->setToolTip(tr("Wer hat an der Besprechung teilgenommen?"));
    this->ui->tableWidget->setHorizontalHeaderItem(1,participant);
    this->ui->tableWidget->horizontalHeader()->setResizeMode(0,QHeaderView::ResizeToContents);
}

void BewohnerProtokoll::init()
{
    this->maDialog = new ChooseMaDialog(ebp::Mitarbeiter::loadAll(context.curConnection),tr("Mitarbeiter wählen:"),this);
    QObject::connect(maDialog,SIGNAL(chosen(QSharedPointer<ebp::Mitarbeiter>)),SLOT(chosenMitarbeiter(QSharedPointer<ebp::Mitarbeiter>)));

    if (!context.curBewohner.isNull())
    {
	context.curBewohner->reload(context.curConnection);

	protokolle = context.curBewohner->loadProtokolle(context.curConnection);

	if (protokolle.count()>0)
	{
	    curProtokoll =protokolle.first();
	    schreiber = curProtokoll->loadSchreiber(context.curConnection);
	    teilnehmer = curProtokoll->loadTeilnehmer(context.curConnection);

	    fillFields();
	}
    }
}

void BewohnerProtokoll::chosenMitarbeiter(QSharedPointer<ebp::Mitarbeiter> chosenMa)
{
    // Check item
    this->ui->tableWidget->insertRow(this->ui->tableWidget->rowCount());
    QTableWidgetItem *tmp = new QTableWidgetItem(tr(""));
    tmp->setFlags(tmp->flags()|Qt::ItemIsUserCheckable);
    tmp->setCheckState(Qt::Unchecked);
    this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount()-1,0,tmp);

    // Ma
    CustomTableWidgetItem<ebp::Mitarbeiter> *item = new CustomTableWidgetItem<ebp::Mitarbeiter>(chosenMa);
    this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount()-1,1,item);


}
void BewohnerProtokoll::fillFields()
{
    this->ui->ProtokollText->setText(curProtokoll->inhalt());
    this->ui->ProtokollDatum->setDate(curProtokoll->datum());

    if(schreiber.count()>0)
	fillParticipants(schreiber,Qt::Checked);

    if(teilnehmer.count()>0)
	fillParticipants(teilnehmer,Qt::Unchecked);
}

void BewohnerProtokoll::fillParticipants(QList< QSharedPointer < ebp::Mitarbeiter > > ma, Qt::CheckState state)
{
    QTableWidgetItem *tmp;
    CustomTableWidgetItem<ebp::Mitarbeiter> *item;
    foreach (QSharedPointer < ebp::Mitarbeiter > m , ma)
    {
	this->ui->tableWidget->insertRow(this->ui->tableWidget->rowCount());
	tmp = new QTableWidgetItem(tr(""));
	tmp->setFlags(tmp->flags()|Qt::ItemIsUserCheckable);
	tmp->setCheckState(state);
	this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount()-1,0,tmp);

	item = new CustomTableWidgetItem<ebp::Mitarbeiter>(m);
	this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount()-1,1,item);
    }
}

void BewohnerProtokoll::on_ProtokollListe_currentRowChanged(int currentRow)
{
    if (currentRow >= protokolle.count()-1)
    {
	curProtokoll = protokolle.at(currentRow);

	fillFields();
    }
}
