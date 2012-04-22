/********************************************************************************
** Form generated from reading UI file 'meldeliste.ui'
**
** Created: Sat Apr 21 15:46:01 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MELDELISTE_H
#define UI_MELDELISTE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeldeListe
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QDateEdit *curDay;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QDateEdit *from;
    QLabel *label_3;
    QDateEdit *to;
    QPushButton *pushButton;
    QTableWidget *tableWidget;

    void setupUi(QWidget *MeldeListe)
    {
        if (MeldeListe->objectName().isEmpty())
            MeldeListe->setObjectName(QString::fromUtf8("MeldeListe"));
        MeldeListe->resize(833, 556);
        verticalLayout = new QVBoxLayout(MeldeListe);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(MeldeListe);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(0);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        curDay = new QDateEdit(groupBox_2);
        curDay->setObjectName(QString::fromUtf8("curDay"));
        curDay->setCalendarPopup(true);

        horizontalLayout_2->addWidget(curDay);


        horizontalLayout_3->addWidget(groupBox_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        from = new QDateEdit(groupBox);
        from->setObjectName(QString::fromUtf8("from"));
        from->setCalendarPopup(true);

        horizontalLayout->addWidget(from);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        to = new QDateEdit(groupBox);
        to->setObjectName(QString::fromUtf8("to"));
        to->setCalendarPopup(true);

        horizontalLayout->addWidget(to);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        horizontalLayout_3->addWidget(groupBox);


        verticalLayout->addWidget(frame);

        tableWidget = new QTableWidget(MeldeListe);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setAutoFillBackground(false);
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setLineWidth(1);
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tableWidget);


        retranslateUi(MeldeListe);

        QMetaObject::connectSlotsByName(MeldeListe);
    } // setupUi

    void retranslateUi(QWidget *MeldeListe)
    {
        MeldeListe->setWindowTitle(QApplication::translate("MeldeListe", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MeldeListe", "Tag anzeigen", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MeldeListe", "Exportieren der Meldeliste", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MeldeListe", "Von:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MeldeListe", "Bis:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MeldeListe", "Export", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MeldeListe", "Bewohner", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MeldeListe", "Anwesend", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MeldeListe", "wenn nein - Grund", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MeldeListe: public Ui_MeldeListe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MELDELISTE_H
