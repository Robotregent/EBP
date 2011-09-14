#ifndef PERSON_H
#define PERSON_H

#include <QWidget>
#include <QList>
#include <QTextEdit>

class person : public QWidget
{
    Q_OBJECT
    QList <QTextEdit *> person_edit;
public:
    explicit person(QWidget *parent = 0);
    enum PersonSlots{title=0, forename=1, name=2, dateOfBirth=3, age=4, birthplace=5, citizenship=6,
		     confession=7, familyStatus=8, formerAddress=9, residence=10, comments=11, countOfLineEdits=12};
    QTextEdit *getPersonSlot(int i){ return this->person_edit.at(i); }

signals:

public slots:

};

#endif // PERSON_H
