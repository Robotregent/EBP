#ifndef MELDELISTE_H
#define MELDELISTE_H

#include <QWidget>

namespace Ui {
    class MeldeListe;
}

/**
  * \brief Maske: "Meldeliste"
  */
class MeldeListe : public QWidget
{
    Q_OBJECT

public:
    explicit MeldeListe(QWidget *parent = 0);
    ~MeldeListe();

private:
    Ui::MeldeListe *ui;
};

#endif // MELDELISTE_H
