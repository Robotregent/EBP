#include "leistungstraegerarea.h"
#include "leistungstraegerbox.h"
#include "ui_leistungstraegerarea.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDesktopWidget>
LeistungstraegerArea::LeistungstraegerArea(QWidget *parent) :
    QWidget(parent),
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

    if(availableWidth > 0)
    {
	int col = availableWidth / LeistungstraegerBox::fixedWidth;
	this->setBoxesInTable(col);
    }


}

LeistungstraegerArea::~LeistungstraegerArea()
{
    delete ui;
}

void LeistungstraegerArea::setBoxesInColumn()
{
    QVBoxLayout *layout = new QVBoxLayout();

    LeistungstraegerBox *tmp;

    for (int i = 0 ; i <6; ++i)
    {
	    tmp=new LeistungstraegerBox(this);
	    tmp->setTitle(tr("Test Test "));
	    layout->addWidget(tmp);
    }
    this->ui->scrollArea->widget()->setLayout(layout);
}
void LeistungstraegerArea::setBoxesInTable(int columns)
{
    QGridLayout *grid= new QGridLayout();

    LeistungstraegerBox *tmp;

    for (int i = 0 ; i <4; ++i)
    {
	for(int k = 0; k<columns; ++k)
	{
	    tmp=new LeistungstraegerBox(this);
	    tmp->setTitle(tr("Test Test "));
	    grid->addWidget(tmp,i,k);
	}
    }

    this->ui->scrollArea->widget()->setLayout(grid);

}
