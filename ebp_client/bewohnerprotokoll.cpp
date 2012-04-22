#include "bewohnerprotokoll.h"
#include "ui_bewohnerprotokoll.h"
#include <QDebug>
#include "customtablewidgetitem.h"
#include "customlistwidgetitem.h"
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
    if(!curProtokoll.isNull())
    {
        result.isEmpty = true;
        if (this->ui->ProtokollText->textCursor().hasSelection())
        {
            result.information = tr("Texttransfer aus Protokoll vom ")+curProtokoll->datum().toString()+":";
            result.textTransferFragment = this->ui->ProtokollText->textCursor().selection();
            result.isEmpty = false;
        }
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
        curProtokoll->inhalt(this->ui->ProtokollText->toHtml());

	sync();

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
	bool editable = false;

	if(!context.curBewohner->bezugsbetreuer().isNull())
	    if(context.curBewohner->bezugsbetreuer()->login()== context.curMitarbeiter->login())
		editable = true;

        this->ui->NewProtokollDatum->setDate(QDate::currentDate());

	this->ui->NewProtokollButton->setEnabled(editable);
	this->ui->addTeilnehmer->setEnabled(editable);


	context.curBewohner->reload(context.curConnection);

	protokolle = context.curBewohner->loadProtokolle(context.curConnection);

	if (protokolle.count()>0)
	{
	    foreach ( const QSharedPointer<ebp::Protokoll> p , protokolle)
	    {
		QListWidgetItem *item = new QListWidgetItem(p->datum().toString(),this->ui->ProtokollListe);
		Q_UNUSED(item);
	    }

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
    this->ui->ProtokollText->setHtml(curProtokoll->inhalt());

    int rows = this->ui->tableWidget->rowCount();

    for (int i = 0; i < rows;i++ )
    {
	this->ui->tableWidget->removeRow(0);
    }

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
    if (currentRow < protokolle.count())
    {
	curProtokoll = protokolle.at(currentRow);

	schreiber = curProtokoll->loadSchreiber(context.curConnection);
	teilnehmer = curProtokoll->loadTeilnehmer(context.curConnection);

	fillFields();
    }
}

void BewohnerProtokoll::on_NewProtokollButton_clicked()
{
    QDateTime date = this->ui->NewProtokollDatum->dateTime();

    QSharedPointer< ebp::Protokoll > p = QSharedPointer<ebp::Protokoll>(new ebp::Protokoll(" ",date));

    if (p->create(context.curConnection))
    {
	ebp::Protokoll::linkBewohner(p,context.curBewohner);
	p->update(context.curConnection);
	context.curBewohner->reload(context.curConnection);

	protokolle.append(p);

	QListWidgetItem *item = new QListWidgetItem(date.toString(),this->ui->ProtokollListe);
	Q_UNUSED(item);

        this->ui->ProtokollListe->setCurrentRow(this->ui->ProtokollListe->count()-1);

    }
    this->ui->NewProtokollDatum->setDate(QDate::currentDate());
}

void BewohnerProtokoll::syncSchreiber(QSharedPointer<ebp::Mitarbeiter> s)
{
    foreach ( const QSharedPointer<ebp::Mitarbeiter> ma, schreiber)
    {
	if (ma->login()==s->login())
	    return;
    }
    ebp::Protokoll::linkSchreiber(curProtokoll,s);
    foreach ( const QSharedPointer<ebp::Mitarbeiter> ma, teilnehmer)
    {
	if (ma->login()==s->login())
	    ebp::Protokoll::unlinkTeilnehmer(curProtokoll,s);
    }
}
void BewohnerProtokoll::syncTeilnehmer(QSharedPointer<ebp::Mitarbeiter> t)
{
    foreach ( const QSharedPointer<ebp::Mitarbeiter> ma, teilnehmer)
    {
	if (ma->login()==t->login())
	    return;
    }
    ebp::Protokoll::linkTeilnehmer(curProtokoll,t);
    foreach ( const QSharedPointer<ebp::Mitarbeiter> ma, schreiber)
    {
	if (ma->login()==t->login())
	    ebp::Protokoll::unlinkSchreiber(curProtokoll,t);
    }
}
void BewohnerProtokoll::sync()
{
    QTableWidgetItem *curFlag;
    CustomTableWidgetItem<ebp::Mitarbeiter> *curMa;
    for (int i = 0 ; i < this->ui->tableWidget->rowCount(); i++)
    {
	curFlag = this->ui->tableWidget->item(i,0);
	curMa =(CustomTableWidgetItem<ebp::Mitarbeiter> *) this->ui->tableWidget->item(i,1);
	if (curFlag->checkState()==Qt::Checked)
	{
	    //Schreiber
	    syncSchreiber(curMa->getCitem());
	}
	else
	{
	    //Teilnehmer
	    syncTeilnehmer(curMa->getCitem());
	}
    }
}
