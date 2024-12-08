/********************************************************************************
** Form generated from reading UI file 'voicehome.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOICEHOME_H
#define UI_VOICEHOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VoiceHome
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *VoiceHome)
    {
        if (VoiceHome->objectName().isEmpty())
            VoiceHome->setObjectName("VoiceHome");
        VoiceHome->resize(800, 600);
        centralwidget = new QWidget(VoiceHome);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(300, -20, 200, 200));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/voicehomelogo-removebg-preview(1).png")));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(240, 470, 341, 91));
        QFont font;
        font.setPointSize(36);
        label_2->setFont(font);
        VoiceHome->setCentralWidget(centralwidget);
        menubar = new QMenuBar(VoiceHome);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        VoiceHome->setMenuBar(menubar);
        statusbar = new QStatusBar(VoiceHome);
        statusbar->setObjectName("statusbar");
        VoiceHome->setStatusBar(statusbar);

        retranslateUi(VoiceHome);

        QMetaObject::connectSlotsByName(VoiceHome);
    } // setupUi

    void retranslateUi(QMainWindow *VoiceHome)
    {
        VoiceHome->setWindowTitle(QCoreApplication::translate("VoiceHome", "VoiceHome", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("VoiceHome", "\320\230\320\264\321\221\321\202 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\320\260...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VoiceHome: public Ui_VoiceHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOICEHOME_H
