#include "bewohnerprotokoll.h"
#include "ui_bewohnerprotokoll.h"
#include <QDebug>

BewohnerProtokoll::BewohnerProtokoll(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::BewohnerProtokoll)
{
    ui->setupUi(this);
    this->ui->tableWidget->setRowCount(1);

    //initialize Header
    QTableWidgetItem *writer = new QTableWidgetItem(QIcon(":/costumer/protokollf.png"),tr(""));
    writer->setToolTip(tr("Wer ist Protokollführer?"));
    this->ui->tableWidget->setHorizontalHeaderItem(0,writer);

    QTableWidgetItem *participant = new QTableWidgetItem(tr("Teilnehmer"));
    participant->setTextAlignment(Qt::AlignLeft);
    participant->setToolTip(tr("Wer hat an der Besprechung teilgenommen?"));
    this->ui->tableWidget->setHorizontalHeaderItem(1,participant);

    this->ui->tableWidget->horizontalHeader()->setResizeMode(0,QHeaderView::ResizeToContents);


    QTableWidgetItem *testEins = new QTableWidgetItem(tr(""));
    testEins->setFlags(testEins->flags()|Qt::ItemIsUserCheckable);
    testEins->setCheckState(Qt::Unchecked);
    this->ui->tableWidget->setItem(0,0,testEins);

    QTableWidgetItem *testZwei = new QTableWidgetItem(tr(""));
    this->ui->tableWidget->setItem(0,1,testZwei);

    //qDebug() << "Protokoll";
}

BewohnerProtokoll::~BewohnerProtokoll()
{
    delete ui;
}

void BewohnerProtokoll::on_addTeilnehmer_clicked()
{
    //qDebug()<<this->ui->tableWidget->rowCount();
    this->ui->tableWidget->insertRow(this->ui->tableWidget->rowCount());

    //qDebug()<<this->ui->tableWidget->rowCount();
    QTableWidgetItem *tmp = new QTableWidgetItem(tr(""));
    tmp->setFlags(tmp->flags()|Qt::ItemIsUserCheckable);
    tmp->setCheckState(Qt::Unchecked);
    this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount()-1,0,tmp);

}

TextTransferInformation BewohnerProtokoll::getSelectedText()
{
    TextTransferInformation result;
    result.isEmpty = true;
    if (this->ui->textBrowser->textCursor().hasSelection())
    {
	result.information = "Texttransfer aus Protokoll vom "+this->ui->dateTimeEdit->dateTime().toString();
	result.textTransferFragment = this->ui->textBrowser->textCursor().selection();
	result.isEmpty = false;
    }
    return result;
}