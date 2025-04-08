/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *Ip;
    QLabel *label;
    QSpinBox *port;
    QPushButton *connect;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QPushButton *send;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QPushButton *clearbtn;
    QListWidget *console;
    QListWidget *users;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(878, 755);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        Ip = new QLineEdit(groupBox);
        Ip->setObjectName("Ip");
        Ip->setStyleSheet(QString::fromUtf8("#Ip[state = \"0\"]{\n"
"	background-color: rgb(255, 0, 0);\n"
"}\n"
"#Ip[state=\"1\"]{\n"
"	\n"
"	background-color: rgb(0, 170, 0);\n"
"}"));
        Ip->setClearButtonEnabled(true);

        gridLayout->addWidget(Ip, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        port = new QSpinBox(groupBox);
        port->setObjectName("port");
        port->setMinimum(1024);
        port->setMaximum(65535);

        gridLayout->addWidget(port, 1, 1, 1, 1);

        connect = new QPushButton(groupBox);
        connect->setObjectName("connect");

        gridLayout->addWidget(connect, 2, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName("formLayout");
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_4);

        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit);

        send = new QPushButton(groupBox_2);
        send->setObjectName("send");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, send);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName("gridLayout_3");
        clearbtn = new QPushButton(groupBox_3);
        clearbtn->setObjectName("clearbtn");

        gridLayout_3->addWidget(clearbtn, 3, 0, 1, 1);

        console = new QListWidget(groupBox_3);
        console->setObjectName("console");

        gridLayout_3->addWidget(console, 2, 0, 1, 1);

        users = new QListWidget(groupBox_3);
        users->setObjectName("users");

        gridLayout_3->addWidget(users, 1, 0, 1, 1, Qt::AlignmentFlag::AlignTop);


        gridLayout_2->addWidget(groupBox_3, 0, 1, 3, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 878, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        groupBox->setProperty("state", QVariant(QCoreApplication::translate("MainWindow", "0", nullptr)));
        label_2->setText(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
        Ip->setInputMask(QCoreApplication::translate("MainWindow", "000.000.000.000", nullptr));
        Ip->setProperty("state", QVariant(QString()));
        label->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
        send->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        groupBox_3->setTitle(QString());
        clearbtn->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
