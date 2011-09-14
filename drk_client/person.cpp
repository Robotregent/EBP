#include "person.h"
#include <QBoxLayout>
#include <QLabel>

person::person(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayoutLabel = new QVBoxLayout();
    QVBoxLayout *vLayoutEdit = new QVBoxLayout();

    for (int i = 0 ; i<person::countOfLineEdits ; i++)
    {
	this->person_edit.append( new QTextEdit(this));
	vLayoutEdit->addWidget(this->person_edit.at(i));
    }

    vLayoutLabel->addWidget(new QLabel(tr("Anrede")));
    vLayoutLabel->addWidget(new QLabel(tr("Vorname")));
    vLayoutLabel->addWidget(new QLabel(tr("Nachname")));
    vLayoutLabel->addWidget(new QLabel(tr("Geburtsdatum")));
    vLayoutLabel->addWidget(new QLabel(tr("Alter")));
    vLayoutLabel->addWidget(new QLabel(tr("Geburtsort")));
    vLayoutLabel->addWidget(new QLabel(tr("Staatsbürgerschaft")));
    vLayoutLabel->addWidget(new QLabel(tr("Konfession")));
    vLayoutLabel->addWidget(new QLabel(tr("Familienstatus")));

}
