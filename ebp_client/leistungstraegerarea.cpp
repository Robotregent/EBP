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

LeistungstraegerArea::LeistungstraegerArea(SessionContext &_context,QWidget *parent) :
    QWidget(parent),
    context(_context),
    ui(new Ui::LeistungstraegerArea)
{
    ui->setupUi(this);

    this->VLayouts.prepend(this->ui->VLayout);

    if(!context.curBewohner.isNull())
    {
	context.curBewohner->reload(context.curConnection);
	this->leistungstraeger = context.curBewohner->loadLeistungstraeger(context.curConnection);

    }

    //entscheiden, in wieviel Spalten die Boxen dargestellt werden
    QDesktopWidget desktop;
    QRect screen = desktop.availableGeometry(parent);
    int availableWidth = screen.width() - 280;
    if(availableWidth > 0)
    {
	columns = availableWidth / LeistungstraegerBox::fixedWidth;
	//Mehr Layouts erstellen, wenn Platz ist
	if(columns>1)
	{
	    QVBoxLayout *layout;
	    for (int i=0;i<columns-1;i++)
	    {
		layout = new QVBoxLayout();
		layout->insertStretch(0,1);
		//layout->insertSpacing(-1,5);
		this->ui->HLayout->insertLayout(i+1,layout);
		this->VLayouts.prepend(layout);
	    }
	}
    }
    this->initBoxes();
}

LeistungstraegerArea::~LeistungstraegerArea()
{
    delete ui;
}


void LeistungstraegerArea::addBox(QSharedPointer<ebp::Leistungstraeger> newLeistungstraeger)
{
    LeistungstraegerBox *aBox = new LeistungstraegerBox(context,this,newLeistungstraeger);

    this->boxes.append(aBox);

    QVBoxLayout *l =this->VLayouts.at(boxes.count()%columns);
    l->insertWidget(l->count()-1,aBox);
}

void LeistungstraegerArea::initBoxes()
{

    foreach (const QSharedPointer<ebp::Leistungstraeger> l, leistungstraeger)
    {
	addBox(l);
    }
}

void LeistungstraegerArea::on_neuerTraegerButton_clicked()
{
    QSharedPointer<ebp::Leistungstraeger> leer= QSharedPointer<ebp::Leistungstraeger>();
    addBox(leer);
}
/**
  * \brief Speichern aller Leistungsträger
  */
bool LeistungstraegerArea::saveContent()
{
    bool result = true;
    foreach (LeistungstraegerBox *b, boxes)
    {
	if(!b->saveContent())
	    result = false;
    }
    return result;
}
