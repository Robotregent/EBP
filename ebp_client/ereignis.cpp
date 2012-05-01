#include "ereignis.h"
#include "ui_ereignis.h"
#include "newereignisdialog.h"
#include <QDebug>
#include <EBPdb/Wohngruppenereignis.hxx>
Ereignis::Ereignis(SessionContext _context, TextTransferAgent *agent,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ereignis),
    transferAgent(agent),
    context(_context)
{
    ui->setupUi(this);
    QWidget *puffer = new QWidget(this);
    pufferLayout = new QVBoxLayout();
    pufferLayout->setMargin(0);
    pufferLayout->setSpacing(0);
    puffer->setLayout(pufferLayout);
    this->ui->scrollArea->setWidget(puffer);
    this->ui->dateTimeEdit->setDate(QDate::currentDate());

    initEreignisse();
}

Ereignis::~Ereignis()
{
    delete ui;
    delete pufferLayout;
}

void Ereignis::on_pushButton_clicked()
{
    //Dialog öffnen

    EreignisInformation info;
    info.isEmpty = true;
    NewEreignisDialog ereignisDialog(&info,this);

    if(!context.curMitarbeiter.isNull()&&!context.curWohngruppe.isNull())
    {
	if(ereignisDialog.exec()==1)
	{
	    if(!info.isEmpty)
	    {
		EinzelEreignis *tmp=new EinzelEreignis(this);

		QSharedPointer< ebp::Wohngruppenereignis > newEreignis = QSharedPointer< ebp::Wohngruppenereignis >(new ebp::Wohngruppenereignis(info.time,info.EreignisText));

		if(newEreignis->create(context.curConnection))
		{
		    qDebug()<<"Erfolgreich angelegt";
		    ebp::Wohngruppenereignis::linkSchreiber(newEreignis,context.curMitarbeiter);
		    ebp::Wohngruppenereignis::linkWohngruppe(newEreignis,context.curWohngruppe);

		    if (newEreignis->update(context.curConnection))
		    {
			qDebug()<<"Erfolgreich upgedated";
			tmp->setContent(info.time,context.curMitarbeiter->name(),info.EreignisText);

			//Neue Eingabe anzeigen
			this->EreignisListe.prepend(tmp);
			this->pufferLayout->insertWidget(0,tmp);

			//TextransferInterface registrieren
			this->transferAgent->registerNewInterface(tmp);

			context.curMitarbeiter->reload(context.curConnection);
			context.curWohngruppe->reload(context.curConnection);
		    }
		    else
			qDebug()<<"Fehlschlag beim updaten";



		}
		else
		    qDebug()<<"Fehlschlag beim angelegen";


	    }
	}
    }

}

void Ereignis::initEreignisse()
{
    QList < QSharedPointer < ebp::Wohngruppenereignis > > wgEreignisse = context.curWohngruppe->loadEreignisse(context.curConnection);

    foreach (QSharedPointer < ebp::Wohngruppenereignis > e, wgEreignisse)
    {
	EinzelEreignis *tmp=new EinzelEreignis(this);
	QString mitarbeiter="";
	foreach ( const QSharedPointer < ebp::Mitarbeiter > ma, e->loadSchreiber(context.curConnection))
	{
	    mitarbeiter+=ma->name()+";";
	}

	tmp->setContent(e->zeitpunkt(),mitarbeiter,e->text());
	this->EreignisListe.prepend(tmp);
	this->pufferLayout->insertWidget(0,tmp);

	//TextransferInterface registrieren
	this->transferAgent->registerNewInterface(tmp);
    }
}

void Ereignis::on_setFilterButton_clicked()
{
    QDateTime filter = this->ui->dateTimeEdit->dateTime();
    foreach (EinzelEreignis *e, EreignisListe)
    {
	if ( e->getDatum()==filter)
	    e->setVisible(true);
	else
	    e->setVisible(false);
    }
}

void Ereignis::on_clearFilterButton_clicked()
{
    foreach (EinzelEreignis *e, EreignisListe)
    {
	e->setVisible(true);
    }
    this->ui->dateTimeEdit->setDate(QDate::currentDate());
}
