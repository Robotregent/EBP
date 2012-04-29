#ifndef LEISTUNGSTRAEGERAREA_H
#define LEISTUNGSTRAEGERAREA_H

#include <QWidget>
#include <QList>
#include <EBPdb/Leistungstraeger.hxx>
#include <QBoxLayout>
#include "leistungstraegerbox.h"
#include "sessioncontext.h"
#include "savecontentinterface.h"


namespace Ui {
    class LeistungstraegerArea;
}
/**
  * \brief Maske "Leistungsträger"
  */
class LeistungstraegerArea : public QWidget , public SaveContentInterface
{
    Q_OBJECT
    SessionContext &context;
    QList <QSharedPointer< ebp::Leistungstraeger > > leistungstraeger;
    QList <LeistungstraegerBox *> boxes;
    void initBoxes();


public:
    explicit LeistungstraegerArea(SessionContext &_context,QWidget *parent = 0);
    ~LeistungstraegerArea();
    bool saveContent();				///< Speichern den Inhalts
    bool hasPendingChanges();

private:
    Ui::LeistungstraegerArea *ui;
    int columns;
    QList<QVBoxLayout *> VLayouts;
    void addBox(QSharedPointer<ebp::Leistungstraeger> newLeistungstraeger);

private slots:
    void on_neuerTraegerButton_clicked();
};

#endif // LEISTUNGSTRAEGERAREA_H
