#include "person.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
person::person(QWidget *parent) :
    QWidget(parent)
{
    QFormLayout *Layout = new QFormLayout(this);

    for (int i = 0 ; i<person::countOfLineEdits ; i++)
    {
	if((i == person::comments)||(i == person::formerAddress))
	{
	    this->person_edit.append( new QTextEdit(this));
	}
	else
	{
	    this->person_edit.append( new QLineEdit(this));
	}
    }

    Layout->addRow(tr("Anrede"),this->person_edit.at(person::title));
    Layout->addRow(tr("Vorname"),this->person_edit.at(person::forename));
    Layout->addRow(tr("Nachname"),this->person_edit.at(person::name));
    Layout->addRow(tr("Geburtsdatum"),this->person_edit.at(person::dateOfBirth));
    Layout->addRow(tr("Alter"),this->person_edit.at(person::age));
    Layout->addRow(tr("Geburtsort"),this->person_edit.at(person::birthplace));
    Layout->addRow(tr("Staatsbürgerschaft"),this->person_edit.at(person::citizenship));
    Layout->addRow(tr("Konfession"),this->person_edit.at(person::confession));
    Layout->addRow(tr("Familienstatus"),this->person_edit.at(person::familyState));
    Layout->addRow(tr("bisherige Anschrift"),this->person_edit.at(person::formerAddress));
    Layout->addRow(tr("Aufenthalt hier seit"),this->person_edit.at(person::residence));
    Layout->addRow(tr("Anmerkung"),this->person_edit.at(person::comments));


    this->setLayout(Layout);

}
