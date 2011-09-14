#include "person.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
person::person(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setSpacing(20);
    QFormLayout *LayoutLeft = new QFormLayout();
    LayoutLeft->setSpacing(15);
    QFormLayout *LayoutRight = new QFormLayout();
    LayoutRight->setSpacing(15);

    for (int i = 0 ; i<person::countOfLineEdits ; i++)
    {
	this->person_edit.append(this->CreatePersonEdit(i));
    }

    LayoutLeft->addRow(tr("Anrede"),this->person_edit.at(person::title));
    LayoutLeft->addRow(tr("Vorname"),this->person_edit.at(person::forename));
    LayoutLeft->addRow(tr("Nachname"),this->person_edit.at(person::name));
    LayoutLeft->addRow(tr("Geburtsdatum"),this->person_edit.at(person::dateOfBirth));
    LayoutLeft->addRow(tr("Alter"),this->person_edit.at(person::age));
    LayoutLeft->addRow(tr("Geburtsort"),this->person_edit.at(person::birthplace));
    LayoutLeft->addRow(tr("Staatsbürgerschaft"),this->person_edit.at(person::citizenship));
    LayoutLeft->addRow(tr("Konfession"),this->person_edit.at(person::confession));
    LayoutLeft->addRow(tr("Familienstatus"),this->person_edit.at(person::familyState));
    LayoutLeft->addRow(tr("Aufenthalt hier seit"),this->person_edit.at(person::residence));

    LayoutRight->addRow(tr("bisherige Anschrift"),this->person_edit.at(person::formerAddress));
    LayoutRight->addRow(tr("Anmerkung"),this->person_edit.at(person::comments));

    hLayout->addLayout(LayoutLeft,1);
    hLayout->addLayout(LayoutRight,2);
    this->setLayout(hLayout);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

}

QWidget *person::CreatePersonEdit(int type)
{
    QWidget *result;
    switch (type)
    {
    case person::comments:
    case person::formerAddress:
	result = new QTextEdit(this);
	break;
    case person::dateOfBirth:
    case person::residence:
	result = new QDateEdit(this);
	break;
    default:
	result = new QLineEdit(this);
	break;
    }
    return result;
}
