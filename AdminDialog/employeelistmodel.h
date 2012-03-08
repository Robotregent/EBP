#ifndef EMPLOYEELISTMODEL_H
#define EMPLOYEELISTMODEL_H

#include <QAbstractTableModel>
#include <QSharedPointer>
#include <EBPdb/Mitarbeiter.hxx>

class EmployeeTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QList < QSharedPointer < ebp::Mitarbeiter > > EmployeeList;
public:
    explicit EmployeeTableModel(QList < QSharedPointer < ebp::Mitarbeiter> > employees,QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QString login(int row) { return EmployeeList.at(row)->login(); }
    QString name(int row) { return EmployeeList.at(row)->name(); }
    QSharedPointer < ebp::Mitarbeiter> getMitarbeiter(int index);
    void addMitarbeiter(QSharedPointer<ebp::Mitarbeiter> newMA);
signals:

public slots:

};

#endif // EMPLOYEELISTMODEL_H
