#ifndef MAMODEL_H
#define MAMODEL_H

#include <EBPdb/Mitarbeiter.hxx>
#include <QAbstractTableModel>

class MAmodel : public QAbstractTableModel
{
    Q_OBJECT
    QList < QSharedPointer < ebp::Mitarbeiter > > MAList;
public:
    explicit MAmodel(QList< QSharedPointer< ebp::Mitarbeiter> > MA, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:

public slots:

};

#endif // MAMODEL_H
