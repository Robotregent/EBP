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
    //fünf ist nur geraten. Muss angepasst werden
    return 5;
}
QVariant MAmodel::data(const QModelIndex &index, int role) const
{

}
QVariant MAmodel::headerData(int section, Qt::Orientation orientation, int role) const
{

}
