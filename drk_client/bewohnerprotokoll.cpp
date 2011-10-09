#include "bewohnerprotokoll.h"
#include "ui_bewohnerprotokoll.h"
#include <QDebug>

BewohnerProtokoll::BewohnerProtokoll(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::BewohnerProtokoll)
{
    ui->setupUi(this);

    this->ui->tableWidget->setRowCount(14);
    //initialize Header
    QTableWidgetItem *writer = new QTableWidgetItem(QIcon(":/custumer/protokollf.png"),tr(""));
    writer->setToolTip(tr("Wer ist Protokollführer?"));
    this->ui->tableWidget->setHorizontalHeaderItem(0,writer);

    QTableWidgetItem *participant = new QTableWidgetItem(QIcon(":/custumer/Teilnehmer.png"),tr("Teilnehmer"));
    participant->setTextAlignment(Qt::AlignLeft);
    participant->setToolTip(tr("Wer hat an der Besprechung teilgenommen?"));
    this->ui->tableWidget->setHorizontalHeaderItem(1,participant);

    QTableWidgetItem *testEins = new QTableWidgetItem(tr(""));
    testEins->setFlags(testEins->flags()|Qt::ItemIsUserCheckable);
    testEins->setCheckState(Qt::Unchecked);
    this->ui->tableWidget->setItem(0,0,testEins);

    QTableWidgetItem *testZwei = new QTableWidgetItem(tr("Testmitarbeiter"));
    this->ui->tableWidget->setItem(0,1,testZwei);

    qDebug() << "Protokoll";
}

BewohnerProtokoll::~BewohnerProtokoll()
{
    delete ui;
}
