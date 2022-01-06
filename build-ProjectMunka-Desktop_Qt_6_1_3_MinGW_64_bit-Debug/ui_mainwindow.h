/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *lineMode;
    QPushButton *showWayButton;
    QPushButton *animationButton;
    QLabel *label_3;
    QLabel *fieldNumLabel;
    QLabel *label_4;
    QLabel *shortWayLabel;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *widthBox;
    QLabel *label_2;
    QSpinBox *heightBox;
    QPushButton *resizeButton;
    QPushButton *leptetbtn;
    QSpacerItem *verticalSpacer_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(861, 489);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        horizontalLayout->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineMode = new QCheckBox(groupBox);
        lineMode->setObjectName(QString::fromUtf8("lineMode"));

        verticalLayout->addWidget(lineMode);

        showWayButton = new QPushButton(groupBox);
        showWayButton->setObjectName(QString::fromUtf8("showWayButton"));

        verticalLayout->addWidget(showWayButton);

        animationButton = new QPushButton(groupBox);
        animationButton->setObjectName(QString::fromUtf8("animationButton"));

        verticalLayout->addWidget(animationButton);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        fieldNumLabel = new QLabel(groupBox);
        fieldNumLabel->setObjectName(QString::fromUtf8("fieldNumLabel"));
        fieldNumLabel->setTextFormat(Qt::AutoText);

        verticalLayout->addWidget(fieldNumLabel);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        shortWayLabel = new QLabel(groupBox);
        shortWayLabel->setObjectName(QString::fromUtf8("shortWayLabel"));

        verticalLayout->addWidget(shortWayLabel);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        widthBox = new QSpinBox(groupBox_2);
        widthBox->setObjectName(QString::fromUtf8("widthBox"));
        widthBox->setMinimum(5);
        widthBox->setMaximum(50);

        formLayout->setWidget(0, QFormLayout::FieldRole, widthBox);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        heightBox = new QSpinBox(groupBox_2);
        heightBox->setObjectName(QString::fromUtf8("heightBox"));
        heightBox->setMinimum(5);
        heightBox->setMaximum(50);

        formLayout->setWidget(1, QFormLayout::FieldRole, heightBox);


        verticalLayout_4->addLayout(formLayout);

        resizeButton = new QPushButton(groupBox_2);
        resizeButton->setObjectName(QString::fromUtf8("resizeButton"));

        verticalLayout_4->addWidget(resizeButton);

        leptetbtn = new QPushButton(groupBox_2);
        leptetbtn->setObjectName(QString::fromUtf8("leptetbtn"));

        verticalLayout_4->addWidget(leptetbtn);


        verticalLayout_3->addWidget(groupBox_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_2->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 861, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Control", nullptr));
        lineMode->setText(QCoreApplication::translate("MainWindow", "Box mode", nullptr));
        showWayButton->setText(QCoreApplication::translate("MainWindow", "Show Shortest Way", nullptr));
        animationButton->setText(QCoreApplication::translate("MainWindow", "Animate search", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Discovered fields:", nullptr));
        fieldNumLabel->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Shortest way:", nullptr));
        shortWayLabel->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Setting", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Width", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Height", nullptr));
        resizeButton->setText(QCoreApplication::translate("MainWindow", "Resize", nullptr));
        leptetbtn->setText(QCoreApplication::translate("MainWindow", "leptet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
