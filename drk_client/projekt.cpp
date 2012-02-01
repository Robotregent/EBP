#include "projekt.h"
#include "ui_projekt.h"
/*ToDo hier:
 *Alle Projekte eines Bewohners auslesen und in dem listwidget darstellen.
 *Je nach Eintrag in dem listwidget, sollen die Details rechts angezeigt werden.
 *Durch drücken des "Neues Projekt Knopfes soll ein neues Projekt eingefügt werden ;)
 */
Projekt::Projekt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Projekt)
{
    ui->setupUi(this);
    this->ui->alleProjekteLabel->setMinimumHeight(this->ui->betreuenderMitarbeiterLabel->height());
}

Projekt::~Projekt()
{
    delete ui;
}

void Projekt::on_pushButton_clicked()
{
    //ToDo:
    /*Vlt Popup, um den Projektnamen vom User abzufragen,
      dann neues EBP::Projekt anlegen und im widget anzeigen
     */
}
