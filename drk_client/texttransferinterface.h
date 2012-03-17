#ifndef TEXTTRANSFERINTERFACE_H
#define TEXTTRANSFERINTERFACE_H
#include <QString>
/**
  * \brief Interface für die Transferfunktion von Text in die Betruungsdokumentation
  */
class TextTransferInterface
{
public:
    virtual QString getSelectedText()=0;
};



#endif // TEXTTRANSFERINTERFACE_H
