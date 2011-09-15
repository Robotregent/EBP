#include "employeelistmodel.h"

EmployeeTableModel::EmployeeTableModel(QList<QSharedPointer<Mitarbeiter> > employees, QObject *parent) :
    QAbstractTableModel(parent) , EmployeeList(employees)
{

}

int EmployeeTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}
int EmployeeTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->EmployeeList.count();
}
QVariant EmployeeTableModel::data(const QModelIndex &index, int role) const
{

    //Abbruch, wenn kein valider Index übergeben wurde
    if (!index.isValid())
	     return QVariant();
    //Abbruch, wenn Index außerhalb außerhalb der Grenzen des Models liegt
    if (index.row() >= EmployeeList.size()||index.row()<0)
	     return QVariant();
    //Ausgeben der Daten
    if (role == Qt::DisplayRole)
    {
	if (index.column() == 0)
	    return EmployeeList.at(index.row())->name();

    }
    else
    {
	return QVariant();
    }
    return QVariant();
}
QVariant EmployeeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result;
    //Abbruch bei falscher Rolle
    if (role==Qt::DisplayRole)
    {
	//Beschriftung der Spalten
	if(orientation==Qt::Horizontal)
	{
	    switch (section)
	    {
	    case 0:
		result= tr("Mitarbeiter");
		break;
	    default:
		break;
	    }
	}
    }
    return result;
}
