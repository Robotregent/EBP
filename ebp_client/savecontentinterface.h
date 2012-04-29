#ifndef SAVECONTENTINTERFACE_H
#define SAVECONTENTINTERFACE_H
#include <QMessageBox>
/**
  * \brief Interface muss von den Contentwidgets implementiert werden, die zu speicherden Inhalt haben
  */
class SaveContentInterface
{
protected:
    bool pendingChanges;
public:
    SaveContentInterface()
    {
        pendingChanges=false;
    }
    virtual bool hasPendingChanges()=0;
    virtual bool saveContent()=0;

};

#endif // SAVECONTENTINTERFACE_H
