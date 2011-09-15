#ifndef EMPLOYEELISTMODEL_H
#define EMPLOYEELISTMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>
#include "../drkv/Mitarbeiter.hxx"
using namespace drkv;
class EmployeeTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QList < QSharedPointer < Mitarbeiter > > EmployeeList;
public:
    explicit EmployeeTableModel(QList < QSharedPointer < Mitarbeiter> > employees,QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
signals:

public slots:

};

#endif // EMPLOYEELISTMODEL_H
