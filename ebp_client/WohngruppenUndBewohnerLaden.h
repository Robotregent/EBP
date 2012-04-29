#ifndef WOHNGRUPPENLADEN_H
#define WOHNGRUPPENLADEN_H

#endif // WOHNGRUPPENLADEN_H
#include <EBPdb/Wohngruppe.hxx>
#include <QList>

/**
 * \brief Laden aller Wohnguppen. Soll QtConcurrent::run() asynchron zum Laden genutzt werden.
 **/
QList < QSharedPointer <ebp::Wohngruppe> > loadAllGroups(QSharedPointer<ebp::connection> aPointerToAConnection, QSharedPointer<ebp::Mitarbeiter> curMitarbeiter)
{
	return curMitarbeiter->loadWohngruppen(aPointerToAConnection);
}
/**
  * \brief Laden aller Bewohner. Soll QtConcurrent::run() asynchron zum Laden genutzt werden.
  **/
QList < QSharedPointer <ebp::Bewohner> > loadAllBewohner(QSharedPointer<ebp::connection> aPointerToAConnection, QList < QSharedPointer <ebp::Wohngruppe> >allGroups )
{
	QList < QSharedPointer <ebp::Bewohner> > result= QList < QSharedPointer <ebp::Bewohner> >();
	foreach (QSharedPointer <ebp::Wohngruppe> wg, allGroups )
	{
	    result.append(wg->loadBewohner(aPointerToAConnection));
	}
	return result;
}
