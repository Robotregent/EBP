#ifndef WOHNGRUPPENLADEN_H
#define WOHNGRUPPENLADEN_H

#endif // WOHNGRUPPENLADEN_H
#include <EBPdb/Wohngruppe.hxx>
#include <QList>

namespace ebp
{
    /**
      * \brief Laden aller Wohnguppen. Soll QtConcurrent::run() asynchron zum Laden genutzt werden.
      **/
    QList < QSharedPointer <ebp::Wohngruppe> > loadAllGroups(QSharedPointer<ebp::connection> aPointerToAConnection)
    {
        return ebp::Wohngruppe::loadAll(aPointerToAConnection);
    }
    /**
      * \brief Laden aller Bewohner. Soll QtConcurrent::run() asynchron zum Laden genutzt werden.
      **/
    QList < QSharedPointer <ebp::Bewohner> > loadAllBewohner(QSharedPointer<ebp::connection> aPointerToAConnection)
    {
        return ebp::Bewohner::loadAll(aPointerToAConnection);
    }
}
