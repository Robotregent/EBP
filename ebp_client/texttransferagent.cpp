#include "texttransferagent.h"
#include "ui_texttransferagent.h"
#include <EBPdb/Bewohner.hxx>
#include <QMessageBox>

TextTransferAgent::TextTransferAgent(QList<TextTransferInterface *>Interfaces, const SessionContext &context,QWidget *parent) :
    QFrame(parent),
    _context(context),
    ui(new Ui::TextTransferAgent)
{
    ui->setupUi(this);

    this->textInterfaces = Interfaces;

    foreach (QSharedPointer< ebp::Bewohner> bw, _context.allBewohner )
    {
	this->ui->bewohnerBox->addItem(bw->name(),qulonglong(bw->nummer()));
    }
    if(this->ui->bewohnerBox->count()>0)
	this->ui->bewohnerBox->setCurrentIndex(0);
}

TextTransferAgent::~TextTransferAgent()
{
    delete ui;
}

void TextTransferAgent::on_bewohnerBox_currentIndexChanged(int index)
{
    unsigned long int Bewohnernummer = (unsigned long int) this->ui->bewohnerBox->itemData(index).toULongLong();
    QSharedPointer< ebp::Bewohner > selectedBewohner;
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
	//ToDo:
	//Hier die Betreuungsplaung des Bewohners in die ComboBox laden
    }
}

void TextTransferAgent::on_pushButton_clicked()
{
    //ToDo:
    /*
      Den eigentlichen Texttransfer starten. Member textInterface hält die getText Methode
      den Text dann einfach in die entsprechende Betreuungsplanung des Bewohners stecken...
    */
    //Testballon
    foreach(TextTransferInterface *interface, textInterfaces)
    {
	TextTransferInformation info =interface->getSelectedText();
	if (!info.isEmpty)
	{
	    QMessageBox::information(this,"Texttransfer",interface->getSelectedText().textTransferFragment.toPlainText());
	}
	/*else
	    QMessageBox::information(this,"Texttransfer","Empty");*/
    }
}
void TextTransferAgent::registerNewInterface(TextTransferInterface *newInterface)
{
    this->textInterfaces.append(newInterface);
}
