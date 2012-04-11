#include "leistungstraegerarea.h"
#include "leistungstraegerbox.h"
#include "ui_leistungstraegerarea.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDesktopWidget>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Leistungstraeger.hxx>
#include <EBPdb/Betreuung.hxx>
#include <math.h>
#include <QMessageBox>

LeistungstraegerArea::LeistungstraegerArea(const SessionContext &context,QWidget *parent) :
    QWidget(parent),
    con(context),
    ui(new Ui::LeistungstraegerArea)
{
    ui->setupUi(this);

    //Widget für die LeistungsträgerBoxen
    QWidget *wid = new QWidget(this);
    this->ui->scrollArea->setWidget(wid);

    //entscheiden, in wieviel Spalten die Boxen dargestellt werden
    QDesktopWidget desktop;
    QRect screen = desktop.availableGeometry(parent);
    int availableWidth = screen.width() - 280;
    grid= new QGridLayout();
    entryCount=0;
    if(availableWidth > 0)
    {
        col = availableWidth / LeistungstraegerBox::fixedWidth;
        this->setBoxesInTable(col);
    }


}

LeistungstraegerArea::~LeistungstraegerArea()
{
    delete ui;
}

void LeistungstraegerArea::setBoxesInColumn()
{
  /*  QVBoxLayout *layout = new QVBoxLayout();

    LeistungstraegerBox *tmp;

    for (int i = 0 ; i <6; ++i)
    {
            tmp=new LeistungstraegerBox(con,this,bewohner_leistungstraeger.at((i*columns)+k));
            tmp->setTitle(tr("Test Test "));
            layout->addWidget(tmp);
    }
    this->ui->scrollArea->widget()->setLayout(layout);*/
}

void LeistungstraegerArea::setBoxesInTable(int columns)
{
    grid= new QGridLayout();
    LeistungstraegerBox *tmp;
    if (con.curBewohner!=NULL)
    {
        con.curBewohner->reload(con.curConnection);
        this->bewohner_leistungstraeger=con.curBewohner->loadLeistungstraeger(con.curConnection);
        if (bewohner_leistungstraeger.isEmpty())
            return;
        entryCount=bewohner_leistungstraeger.count();
        for (int i = 0 ; i <(entryCount/columns); ++i)
        {
            for(int k = 0; k<columns; ++k)
            {
                tmp=new LeistungstraegerBox(con,this,bewohner_leistungstraeger.at((i*columns)+k));
                tmp->setTitle(bewohner_leistungstraeger.at((i*columns)+k)->name());
                grid->addWidget(tmp,i,k);
            }
        }
    }

}
void LeistungstraegerArea::on_pushButton_clicked()
{
    if(ui->scrollArea->layout()!=0)
        delete(ui->scrollArea->layout());
    LeistungstraegerBox *tmp;
    QSharedPointer< ebp::Leistungstraeger > tmpPointer(new ebp::Leistungstraeger("Neuer Leistungsträger"));
   // QString str;
   // str.append(QString("%1%2").arg(entryCount/col).arg(entryCount));
   // QMessageBox::about(this, tr("test"),str);
    tmp=new LeistungstraegerBox(con,this,tmpPointer);
    tmp->setTitle(tr("Neuer Leistungsträger"));

    if(entryCount==0)
        grid->addWidget(tmp,0,0);
    grid->addWidget(tmp,entryCount/col,entryCount%col);
    ui->scrollArea->setLayout(grid);
    entryCount++;
}
