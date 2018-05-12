/********************************************************************************
** Form generated from reading UI file 'client_connector.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_CONNECTOR_H
#define UI_CLIENT_CONNECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_client_connector
{
public:
    QWidget *centralWidget;
    QPushButton *connectButton;
    QPushButton *exitButton;
    QPlainTextEdit *ipTextInput;
    QLabel *ipLabel;
    QLabel *portLabel;
    QPlainTextEdit *portTextInput;
    QLabel *logoWorms;
    QLabel *label;
    QLabel *label_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *client_connector)
    {
        if (client_connector->objectName().isEmpty())
            client_connector->setObjectName(QStringLiteral("client_connector"));
        client_connector->resize(292, 300);
        client_connector->setMinimumSize(QSize(292, 300));
        client_connector->setMaximumSize(QSize(292, 300));
        client_connector->setAutoFillBackground(false);
        client_connector->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(client_connector);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(170, 230, 89, 25));
        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(30, 230, 89, 25));
        exitButton->setMinimumSize(QSize(89, 25));
        exitButton->setMaximumSize(QSize(89, 25));
        ipTextInput = new QPlainTextEdit(centralWidget);
        ipTextInput->setObjectName(QStringLiteral("ipTextInput"));
        ipTextInput->setGeometry(QRect(120, 130, 161, 31));
        ipTextInput->setBackgroundVisible(false);
        ipLabel = new QLabel(centralWidget);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));
        ipLabel->setGeometry(QRect(20, 130, 71, 31));
        portLabel = new QLabel(centralWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));
        portLabel->setGeometry(QRect(20, 190, 67, 17));
        portTextInput = new QPlainTextEdit(centralWidget);
        portTextInput->setObjectName(QStringLiteral("portTextInput"));
        portTextInput->setGeometry(QRect(120, 180, 91, 31));
        logoWorms = new QLabel(centralWidget);
        logoWorms->setObjectName(QStringLiteral("logoWorms"));
        logoWorms->setGeometry(QRect(50, 0, 201, 71));
        logoWorms->setTextFormat(Qt::RichText);
        logoWorms->setPixmap(QPixmap(QString::fromUtf8("../../resources/graphics/Logos/worms_logo.png")));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(-50, -40, 411, 301));
        label->setTextFormat(Qt::RichText);
        label->setPixmap(QPixmap(QString::fromUtf8("../../resources/graphics/Logos/client_connector_background.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(-20, 110, 151, 111));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../../resources/graphics/Logos/text_box.png")));
        label_2->setScaledContents(true);
        client_connector->setCentralWidget(centralWidget);
        label->raise();
        label_2->raise();
        logoWorms->raise();
        connectButton->raise();
        exitButton->raise();
        ipTextInput->raise();
        ipLabel->raise();
        portLabel->raise();
        portTextInput->raise();
        mainToolBar = new QToolBar(client_connector);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        client_connector->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(client_connector);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        client_connector->setStatusBar(statusBar);

        retranslateUi(client_connector);

        QMetaObject::connectSlotsByName(client_connector);
    } // setupUi

    void retranslateUi(QMainWindow *client_connector)
    {
        client_connector->setWindowTitle(QApplication::translate("client_connector", "Worms - Cliente", Q_NULLPTR));
#ifndef QT_NO_ACCESSIBILITY
        client_connector->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        connectButton->setText(QApplication::translate("client_connector", "Connect", Q_NULLPTR));
        exitButton->setText(QApplication::translate("client_connector", "Exit", Q_NULLPTR));
        ipLabel->setText(QApplication::translate("client_connector", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600; color:#fce94f;\">Host / IP</span></p></body></html>", Q_NULLPTR));
        portLabel->setText(QApplication::translate("client_connector", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600; color:#fce94f;\">Port</span></p></body></html>", Q_NULLPTR));
        logoWorms->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class client_connector: public Ui_client_connector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_CONNECTOR_H
