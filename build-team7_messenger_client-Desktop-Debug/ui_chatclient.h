/********************************************************************************
** Form generated from reading UI file 'chatclient.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATCLIENT_H
#define UI_CHATCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatClient
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_port;
    QLineEdit *lineEdit_user;
    QLineEdit *lineEdit_message;
    QTextBrowser *textBrowser_messages;
    QPushButton *button_connect;
    QPushButton *button_send;
    QPushButton *button_sendFile;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChatClient)
    {
        if (ChatClient->objectName().isEmpty())
            ChatClient->setObjectName(QString::fromUtf8("ChatClient"));
        ChatClient->resize(383, 558);
        centralwidget = new QWidget(ChatClient);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 71, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 81, 21));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 130, 57, 21));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 220, 57, 21));
        lineEdit_ip = new QLineEdit(centralwidget);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
        lineEdit_ip->setGeometry(QRect(100, 30, 201, 23));
        lineEdit_port = new QLineEdit(centralwidget);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(100, 80, 201, 23));
        lineEdit_user = new QLineEdit(centralwidget);
        lineEdit_user->setObjectName(QString::fromUtf8("lineEdit_user"));
        lineEdit_user->setGeometry(QRect(100, 130, 201, 23));
        lineEdit_message = new QLineEdit(centralwidget);
        lineEdit_message->setObjectName(QString::fromUtf8("lineEdit_message"));
        lineEdit_message->setGeometry(QRect(70, 220, 231, 21));
        textBrowser_messages = new QTextBrowser(centralwidget);
        textBrowser_messages->setObjectName(QString::fromUtf8("textBrowser_messages"));
        textBrowser_messages->setGeometry(QRect(15, 261, 351, 211));
        button_connect = new QPushButton(centralwidget);
        button_connect->setObjectName(QString::fromUtf8("button_connect"));
        button_connect->setGeometry(QRect(150, 170, 80, 23));
        button_send = new QPushButton(centralwidget);
        button_send->setObjectName(QString::fromUtf8("button_send"));
        button_send->setGeometry(QRect(310, 220, 61, 23));
        button_sendFile = new QPushButton(centralwidget);
        button_sendFile->setObjectName(QString::fromUtf8("button_sendFile"));
        button_sendFile->setGeometry(QRect(140, 490, 101, 23));
        ChatClient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChatClient);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 383, 20));
        ChatClient->setMenuBar(menubar);
        statusbar = new QStatusBar(ChatClient);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ChatClient->setStatusBar(statusbar);

        retranslateUi(ChatClient);

        QMetaObject::connectSlotsByName(ChatClient);
    } // setupUi

    void retranslateUi(QMainWindow *ChatClient)
    {
        ChatClient->setWindowTitle(QCoreApplication::translate("ChatClient", "ChatClient", nullptr));
        label->setText(QCoreApplication::translate("ChatClient", "IP Address", nullptr));
        label_2->setText(QCoreApplication::translate("ChatClient", "Port Number", nullptr));
        label_3->setText(QCoreApplication::translate("ChatClient", "User ID", nullptr));
        label_4->setText(QCoreApplication::translate("ChatClient", "message", nullptr));
        button_connect->setText(QCoreApplication::translate("ChatClient", "connect", nullptr));
        button_send->setText(QCoreApplication::translate("ChatClient", "send", nullptr));
        button_sendFile->setText(QCoreApplication::translate("ChatClient", "send a file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatClient: public Ui_ChatClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATCLIENT_H
