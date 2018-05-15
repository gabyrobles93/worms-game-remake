/********************************************************************************
** Form generated from reading UI file 'client_connector.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
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
    QLabel *ipLabel;
    QLabel *portLabel;
    QLabel *logoWorms;
    QLabel *background;
    QLabel *portBoxLabel;
    QLabel *playerNameLabel;
    QLabel *ipBoxLabel;
    QLabel *nameBoxLabel;
    QLineEdit *playerNameInput;
    QLineEdit *ipTextInput;
    QLineEdit *portTextInput;
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
        ipLabel = new QLabel(centralWidget);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));
        ipLabel->setGeometry(QRect(30, 130, 71, 31));
        portLabel = new QLabel(centralWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));
        portLabel->setGeometry(QRect(30, 186, 67, 21));
        logoWorms = new QLabel(centralWidget);
        logoWorms->setObjectName(QStringLiteral("logoWorms"));
        logoWorms->setGeometry(QRect(50, 0, 201, 71));
        logoWorms->setTextFormat(Qt::RichText);
        logoWorms->setPixmap(QPixmap(QString::fromUtf8(":/images/worms_logo.png")));
        background = new QLabel(centralWidget);
        background->setObjectName(QStringLiteral("background"));
        background->setGeometry(QRect(-50, -40, 411, 311));
        background->setTextFormat(Qt::RichText);
        background->setPixmap(QPixmap(QString::fromUtf8(":/images/connector_bg.jpg")));
        background->setScaledContents(true);
        portBoxLabel = new QLabel(centralWidget);
        portBoxLabel->setObjectName(QStringLiteral("portBoxLabel"));
        portBoxLabel->setGeometry(QRect(10, 170, 101, 51));
        portBoxLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/text_box.png")));
        portBoxLabel->setScaledContents(true);
        playerNameLabel = new QLabel(centralWidget);
        playerNameLabel->setObjectName(QStringLiteral("playerNameLabel"));
        playerNameLabel->setGeometry(QRect(40, 80, 91, 31));
        ipBoxLabel = new QLabel(centralWidget);
        ipBoxLabel->setObjectName(QStringLiteral("ipBoxLabel"));
        ipBoxLabel->setGeometry(QRect(10, 120, 101, 51));
        ipBoxLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/text_box.png")));
        ipBoxLabel->setScaledContents(true);
        nameBoxLabel = new QLabel(centralWidget);
        nameBoxLabel->setObjectName(QStringLiteral("nameBoxLabel"));
        nameBoxLabel->setGeometry(QRect(10, 70, 101, 51));
        nameBoxLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/text_box.png")));
        nameBoxLabel->setScaledContents(true);
        playerNameInput = new QLineEdit(centralWidget);
        playerNameInput->setObjectName(QStringLiteral("playerNameInput"));
        playerNameInput->setGeometry(QRect(110, 80, 113, 25));
        ipTextInput = new QLineEdit(centralWidget);
        ipTextInput->setObjectName(QStringLiteral("ipTextInput"));
        ipTextInput->setGeometry(QRect(110, 130, 113, 25));
        portTextInput = new QLineEdit(centralWidget);
        portTextInput->setObjectName(QStringLiteral("portTextInput"));
        portTextInput->setGeometry(QRect(110, 180, 113, 25));
        client_connector->setCentralWidget(centralWidget);
        background->raise();
        portBoxLabel->raise();
        logoWorms->raise();
        connectButton->raise();
        exitButton->raise();
        portLabel->raise();
        ipBoxLabel->raise();
        ipLabel->raise();
        nameBoxLabel->raise();
        playerNameLabel->raise();
        playerNameInput->raise();
        ipTextInput->raise();
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
        client_connector->setWindowTitle(QApplication::translate("client_connector", "Worms - Cliente", 0));
#ifndef QT_NO_ACCESSIBILITY
        client_connector->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        connectButton->setText(QApplication::translate("client_connector", "Connect", 0));
        exitButton->setText(QApplication::translate("client_connector", "Exit", 0));
        ipLabel->setText(QApplication::translate("client_connector", "<html><head/><body><p><span style=\" font-weight:600; color:#000000;\">Host / IP</span></p></body></html>", 0));
        portLabel->setText(QApplication::translate("client_connector", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600; color:#000000;\">Port</span></p></body></html>", 0));
        logoWorms->setText(QString());
        background->setText(QString());
        portBoxLabel->setText(QString());
        playerNameLabel->setText(QApplication::translate("client_connector", "<html><head/><body><p><span style=\" font-weight:600; color:#000000;\"> Name</span></p></body></html>", 0));
        ipBoxLabel->setText(QString());
        nameBoxLabel->setText(QString());
        playerNameInput->setText(QApplication::translate("client_connector", "player", 0));
        ipTextInput->setText(QApplication::translate("client_connector", "localhost", 0));
        portTextInput->setText(QApplication::translate("client_connector", "8080", 0));
    } // retranslateUi

};

namespace Ui {
    class client_connector: public Ui_client_connector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_CONNECTOR_H
