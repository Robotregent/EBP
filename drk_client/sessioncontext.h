#ifndef SESSIONCONTEXT_H
#define SESSIONCONTEXT_H

#include <EBPdb/connection.hxx>
#include <EBPdb/Mitarbeiter.hxx>
#include <EBPdb/Bewohner.hxx>
#include <EBPdb/Wohngruppe.hxx>
#include <QList>

/**
  * \brief Hällt alle Daten der aktuellen Session
  */
typedef struct
{
    QSharedPointer< ebp::connection > curConnection;        ///< Connectiion zur Datenbank
    QSharedPointer< ebp::Mitarbeiter > curMitarbeiter;      ///< Eingeloggter Mitarbeiter
    QSharedPointer< ebp::Wohngruppe > curWohngruppe;        ///< Aktive Whngruppe
    QSharedPointer< ebp::Bewohner > curBewohner;            ///< Aktiver Bewohner
    QList< QSharedPointer< ebp::Wohngruppe > > allGroups;   ///< Alle Wohngruppen, die mit dem eingeloggten Mitarbeiter assoziiert sind
    QList< QSharedPointer < ebp::Bewohner > > allBewohner;  ///< Alle Bewohner der aktiven Wohngruppe
}  SessionContext;

#endif // SESSIONCONTEXT_H
