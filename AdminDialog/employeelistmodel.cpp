#include "employeelistmodel.h"

using namespace ebp;


EmployeeTableModel::EmployeeTableModel(QList<QSharedPointer<Mitarbeiter> > employees, QObject *parent) :
    QAbstractTableModel(parent) , EmployeeList(employees)
{

}

int EmployeeTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
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
	    return EmployeeList.at(index.row())->login();
	else if (index.column()==1)
	    return EmployeeList.at(index.row())->name();
	else
	    return QVariant();

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
		result= tr("login");
		break;
	    case 1:
		result= tr("Name");
	    default:
		break;
	    }
	}
    }
    return result;
}
/**
  * \brief gibt den Mitarbeiter an einer bestimmten Stelle des Models zurück.
  */
QSharedPointer<ebp::Mitarbeiter> EmployeeTableModel::getMitarbeiter(int index)
{
    QSharedPointer<ebp::Mitarbeiter> res = QSharedPointer<ebp::Mitarbeiter>();
    if (this->EmployeeList.count() >= index)
	res = this->EmployeeList.at(index);
    return res;
}
/**
  * \brief Fügt einen neuen Mitarbeiter dem Model hinzu.
  */
void EmployeeTableModel::addMitarbeiter(QSharedPointer<ebp::Mitarbeiter> newMA)
{
    this->EmployeeList.append(newMA);
}
