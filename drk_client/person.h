#ifndef PERSON_H
#define PERSON_H

#include <QWidget>
#include <QList>
#include "sessioncontext.h"
#include "savecontentinterface.h"


class person : public QWidget, public SaveContentInterface
{
    Q_OBJECT
    QList <QWidget *> person_edit;
    QWidget *CreatePersonEdit(int type);
    void initField();
    const SessionContext &con;

public:
    explicit person(const SessionContext &context, QWidget *parent = 0);
    enum PersonSlots{title=0, forename=1, name=2, dateOfBirth=3, birthplace=4, citizenship=5,
                     confession=6, familyState=7, formerAddress=8, residence=9, comments=10, countOfLineEdits=11};
    QWidget *getPersonSlot(int i){ return this->person_edit.at(i); }
    bool saveContent();

signals:

public slots:

};

#endif // PERSON_H
