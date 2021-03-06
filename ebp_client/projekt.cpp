#include "projekt.h"
#include "ui_projekt.h"
#include "choosedialog.h"
#include "customlistwidgetitem.h"
#include <QDebug>

Projekt::Projekt(SessionContext &_curContext, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Projekt),
    curContext(_curContext)
{
    ui->setupUi(this);
    this->ui->alleProjekteLabel->setMinimumHeight(this->ui->betreuenderMitarbeiterLabel->height());

    init();
}

Projekt::~Projekt()
{
    if ( maDialog != NULL)
    {
        maDialog->disconnect(this);
        delete maDialog;
    }
    delete ui;
}

/**
  * \brief Neues Projekt anlegen
  */
void Projekt::on_pushButton_clicked()
{
    QString name = this->ui->NewProjektLineEdit->text() ;

    if (!name.isEmpty() && !name.isNull())
    {
        QSharedPointer< ebp::Projekt > project = QSharedPointer< ebp::Projekt >(new ebp::Projekt( name,"","",QDate::currentDate(),QDate::currentDate()));
        project->create(curContext.curConnection);
        ebp::Projekt::linkBewohner(project,curContext.curBewohner);
        if(project->update(curContext.curConnection))
        {
            projects.append(project);

            new CustomListWidgetItem<ebp::Projekt>(project,this->ui->listWidget);

            this->ui->listWidget->setCurrentRow(this->ui->listWidget->count()-1);

            this->ui->beginnDateEdit->setDate(QDate::currentDate());
            this->ui->endeDateEdit->setDate(QDate::currentDate());
            pendingChanges = true;
        }

        this->ui->NewProjektLineEdit->clear();
    }


}
/**
  * \brief Dialog öffnen, um neuen Mitarbeiter zu wählen.
  */
void Projekt::on_pushButton_2_clicked()
{
    maDialog->show();
}
/**
  * \brief Implementiert das TextTransferInterface und gibt den selektierten Text zurück.
  */
TextTransferInformation Projekt::getSelectedText()
{
    TextTransferInformation result;
    result.isEmpty = true;

    if(this->ui->zieleEdit->textCursor().hasSelection())
    {
        result.information ="\n"+ QDateTime::currentDateTime().toString(Qt::SystemLocaleShortDate)+ tr(" Projektziele:");
        result.textTransferFragment= this->ui->zieleEdit->textCursor().selection();
        result.isEmpty = false;

    }
    else if (this->ui->beschreibungEdit->textCursor().hasSelection())
    {
        result.information = "\n"+ QDateTime::currentDateTime().toString(Qt::SystemLocaleShortDate)+ tr(" Projektbeschreibung:");
        result.textTransferFragment = this->ui->beschreibungEdit->textCursor().selection();
        result.isEmpty = false;
    }
    return result;
}

void Projekt::setChosenMa(QSharedPointer<ebp::Mitarbeiter> chosenMa)
{
    this->potentiallyNewMa = chosenMa;
    this->ui->betreuenderMitarbeiterLineEdit->setText(chosenMa->name());
    pendingChanges = true;
}

void Projekt::setProjekt()
{
    QString maName="";

    QList < QSharedPointer < ebp::Mitarbeiter > > list = this->curProject->loadVerantwortliche(this->curContext.curConnection);
    if (list.count()>0)
        maName = list.first()->name();

    this->ui->betreuenderMitarbeiterLineEdit->setText(maName);

    this->ui->beginnDateEdit->setDate(this->curProject->beginn());

    this->ui->endeDateEdit->setDate(this->curProject->ende());

    this->ui->zieleEdit->setHtml(this->curProject->ziele());

    this->ui->beschreibungEdit->setHtml(this->curProject->beschreibung());

    pendingChanges = false;
}

void Projekt::on_listWidget_currentRowChanged(int currentRow)
{
    if (projects.count()>=(currentRow))
    {
        if(this->hasPendingChanges())
        {
            if(editable)
                this->saveContent();
        }
        pendingChanges = false;
        this->curProject = this->projects.at(currentRow);
        this->setProjekt();
    }
}

bool Projekt::saveContent()
{
    bool result = false;

    if(!curProject.isNull())
    {
        if (!potentiallyNewMa.isNull())
        {
            QList < QSharedPointer < ebp::Mitarbeiter > > list = this->curProject->loadVerantwortliche(this->curContext.curConnection);
            if (list.count()>0)
            {
                ebp::Projekt::unlinkVerantwortlicher(curProject,list.first());
            }

            ebp::Projekt::linkVerantwortlicher(curProject,potentiallyNewMa);
        }

        this->curProject->beginn(this->ui->beginnDateEdit->date());

        this->curProject->ende(this->ui->endeDateEdit->date());

        this->curProject->ziele(this->ui->zieleEdit->toHtml());

        this->curProject->beschreibung(this->ui->beschreibungEdit->toHtml());

        if (this->curProject->update(curContext.curConnection) )
        {
            result = true;
            curContext.curBewohner->reload(curContext.curConnection);
        }
    }
    return result;
}
void Projekt::init()
{

    if(!this->curContext.curBewohner.isNull())
    {
        editable = false;
        if(!curContext.curBewohner->bezugsbetreuer().isNull())
            if(curContext.curBewohner->bezugsbetreuer()->login()== curContext.curMitarbeiter->login())
                editable = true;

        this->ui->pushButton->setEnabled(editable);
        this->ui->pushButton_2->setEnabled(editable);

        projects =  this->curContext.curBewohner->loadProjekte(curContext.curConnection);
        foreach (QSharedPointer< ebp::Projekt> p, projects)
        {
            new CustomListWidgetItem<ebp::Projekt>(p,this->ui->listWidget);
        }

        if (projects.count()>0)
        {
            curProject=projects.first();
            setProjekt();
        }

        maDialog = NULL;
        maDialog = new ChooseMaDialog(ebp::Mitarbeiter::loadAll(curContext.curConnection),"Mitarbeiter wählen:",this);
        QObject::connect(maDialog,SIGNAL(chosen(QSharedPointer<ebp::Mitarbeiter>)),this, SLOT(setChosenMa(QSharedPointer<ebp::Mitarbeiter>)));
    }
    pendingChanges = false;
}
bool Projekt::hasPendingChanges()
{
    bool result = pendingChanges;
    if (this->ui->beschreibungEdit->document()->isUndoAvailable())
        result = true;

    if (this->ui->zieleEdit->document()->isUndoAvailable())
        result = true;

    return result;
}
void Projekt::on_beginnDateEdit_dateChanged(const QDate &date)
{
    Q_UNUSED(date)
    pendingChanges = true;
}
void Projekt::on_endeDateEdit_dateChanged(const QDate &date)
{
    Q_UNUSED(date)
    pendingChanges = true;
}
