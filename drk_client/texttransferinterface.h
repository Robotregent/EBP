#ifndef TEXTTRANSFERINTERFACE_H
#define TEXTTRANSFERINTERFACE_H
#include <QTextDocumentFragment>
/**
  *\brief Hält alle notwendigen Informationen für einen Texttransfer
  */
typedef struct
{
    bool isEmpty;				    ///< true, wenn es keinen Text für einen Texttransfer gab
    QString information;			    ///< Metainformationen über den Texttransfer. In der Regel aus welchem Widget das Textfragment stammt
    QTextDocumentFragment textTransferFragment;	    ///< Ein formatiertes Textfragment
} TextTransferInformation;
/**
  * \brief Interface für die Transferfunktion von Text in die Betruungsdokumentation. Kann auch leer sein. Prüfe TextTransferInformation::isEmpty.
  */
class TextTransferInterface
{
public:
    virtual TextTransferInformation getSelectedText()=0;
};



#endif // TEXTTRANSFERINTERFACE_H
