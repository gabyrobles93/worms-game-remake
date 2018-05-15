/********************************************************************************
** Form generated from reading UI file 'client_lobby.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_LOBBY_H
#define UI_CLIENT_LOBBY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_client_lobby
{
public:
    QLabel *lobbyBackground;
    QLabel *lobbyGamesImage;
    QPushButton *exitLobbyButton;
    QPushButton *createGameButton;
    QPushButton *joinGameButton;
    QTableWidget *gamesTable;
    QLabel *label;
    QLabel *playerName;

    void setupUi(QWidget *client_lobby)
    {
        if (client_lobby->objectName().isEmpty())
            client_lobby->setObjectName(QStringLiteral("client_lobby"));
        client_lobby->resize(720, 430);
        client_lobby->setMinimumSize(QSize(720, 430));
        client_lobby->setMaximumSize(QSize(720, 430));
        lobbyBackground = new QLabel(client_lobby);
        lobbyBackground->setObjectName(QStringLiteral("lobbyBackground"));
        lobbyBackground->setGeometry(QRect(-180, 0, 1131, 491));
        lobbyBackground->setTextFormat(Qt::RichText);
        lobbyBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/lobby_background.jpg")));
        lobbyBackground->setScaledContents(true);
        lobbyGamesImage = new QLabel(client_lobby);
        lobbyGamesImage->setObjectName(QStringLiteral("lobbyGamesImage"));
        lobbyGamesImage->setGeometry(QRect(30, 20, 201, 91));
        lobbyGamesImage->setTextFormat(Qt::RichText);
        lobbyGamesImage->setPixmap(QPixmap(QString::fromUtf8(":/images/lobby_games.png")));
        lobbyGamesImage->setScaledContents(true);
        exitLobbyButton = new QPushButton(client_lobby);
        exitLobbyButton->setObjectName(QStringLiteral("exitLobbyButton"));
        exitLobbyButton->setGeometry(QRect(30, 380, 89, 25));
        createGameButton = new QPushButton(client_lobby);
        createGameButton->setObjectName(QStringLiteral("createGameButton"));
        createGameButton->setGeometry(QRect(450, 390, 101, 25));
        joinGameButton = new QPushButton(client_lobby);
        joinGameButton->setObjectName(QStringLiteral("joinGameButton"));
        joinGameButton->setGeometry(QRect(590, 390, 89, 25));
        gamesTable = new QTableWidget(client_lobby);
        if (gamesTable->columnCount() < 3)
            gamesTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setText(QStringLiteral("Game"));
        gamesTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setText(QStringLiteral("Creator"));
        gamesTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setText(QStringLiteral("Players"));
        gamesTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        gamesTable->setObjectName(QStringLiteral("gamesTable"));
        gamesTable->setGeometry(QRect(30, 80, 451, 192));
        gamesTable->setMinimumSize(QSize(451, 192));
        gamesTable->setMaximumSize(QSize(451, 192));
        gamesTable->setSortingEnabled(true);
        gamesTable->setRowCount(0);
        gamesTable->setColumnCount(3);
        label = new QLabel(client_lobby);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 280, 81, 17));
        label->setTextFormat(Qt::RichText);
        playerName = new QLabel(client_lobby);
        playerName->setObjectName(QStringLiteral("playerName"));
        playerName->setGeometry(QRect(260, 280, 67, 17));

        retranslateUi(client_lobby);

        QMetaObject::connectSlotsByName(client_lobby);
    } // setupUi

    void retranslateUi(QWidget *client_lobby)
    {
        client_lobby->setWindowTitle(QApplication::translate("client_lobby", "Form", 0));
        lobbyBackground->setText(QString());
        lobbyGamesImage->setText(QString());
        exitLobbyButton->setText(QApplication::translate("client_lobby", "Exit", 0));
        createGameButton->setText(QApplication::translate("client_lobby", "Create Game", 0));
        joinGameButton->setText(QApplication::translate("client_lobby", "Join Game", 0));
        label->setText(QApplication::translate("client_lobby", "<html><head/><body><p><span style=\" font-weight:600;\">Welcome:</span></p></body></html>", 0));
        playerName->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class client_lobby: public Ui_client_lobby {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_LOBBY_H
