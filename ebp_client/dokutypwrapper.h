#ifndef DOKUTYPWRAPPER_H
#define DOKUTYPWRAPPER_H
#include <QString>
#include <EBPdb/Dokumentation.hxx>
class DokuTypWrapper
{

public:

    static QString toString(ebp::Dokumentation::Typ typ)
    {
	QString result;
	switch (typ)
	{
	case ebp::Dokumentation::aufstehenUndZuBettgehen:
	    result = "Aufstehen und zu Bett gehen";
	    break;
	case ebp::Dokumentation::einkaufen:
	    result = "Einkaufen";
	    break;
	case ebp::Dokumentation::waeschepflege:
	    result = "Wäschepflege";
	    break;
	case ebp::Dokumentation::partnerschaften:
	    result = "Partnerschaften";
	    break;
	case ebp::Dokumentation::koerperpflege:
	    result = "Körperpflege";
	    break;
	case ebp::Dokumentation::freundschaften:
	    result = "Freundschaften";
	    break;
	}
	return result;
    }
    static ebp::Dokumentation::Typ toTyp(QString stringTyp)
    {
	ebp::Dokumentation::Typ result;
	if (stringTyp=="Aufstehen und zu Bett gehen" )
	    result = ebp::Dokumentation::aufstehenUndZuBettgehen;
	else if (stringTyp == "Einkaufen")
	    result = ebp::Dokumentation::einkaufen;
	else if (stringTyp == "Wäschepflege")
	    result = ebp::Dokumentation::waeschepflege;
	else if (stringTyp =="Partenerschaften")
	    result = ebp::Dokumentation::partnerschaften;
	else if (stringTyp =="Körperpflege")
	    result = ebp::Dokumentation::koerperpflege;
	else if (stringTyp =="Freundschaften")
	    result = ebp::Dokumentation::freundschaften;
	else
	    result = ebp::Dokumentation::einkaufen;

	return result;
    }
};
#endif // DOKUTYPWRAPPER_H
