#ifndef SIMPLEMA_H
#define SIMPLEMA_H

#include <QAbstractTableModel>
#include <EBPdb/Mitarbeiter.hxx>
class SimpleMA : public QAbstractTableModel
{
    Q_OBJECT
     QList < QSharedPointer < ebp::Mitarbeiter > > MAList;
public:
    explicit SimpleMA(QList< QSharedPointer< ebp::Mitarbeiter> > MA, QObject *parent = 0);
     int rowCount(const QModelIndex &parent) const;
     int columnCount(const QModelIndex &parent) const;
     QVariant data(const QModelIndex &index, int role) const;
     QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:

public slots:

};

#endif // SIMPLEMA_H
