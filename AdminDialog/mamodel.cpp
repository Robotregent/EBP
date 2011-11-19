#include "mamodel.h"

MAmodel::MAmodel(QList<QSharedPointer<Mitarbeiter> > MA, QObject *parent) :
    QAbstractTableModel(parent), MAList(MA)
{

}
int MAmodel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->MAList.count();
}
int MAmodel::columnCount(const QModelIndex &parent) const
{
    //Zwei ist nur geraten. Muss angepasst werden
    return 2;
}
QVariant MAmodel::data(const QModelIndex &index, int role) const
{
    //Abbruch, wenn kein valider Index übergeben wurde
    if (!index.isValid())
             return QVariant();
    //Abbruch, wenn Index außerhalb außerhalb der Grenzen des Models liegt
    if (index.row() >= MAList.size()||index.row()<0)
             return QVariant();
    //Ausgeben der Daten
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return MAList.at(index.row())->login();
        else if (index.column()==1)
            return MAList.at(index.row())->name();
        else
            return QVariant();

    }
    else
    {
        return QVariant();
    }
    return QVariant();
}
QVariant MAmodel::headerData(int section, Qt::Orientation orientation, int role) const
{

}
