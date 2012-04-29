#ifndef PERSON_H
#define PERSON_H

#include <QWidget>
#include <QList>
#include "sessioncontext.h"
#include "savecontentinterface.h"


/**
  * \brief Maske: "Person"
  */
class person : public QWidget, public SaveContentInterface
{
    Q_OBJECT
    QList <QWidget *> person_edit;
    QWidget *CreatePersonEdit(int type);
    void initField();
    const SessionContext &con;
    enum PersonSlots{title=0, forename=1, name=2, dateOfBirth=3, birthplace=4, citizenship=5,
		     confession=6, familyState=7, residence=8, comments=9, countOfLineEdits=10};
    QWidget *getPersonSlot(int i){ return this->person_edit.at(i); }

public:
    explicit person(const SessionContext &context, QWidget *parent = 0);
    bool saveContent();							    ///< Speichern den Inhalts
    bool hasPendingChanges();

signals:

public slots:

};

#endif // PERSON_H

