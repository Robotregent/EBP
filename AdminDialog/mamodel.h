#ifndef MAMODEL_H
#define MAMODEL_H

#include "../drkv/Mitarbeiter.hxx"
#include <QAbstractTableModel>
using namespace drkv;
class MAmodel : public QAbstractTableModel
{
    Q_OBJECT
    QList < QSharedPointer < Mitarbeiter > > MAList;
public:
    explicit MAmodel(QList<QSharedPointer<Mitarbeiter> > MA, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:

public slots:

};

#endif // MAMODEL_H
