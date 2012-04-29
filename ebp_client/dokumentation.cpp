#include "dokumentation.h"
#include "ui_dokumentation.h"

Dokumentation::Dokumentation(SessionContext &context, ebp::Dokumentation::Typ typ, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dokumentation),
    curContext(context)
{
    ui->setupUi(this);
    QString name;
    switch(typ)
    {
    case ebp::Dokumentation::einkaufen:
        name = tr("Einkaufen");
	break;
    case ebp::Dokumentation::waeschepflege:
        name = tr("Waschpflege");
	break;
    case ebp::Dokumentation::koerperpflege:
        name = tr("Körperpflege");
	break;
    case ebp::Dokumentation::aufstehenUndZuBettgehen:
        name = tr("Aufstehen und zu Bett gehen");
	break;
    case ebp::Dokumentation::partnerschaften:
        name = tr("In Partnerschaften");
	break;
    case ebp::Dokumentation::freundschaften:
        name = tr("Freundschaften / Peergroups");
	break;
    default:
        name = tr("Betreuung");
	break;
    }
    this->ui->Name->setText(name);

    QList< QSharedPointer< ebp::Dokumentation > > allDokus = curContext.curBewohner->loadDokumentationen(curContext.curConnection);
    foreach (QSharedPointer< ebp::Dokumentation > doku, allDokus)
    {
	if (doku->typ() == typ)
	{
	    curDoku = doku;
	    continue;
	}
    }
    if (!curDoku.isNull())
    {
	int index=0;
	switch(curDoku->einstufung())
	{
	case ebp::Dokumentation::bekommeKeineHilfe:
	    index = 0;
	    break;
	case ebp::Dokumentation::bekommeBeratung:
	    index = 1;
	    break;
	case ebp::Dokumentation::bekommeAssistenz:
	    index = 2;
	case ebp::Dokumentation::machtMitarbeiter:
	    index = 3;
	    break;
	case ebp::Dokumentation::istWichtig:
	    index = 4;
	    break;
	case ebp::Dokumentation::willLernen:
	    index = 5;
	    break;
	default:
	    index = 0;
	    break;
	}
	this->ui->hilfebedarfComboBox->setCurrentIndex(index);

        this->ui->Ziele->setHtml(curDoku->ziele());

        this->ui->Erlaeuterungen->setHtml(curDoku->erlaeuterungen());
    }


}

Dokumentation::~Dokumentation()
{
    delete ui;
}

bool Dokumentation::saveContent()
{
    bool result = false;
    if(!curDoku.isNull())
    {
        ebp::Dokumentation::Einstufung einstufung;

        switch(this->ui->hilfebedarfComboBox->currentIndex())
        {
        case 0:
            einstufung = ebp::Dokumentation::bekommeKeineHilfe;
            break;
        case 1:
            einstufung = ebp::Dokumentation::bekommeBeratung;
            break;
        case 2:
            einstufung = ebp::Dokumentation::bekommeAssistenz;
        case 3:
            einstufung = ebp::Dokumentation::machtMitarbeiter;
            break;
        case 4:
            einstufung = ebp::Dokumentation::istWichtig;
            break;
        case 5:
            einstufung = ebp::Dokumentation::willLernen;
            break;
        default:
            einstufung = ebp::Dokumentation::bekommeKeineHilfe;
            break;
        }
        this->curDoku->einstufung(einstufung);

        this->curDoku->ziele(this->ui->Ziele->toHtml());

        this->curDoku->erlaeuterungen(this->ui->Erlaeuterungen->toHtml());
        if(this->curDoku->update(curContext.curConnection))
            result = true;
        else
            result = false;
    }
    return result;
}

void Dokumentation::on_hilfebedarfComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    pendingChanges = true;
}
bool Dokumentation::hasPendingChanges()
{
    bool result = pendingChanges;
    if (this->ui->Erlaeuterungen->document()->isUndoAvailable())
        result = true;
    if (this->ui->Ziele->document()->isUndoAvailable())
        result = true;

    return result;
}
