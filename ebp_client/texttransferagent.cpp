#include "texttransferagent.h"
#include "ui_texttransferagent.h"
#include <EBPdb/Bewohner.hxx>
#include <QMessageBox>
#include "dokutypwrapper.h"

TextTransferAgent::TextTransferAgent(QList<TextTransferInterface *>Interfaces, const SessionContext &context,QWidget *parent) :
    QFrame(parent),
    _context(context),
    ui(new Ui::TextTransferAgent)
{
    ui->setupUi(this);

    this->textInterfaces = Interfaces;
    int i = 0, count = 0;
    foreach (const QSharedPointer< ebp::Bewohner> bw, _context.allBewohner )
    {
	if (bw->nummer()==_context.curBewohner->nummer())
	    count = i;
	this->ui->bewohnerBox->addItem(bw->name(),qulonglong(bw->nummer()));
	i++;
    }
    if(this->ui->bewohnerBox->count()>=count+1)
	this->ui->bewohnerBox->setCurrentIndex(count);
}

TextTransferAgent::~TextTransferAgent()
{
    delete ui;
}

void TextTransferAgent::on_bewohnerBox_currentIndexChanged(int index)
{
    unsigned long int Bewohnernummer = (unsigned long int) this->ui->bewohnerBox->itemData(index).toULongLong();

    foreach(QSharedPointer<ebp::Bewohner> bw, _context.allBewohner)
    {
	if(bw->nummer()==Bewohnernummer)
	{
	    selectedBewohner = bw;
	    break;
	}
    }
    if(!selectedBewohner.isNull())
    {
	this->ui->PlanungsBox->clear();
	dokus = selectedBewohner->loadDokumentationen(_context.curConnection);
	foreach (QSharedPointer < ebp::Dokumentation >  doku, dokus)
	{
	    this->ui->PlanungsBox->addItem(DokuTypMapper::toString(doku->typ()));
	}
    }
}

void TextTransferAgent::on_pushButton_clicked()
{
    foreach(TextTransferInterface *interface, textInterfaces)
    {
	TextTransferInformation info =interface->getSelectedText();
	if (!info.isEmpty)
	{
	    QString textfragment = dokus.at(this->ui->PlanungsBox->currentIndex())->erlaeuterungen();
	    textfragment += info.information + "\n";
	    textfragment += info.textTransferFragment.toPlainText()+"\n\n";
	    dokus.at(this->ui->PlanungsBox->currentIndex())->erlaeuterungen(textfragment);
	    dokus.at(this->ui->PlanungsBox->currentIndex())->update(_context.curConnection);
	    QMessageBox::information(this,tr("Texttransfer"),tr("Erfolgreich übertragen"));
	}
    }
}
void TextTransferAgent::registerNewInterface(TextTransferInterface *newInterface)
{
    this->textInterfaces.append(newInterface);
}



void TextTransferAgent::on_helpButton_clicked()
{
    QString text = tr("Wählen Sie als Ziel des Texttransfers den Bewohner und die Kategorie der Betreuungsplanung aus. \n\n");
    text +=tr("Markieren Sie die gewünschte Textstelle mit dem Cursor.\n\n");
    text +=tr("Drücken Sie auf Los!");
    QMessageBox::information(this,tr("Hilfe"),text);
}
