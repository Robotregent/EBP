#include "person.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>


person::person(const SessionContext &context, QWidget *parent) :
    QWidget(parent),
    con(context)
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
    //LayoutLeft->addRow(tr("Alter"),this->person_edit.at(person::age));
    LayoutLeft->addRow(tr("Geburtsort"),this->person_edit.at(person::birthplace));
    LayoutLeft->addRow(tr("Staatsbürgerschaft"),this->person_edit.at(person::citizenship));
    LayoutLeft->addRow(tr("Konfession"),this->person_edit.at(person::confession));
    LayoutLeft->addRow(tr("Familienstatus"),this->person_edit.at(person::familyState));
    LayoutLeft->addRow(tr("Aufenthalt hier seit"),this->person_edit.at(person::residence));

    LayoutRight->addRow(tr("Bisherige Anschrift"),this->person_edit.at(person::formerAddress));
    LayoutRight->addRow(tr("Anmerkung"),this->person_edit.at(person::comments));

    hLayout->addLayout(LayoutLeft,12);
    hLayout->addLayout(LayoutRight,20);
    hLayout->addStretch(1);
    this->setLayout(hLayout);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    this->initField();

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
        ((QDateEdit *)result)->setCalendarPopup(true);
	break;
    default:
	result = new QLineEdit(this);
	break;
    }
    return result;
}
void person::initField()
{
    if (con.curBewohner!=NULL)
    {

        ((QLineEdit *)this->person_edit.at(person::title))->setText(this->con.curBewohner->anrede());
        ((QLineEdit *)this->person_edit.at(person::forename))->setText(this->con.curBewohner->vorname());
        ((QLineEdit *)this->person_edit.at(person::name))->setText(this->con.curBewohner->nachname());
        ((QDateEdit *)this->person_edit.at(person::dateOfBirth))->setDate(this->con.curBewohner->geburtsdatum());
        ((QLineEdit *)this->person_edit.at(person::birthplace))->setText(this->con.curBewohner->geburtsort());
        ((QLineEdit *)this->person_edit.at(person::citizenship))->setText(this->con.curBewohner->staat());
        ((QLineEdit *)this->person_edit.at(person::confession))->setText(con.curBewohner->konfession());
        ((QLineEdit *)this->person_edit.at(person::familyState))->setText(con.curBewohner->familienstatus());
        ((QDateEdit *)this->person_edit.at(person::residence))->setDate(con.curBewohner->seit());
        ((QTextEdit *)this->person_edit.at(person::comments))->setText(con.curBewohner->anmerkung());


    }

}

bool person::saveContent()
{
    /// \todo Speichern Implementierten
    return true;
}
