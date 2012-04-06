#ifndef SAVECONTENTINTERFACE_H
#define SAVECONTENTINTERFACE_H
/**
  * \brief Interface muss von den Contentwidgets implementiert werden, die zu speicherden Inhalt haben
  */
class SaveContentInterface
{
public:
    virtual bool saveContent()=0;
};

#endif // SAVECONTENTINTERFACE_H
