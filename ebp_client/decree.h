#ifndef DECREE_H
#define DECREE_H

#include <QScrollArea>
/**
  * \brief Einzelne "Verfügung"
  */
class Decree : public QScrollArea
{
    Q_OBJECT
    QList < QList <QWidget *> > DecreeWidgets;
public:
    explicit Decree(QWidget *parent = 0);
    enum ContentBoxes{general=0,fixation=1, bedrail=2, psychotropic=3};
    QList <QWidget *> getBoxWidgets(int BoxType) { return DecreeWidgets.at(BoxType); }

signals:

public slots:

};

#endif // DECREE_H
