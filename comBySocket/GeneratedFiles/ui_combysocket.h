/********************************************************************************
** Form generated from reading UI file 'combysocket.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBYSOCKET_H
#define UI_COMBYSOCKET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_comBySocketClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QPushButton *pb_set;
    QCheckBox *pb_send;
    QPushButton *pb_InputClear;
    QComboBox *cmb_baudrate;
    QPushButton *pb_get;
    QTextEdit *textEditIn;
    QRadioButton *radio_in_hex;
    QRadioButton *radio_in_string;
    QLabel *label_9;
    QPushButton *pb_senda;
    QVBoxLayout *verticalLayout_3;
    QButtonGroup *buttonGroup_2;

    void setupUi(QWidget *comBySocketClass)
    {
        if (comBySocketClass->objectName().isEmpty())
            comBySocketClass->setObjectName(QString::fromUtf8("comBySocketClass"));
        comBySocketClass->resize(520, 526);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comBySocketClass->sizePolicy().hasHeightForWidth());
        comBySocketClass->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(comBySocketClass);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(comBySocketClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        pb_set = new QPushButton(comBySocketClass);
        pb_set->setObjectName(QString::fromUtf8("pb_set"));

        gridLayout->addWidget(pb_set, 1, 0, 1, 1);

        pb_send = new QCheckBox(comBySocketClass);
        pb_send->setObjectName(QString::fromUtf8("pb_send"));

        gridLayout->addWidget(pb_send, 1, 3, 1, 1);

        pb_InputClear = new QPushButton(comBySocketClass);
        pb_InputClear->setObjectName(QString::fromUtf8("pb_InputClear"));

        gridLayout->addWidget(pb_InputClear, 2, 1, 1, 1);

        cmb_baudrate = new QComboBox(comBySocketClass);
        cmb_baudrate->setObjectName(QString::fromUtf8("cmb_baudrate"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmb_baudrate->sizePolicy().hasHeightForWidth());
        cmb_baudrate->setSizePolicy(sizePolicy1);
        cmb_baudrate->setEditable(true);

        gridLayout->addWidget(cmb_baudrate, 0, 1, 1, 4);

        pb_get = new QPushButton(comBySocketClass);
        pb_get->setObjectName(QString::fromUtf8("pb_get"));

        gridLayout->addWidget(pb_get, 1, 1, 1, 1);

        textEditIn = new QTextEdit(comBySocketClass);
        textEditIn->setObjectName(QString::fromUtf8("textEditIn"));

        gridLayout->addWidget(textEditIn, 4, 0, 1, 5);

        radio_in_hex = new QRadioButton(comBySocketClass);
        buttonGroup_2 = new QButtonGroup(comBySocketClass);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->addButton(radio_in_hex);
        radio_in_hex->setObjectName(QString::fromUtf8("radio_in_hex"));

        gridLayout->addWidget(radio_in_hex, 2, 2, 1, 1);

        radio_in_string = new QRadioButton(comBySocketClass);
        buttonGroup_2->addButton(radio_in_string);
        radio_in_string->setObjectName(QString::fromUtf8("radio_in_string"));

        gridLayout->addWidget(radio_in_string, 2, 3, 1, 1);

        label_9 = new QLabel(comBySocketClass);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 2, 0, 1, 1);

        pb_senda = new QPushButton(comBySocketClass);
        pb_senda->setObjectName(QString::fromUtf8("pb_senda"));

        gridLayout->addWidget(pb_senda, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        verticalLayout->addLayout(verticalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(comBySocketClass);
        QObject::connect(pb_set, SIGNAL(clicked()), comBySocketClass, SLOT(setCom()));
        QObject::connect(pb_get, SIGNAL(clicked()), comBySocketClass, SLOT(getCom()));
        QObject::connect(pb_InputClear, SIGNAL(clicked()), comBySocketClass, SLOT(inClear()));
        QObject::connect(pb_send, SIGNAL(clicked()), comBySocketClass, SLOT(blain()));
        QObject::connect(pb_senda, SIGNAL(clicked()), comBySocketClass, SLOT(sendCom()));

        QMetaObject::connectSlotsByName(comBySocketClass);
    } // setupUi

    void retranslateUi(QWidget *comBySocketClass)
    {
        comBySocketClass->setWindowTitle(QApplication::translate("comBySocketClass", "comBySocket", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("comBySocketClass", "Baudrate:", 0, QApplication::UnicodeUTF8));
        pb_set->setText(QApplication::translate("comBySocketClass", "SetBaudrate", 0, QApplication::UnicodeUTF8));
        pb_send->setText(QApplication::translate("comBySocketClass", "Blind", 0, QApplication::UnicodeUTF8));
        pb_InputClear->setText(QApplication::translate("comBySocketClass", "Clear", 0, QApplication::UnicodeUTF8));
        pb_get->setText(QApplication::translate("comBySocketClass", "GetBaudrate", 0, QApplication::UnicodeUTF8));
        radio_in_hex->setText(QApplication::translate("comBySocketClass", "Hex", 0, QApplication::UnicodeUTF8));
        radio_in_string->setText(QApplication::translate("comBySocketClass", "String", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("comBySocketClass", "Input:", 0, QApplication::UnicodeUTF8));
        pb_senda->setText(QApplication::translate("comBySocketClass", "Send", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class comBySocketClass: public Ui_comBySocketClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBYSOCKET_H
