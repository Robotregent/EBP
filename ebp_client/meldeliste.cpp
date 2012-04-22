#include "meldeliste.h"
#include "ui_meldeliste.h"
#include "customtablewidgetitem.h"
#include <QDate>
#include <QTableWidget>
#include <QString>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Abwesenheit.hxx>
#include <QPoint>
#include <QMessageBox>
#include <QFileDialog>

MeldeListe::MeldeListe(const SessionContext &_curContext,QWidget *parent) :
    QWidget(parent),
    curContext(_curContext),
    ui(new Ui::MeldeListe)
{
    ui->setupUi(this);
    QDate today;

    this->ui->curDay->setDate(today.currentDate());
    this->ui->from->setDate(today.currentDate());
    this->ui->to->setDate(today.currentDate());
    if (curContext.curWohngruppe!=NULL)
    {
        createList();
        QObject::connect(this->ui->tableWidget, SIGNAL(cellClicked(int,int)),this,SLOT(stateChanged(int,int)));
        QObject::connect(this->ui->curDay, SIGNAL(dateChanged(QDate)),this,SLOT(changeList()));
    }
}

MeldeListe::~MeldeListe()
{
    delete ui;
}

void MeldeListe::createList()
{
    curContext.curWohngruppe->reload(curContext.curConnection);
    curWgBewohner = curContext.curWohngruppe->loadBewohner(curContext.curConnection);
    QTableWidgetItem *tmp;
    CustomTableWidgetItem<ebp::Bewohner> *item;
    QTableWidgetItem *abwItem;
    QTableWidgetItem *grundItem;
    QString grund;

    foreach (QSharedPointer < ebp::Bewohner > tmpBewohner , curWgBewohner)
    {
        if ((tmpBewohner->seit().toString("yyyyMMdd").toInt())<=(this->ui->curDay->date().toString("yyyyMMdd").toInt()))
        {
            this->ui->tableWidget->insertRow(this->ui->tableWidget->rowCount());
            tmp = new QTableWidgetItem(tr(""));
            tmp->setFlags(tmp->flags()|Qt::ItemIsUserCheckable);
            this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount()-1,0,tmp);
            item = new CustomTableWidgetItem<ebp::Bewohner>(tmpBewohner);
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount()-1,0,item);
            abwItem=new QTableWidgetItem("Ja");
            abwItem->setFlags(Qt::ItemIsUserCheckable);
            abwItem->setCheckState(Qt::Checked);
            abwItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            grund = isAbwesend(tmpBewohner,this->ui->curDay->date());
            if (!grund.trimmed().isEmpty())
            {
                abwItem->setText(tr("Nein"));
                abwItem->setCheckState(Qt::Unchecked);
            }
            this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount()-1,1,abwItem);
            grundItem=new QTableWidgetItem(grund);
            this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount()-1,2,grundItem);

        }
    }
}

QString MeldeListe::isAbwesend(QSharedPointer < ebp::Bewohner > tmpBewohner,QDate tmpDate)
{
    QList <QSharedPointer< ebp::Abwesenheit > > tmpAbwesenheit = tmpBewohner->loadAbwesenheiten(curContext.curConnection);
    for (int i=0; i < tmpAbwesenheit.count(); i++)
    {
        if (tmpDate == tmpAbwesenheit.at(i)->tag())
            return tmpAbwesenheit.at(i)->grund();
    }
    return "";
}

void MeldeListe::changeList()
{
    int count = this->ui->tableWidget->rowCount();
    for (int i=0; i< count;i++)
    {
        this->ui->tableWidget->removeRow(count-1-i);
    }
    createList();
}

bool MeldeListe::saveContent()
{
    bool exists = false;
    if (this->ui->tableWidget->rowCount() >0)
    {
        for (int i = 0; i< this->ui->tableWidget->rowCount();i++)
        {
            this->ui->tableWidget->setCurrentCell(i,0);
            if (this->ui->tableWidget->item(i,1)->checkState()==Qt::Unchecked)
            {
                exists = false;
                QList <QSharedPointer< ebp::Abwesenheit > > tmpAbwesenheit = curWgBewohner.at(i)->loadAbwesenheiten(curContext.curConnection);
                for (int j=0; j < tmpAbwesenheit.count(); j++)
                {
                    if (this->ui->curDay->date() == tmpAbwesenheit.at(j)->tag())
                    {
                        if (tmpAbwesenheit.at(j)->grund().trimmed()!=this->ui->tableWidget->item(i,2)->text().trimmed())
                        {
                            tmpAbwesenheit.at(j)->grund(this->ui->tableWidget->item(i,2)->text());
                            tmpAbwesenheit.at(j)->update(curContext.curConnection);
                        }
                        exists = true;
                    }
                }

                if (!exists)
                {
                    createAbwesenheit(curWgBewohner.at(i),this->ui->tableWidget->item(i,2)->text());
                }
            }
            else
            {
                QList <QSharedPointer< ebp::Abwesenheit > > tmpAbwesenheit = curWgBewohner.at(i)->loadAbwesenheiten(curContext.curConnection);
                for (int j=0; j < tmpAbwesenheit.count(); j++)
                {
                    if (this->ui->curDay->date() == tmpAbwesenheit.at(j)->tag())
                    {
                        QSharedPointer<ebp::Bewohner> tempB = curContext.allBewohner.at(curContext.allBewohner.indexOf(curWgBewohner.at(i)));
                        ebp::Abwesenheit::unlinkBewohner(tmpAbwesenheit.operator [](j),tempB);
                        tmpAbwesenheit.at(j)->remove(curContext.curConnection);
                        tmpAbwesenheit.at(j)->update(curContext.curConnection);
                        tmpAbwesenheit.removeAt(j);
                        tempB->reload(curContext.curConnection);

                    }
                }
            }
        }
        return true;
    }
    return false;
}

/*
void MeldeListe::exportFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "~/Documents",
                                tr("File (*.txt)"));
}
*/
void MeldeListe::stateChanged(int row, int col)
{
    if (col == 1) //check if Anwesend field
    {
        QTableWidgetItem *item = this->ui->tableWidget->item(row,col);
        if (item->checkState() == Qt::Checked)
        {
            item->setCheckState(Qt::Unchecked);
            item->setText(tr("Nein"));
        }
        else
        {
            item->setCheckState(Qt::Checked);
            item->setText(tr("Ja"));
            QTableWidgetItem *item2 = this->ui->tableWidget->item(row,col+1);
            item2->setText("");
        }
    }
}


void MeldeListe::createAbwesenheit(QSharedPointer <ebp::Bewohner> abwBewohner,QString tmpGrund)
{
    QSharedPointer< ebp::Abwesenheit > tmpAbwesenheit(new ebp::Abwesenheit(this->ui->curDay->date(),tmpGrund));
    tmpAbwesenheit->create(curContext.curConnection);
    QSharedPointer<ebp::Bewohner> tempB = curContext.allBewohner.at(curContext.allBewohner.indexOf(abwBewohner));
    ebp::Abwesenheit::linkBewohner(tmpAbwesenheit,tempB);
    bewohner_abwesenheit.append(tmpAbwesenheit);
    tmpAbwesenheit->update(this->curContext.curConnection);
    tempB->reload(curContext.curConnection);
}
