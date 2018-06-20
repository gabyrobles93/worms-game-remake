/********************************************************************************
** Form generated from reading UI file 'clientlobby.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTLOBBY_H
#define UI_CLIENTLOBBY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientLobby
{
public:
    QWidget *centralWidget;
    QStackedWidget *pages_client;
    QWidget *page_connection;
    QGroupBox *box_connection;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *text_player_name;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *text_ip;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *text_port;
    QPushButton *button_connect;
    QPushButton *button_clean;
    QLabel *label_11;
    QLabel *background_5;
    QWidget *page_lobby;
    QLabel *background;
    QPushButton *button_create;
    QPushButton *button_join;
    QPushButton *button_exit_lobby;
    QPushButton *button_refresh;
    QTableWidget *table_matchs;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *playerName;
    QLabel *label_12;
    QWidget *page_create_match;
    QPushButton *button_start;
    QPushButton *button_back_lobby;
    QGroupBox *groupBox_3;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *text_game_name;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QPushButton *button_changue_maps_folder;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QLabel *text_current_map_path;
    QLabel *label_14;
    QLabel *background_2;
    QWidget *page_waiting_match;
    QGroupBox *groupBox;
    QPushButton *button_start_waiting_match;
    QListWidget *list_waiting_players;
    QPushButton *button_refresh_waiting_players;
    QLabel *background_3;
    QLabel *label_8;
    QPushButton *button_cancel_waiting_match;
    QWidget *page_joined_waiting_match;
    QGroupBox *groupBox_2;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QLabel *text_game_creator;
    QPushButton *button_exit_waiting_match;
    QLabel *text_waiting_match_notification;
    QLabel *background_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ClientLobby)
    {
        if (ClientLobby->objectName().isEmpty())
            ClientLobby->setObjectName(QStringLiteral("ClientLobby"));
        ClientLobby->resize(666, 365);
        ClientLobby->setMinimumSize(QSize(666, 365));
        ClientLobby->setMaximumSize(QSize(666, 365));
        centralWidget = new QWidget(ClientLobby);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pages_client = new QStackedWidget(centralWidget);
        pages_client->setObjectName(QStringLiteral("pages_client"));
        pages_client->setGeometry(QRect(0, 0, 661, 321));
        page_connection = new QWidget();
        page_connection->setObjectName(QStringLiteral("page_connection"));
        box_connection = new QGroupBox(page_connection);
        box_connection->setObjectName(QStringLiteral("box_connection"));
        box_connection->setGeometry(QRect(240, 50, 291, 191));
        box_connection->setAutoFillBackground(true);
        horizontalLayoutWidget = new QWidget(box_connection);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 20, 271, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        text_player_name = new QLineEdit(horizontalLayoutWidget);
        text_player_name->setObjectName(QStringLiteral("text_player_name"));

        horizontalLayout->addWidget(text_player_name);

        horizontalLayoutWidget_2 = new QWidget(box_connection);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(9, 80, 271, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        text_ip = new QLineEdit(horizontalLayoutWidget_2);
        text_ip->setObjectName(QStringLiteral("text_ip"));

        horizontalLayout_2->addWidget(text_ip);

        horizontalLayoutWidget_3 = new QWidget(box_connection);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 140, 271, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        text_port = new QLineEdit(horizontalLayoutWidget_3);
        text_port->setObjectName(QStringLiteral("text_port"));

        horizontalLayout_3->addWidget(text_port);

        button_connect = new QPushButton(page_connection);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setGeometry(QRect(420, 250, 89, 25));
        button_clean = new QPushButton(page_connection);
        button_clean->setObjectName(QStringLiteral("button_clean"));
        button_clean->setGeometry(QRect(310, 250, 89, 25));
        button_clean->setAutoFillBackground(false);
        QIcon icon;
        QString iconThemeName = QStringLiteral("130");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        button_clean->setIcon(icon);
        label_11 = new QLabel(page_connection);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, -70, 211, 201));
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/resources/graphics/Lobby/worms_logo.png")));
        label_11->setScaledContents(true);
        background_5 = new QLabel(page_connection);
        background_5->setObjectName(QStringLiteral("background_5"));
        background_5->setGeometry(QRect(0, 0, 801, 391));
        background_5->setPixmap(QPixmap(QString::fromUtf8(":/resources/graphics/Lobby/lobby_background.jpg")));
        background_5->setScaledContents(true);
        pages_client->addWidget(page_connection);
        background_5->raise();
        box_connection->raise();
        button_connect->raise();
        label_11->raise();
        button_clean->raise();
        page_lobby = new QWidget();
        page_lobby->setObjectName(QStringLiteral("page_lobby"));
        background = new QLabel(page_lobby);
        background->setObjectName(QStringLiteral("background"));
        background->setGeometry(QRect(0, 0, 801, 391));
        background->setPixmap(QPixmap(QString::fromUtf8(":/resources/graphics/Lobby/lobby_background.jpg")));
        background->setScaledContents(true);
        button_create = new QPushButton(page_lobby);
        button_create->setObjectName(QStringLiteral("button_create"));
        button_create->setGeometry(QRect(40, 290, 89, 25));
        button_join = new QPushButton(page_lobby);
        button_join->setObjectName(QStringLiteral("button_join"));
        button_join->setGeometry(QRect(150, 290, 89, 25));
        button_exit_lobby = new QPushButton(page_lobby);
        button_exit_lobby->setObjectName(QStringLiteral("button_exit_lobby"));
        button_exit_lobby->setGeometry(QRect(560, 290, 89, 25));
        button_refresh = new QPushButton(page_lobby);
        button_refresh->setObjectName(QStringLiteral("button_refresh"));
        button_refresh->setGeometry(QRect(420, 250, 89, 25));
        table_matchs = new QTableWidget(page_lobby);
        if (table_matchs->columnCount() < 4)
            table_matchs->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_matchs->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_matchs->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_matchs->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_matchs->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        table_matchs->setObjectName(QStringLiteral("table_matchs"));
        table_matchs->setGeometry(QRect(20, 70, 511, 171));
        table_matchs->setMinimumSize(QSize(511, 171));
        table_matchs->setMaximumSize(QSize(511, 171));
        table_matchs->setTabKeyNavigation(false);
        table_matchs->setDragDropOverwriteMode(false);
        table_matchs->setAlternatingRowColors(true);
        table_matchs->setSelectionMode(QAbstractItemView::SingleSelection);
        table_matchs->setSelectionBehavior(QAbstractItemView::SelectRows);
        horizontalLayoutWidget_4 = new QWidget(page_lobby);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(290, 40, 201, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        playerName = new QLabel(horizontalLayoutWidget_4);
        playerName->setObjectName(QStringLiteral("playerName"));

        horizontalLayout_4->addWidget(playerName);

        label_12 = new QLabel(page_lobby);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 0, 231, 81));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/resources/graphics/Lobby/cooltext290412065827968.png")));
        label_12->setScaledContents(true);
        pages_client->addWidget(page_lobby);
        background->raise();
        button_create->raise();
        button_join->raise();
        button_exit_lobby->raise();
        button_refresh->raise();
        horizontalLayoutWidget_4->raise();
        label_12->raise();
        table_matchs->raise();
        page_create_match = new QWidget();
        page_create_match->setObjectName(QStringLiteral("page_create_match"));
        button_start = new QPushButton(page_create_match);
        button_start->setObjectName(QStringLiteral("button_start"));
        button_start->setGeometry(QRect(550, 280, 89, 25));
        button_back_lobby = new QPushButton(page_create_match);
        button_back_lobby->setObjectName(QStringLiteral("button_back_lobby"));
        button_back_lobby->setGeometry(QRect(428, 280, 101, 25));
        groupBox_3 = new QGroupBox(page_create_match);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 70, 411, 171));
        groupBox_3->setAutoFillBackground(true);
        horizontalLayoutWidget_6 = new QWidget(groupBox_3);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(10, 30, 251, 31));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(horizontalLayoutWidget_6);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        text_game_name = new QLineEdit(horizontalLayoutWidget_6);
        text_game_name->setObjectName(QStringLiteral("text_game_name"));

        horizontalLayout_6->addWidget(text_game_name);

        horizontalLayoutWidget_5 = new QWidget(groupBox_3);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 70, 191, 41));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(horizontalLayoutWidget_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        button_changue_maps_folder = new QPushButton(horizontalLayoutWidget_5);
        button_changue_maps_folder->setObjectName(QStringLiteral("button_changue_maps_folder"));

        horizontalLayout_5->addWidget(button_changue_maps_folder);

        button_changue_maps_folder->raise();
        label_5->raise();
        verticalLayoutWidget = new QWidget(groupBox_3);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 120, 401, 42));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        text_current_map_path = new QLabel(verticalLayoutWidget);
        text_current_map_path->setObjectName(QStringLiteral("text_current_map_path"));

        verticalLayout->addWidget(text_current_map_path);

        label_14 = new QLabel(page_create_match);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(30, 20, 271, 51));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/resources/graphics/Lobby/cooltext290412106171973.png")));
        label_14->setScaledContents(true);
        background_2 = new QLabel(page_create_match);
        background_2->setObjectName(QStringLiteral("background_2"));
        background_2->setGeometry(QRect(0, 0, 801, 391));
        background_2->setPixmap(QPixmap(QString::fromUtf8(":/resources/graphics/Lobby/lobby_background.jpg")));
        background_2->setScaledContents(true);
        pages_client->addWidget(page_create_match);
        background_2->raise();
        button_start->raise();
        button_back_lobby->raise();
        groupBox_3->raise();
        label_14->raise();
        page_waiting_match = new QWidget();
        page_waiting_match->setObjectName(QStringLiteral("page_waiting_match"));
        groupBox = new QGroupBox(page_waiting_match);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(50, 60, 321, 201));
        button_start_waiting_match = new QPushButton(groupBox);
        button_start_waiting_match->setObjectName(QStringLiteral("button_start_waiting_match"));
        button_start_waiting_match->setGeometry(QRect(210, 60, 101, 25));
        list_waiting_players = new QListWidget(groupBox);
        list_waiting_players->setObjectName(QStringLiteral("list_waiting_players"));
        list_waiting_players->setGeometry(QRect(30, 30, 171, 111));
        button_refresh_waiting_players = new QPushButton(groupBox);
        button_refresh_waiting_players->setObjectName(QStringLiteral("button_refresh_waiting_players"));
        button_refresh_waiting_players->setGeometry(QRect(210, 100, 89, 25));
        background_3 = new QLabel(page_waiting_match);
        background_3->setObjectName(QStringLiteral("background_3"));
        background_3->setGeometry(QRect(0, 0, 801, 391));
        background_3->setPixmap(QPixmap(QString::fromUtf8(":/resources/graphics/Lobby/lobby_background.jpg")));
        background_3->setScaledContents(true);
        label_8 = new QLabel(page_waiting_match);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 0, 371, 61));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/resources/graphics/Lobby/cooltext290413843260424.png")));
        label_8->setScaledContents(true);
        button_cancel_waiting_match = new QPushButton(page_waiting_match);
        button_cancel_waiting_match->setObjectName(QStringLiteral("button_cancel_waiting_match"));
        button_cancel_waiting_match->setGeometry(QRect(540, 270, 89, 25));
        pages_client->addWidget(page_waiting_match);
        background_3->raise();
        groupBox->raise();
        label_8->raise();
        button_cancel_waiting_match->raise();
        page_joined_waiting_match = new QWidget();
        page_joined_waiting_match->setObjectName(QStringLiteral("page_joined_waiting_match"));
        groupBox_2 = new QGroupBox(page_joined_waiting_match);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(100, 30, 471, 241));
        horizontalLayoutWidget_7 = new QWidget(groupBox_2);
        horizontalLayoutWidget_7->setObjectName(QStringLiteral("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(20, 40, 261, 41));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(horizontalLayoutWidget_7);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_7->addWidget(label_9);

        text_game_creator = new QLabel(horizontalLayoutWidget_7);
        text_game_creator->setObjectName(QStringLiteral("text_game_creator"));

        horizontalLayout_7->addWidget(text_game_creator);

        button_exit_waiting_match = new QPushButton(groupBox_2);
        button_exit_waiting_match->setObjectName(QStringLiteral("button_exit_waiting_match"));
        button_exit_waiting_match->setGeometry(QRect(350, 200, 89, 25));
        text_waiting_match_notification = new QLabel(groupBox_2);
        text_waiting_match_notification->setObjectName(QStringLiteral("text_waiting_match_notification"));
        text_waiting_match_notification->setGeometry(QRect(40, 120, 411, 17));
        background_4 = new QLabel(page_joined_waiting_match);
        background_4->setObjectName(QStringLiteral("background_4"));
        background_4->setGeometry(QRect(0, 0, 801, 391));
        background_4->setPixmap(QPixmap(QString::fromUtf8(":/resources/graphics/Lobby/lobby_background.jpg")));
        background_4->setScaledContents(true);
        pages_client->addWidget(page_joined_waiting_match);
        background_4->raise();
        groupBox_2->raise();
        ClientLobby->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ClientLobby);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ClientLobby->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ClientLobby);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ClientLobby->setStatusBar(statusBar);

        retranslateUi(ClientLobby);

        pages_client->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ClientLobby);
    } // setupUi

    void retranslateUi(QMainWindow *ClientLobby)
    {
        ClientLobby->setWindowTitle(QApplication::translate("ClientLobby", "ClientLobby", 0));
        box_connection->setTitle(QApplication::translate("ClientLobby", "Connect To Server", 0));
        label->setText(QApplication::translate("ClientLobby", "Player name: ", 0));
        text_player_name->setText(QApplication::translate("ClientLobby", "player", 0));
        label_2->setText(QApplication::translate("ClientLobby", "IP / Host:         ", 0));
        text_ip->setText(QApplication::translate("ClientLobby", "localhost", 0));
        label_4->setText(QApplication::translate("ClientLobby", "Port:               ", 0));
        text_port->setText(QApplication::translate("ClientLobby", "8080", 0));
        button_connect->setText(QApplication::translate("ClientLobby", "Connect", 0));
        button_clean->setText(QApplication::translate("ClientLobby", "Clean", 0));
        label_11->setText(QString());
        background_5->setText(QString());
        background->setText(QString());
        button_create->setText(QApplication::translate("ClientLobby", "Create", 0));
        button_join->setText(QApplication::translate("ClientLobby", "Join", 0));
        button_exit_lobby->setText(QApplication::translate("ClientLobby", "Exit", 0));
        button_refresh->setText(QApplication::translate("ClientLobby", "Refresh", 0));
        QTableWidgetItem *___qtablewidgetitem = table_matchs->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ClientLobby", "Partida", 0));
        QTableWidgetItem *___qtablewidgetitem1 = table_matchs->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ClientLobby", "Creador", 0));
        QTableWidgetItem *___qtablewidgetitem2 = table_matchs->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ClientLobby", "Participantes", 0));
        QTableWidgetItem *___qtablewidgetitem3 = table_matchs->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("ClientLobby", "Necesarios", 0));
        label_3->setText(QApplication::translate("ClientLobby", "Bienvenido ", 0));
        playerName->setText(QString());
        label_12->setText(QString());
        button_start->setText(QApplication::translate("ClientLobby", "Create", 0));
        button_back_lobby->setText(QApplication::translate("ClientLobby", "Back Lobby", 0));
        groupBox_3->setTitle(QApplication::translate("ClientLobby", "Match settings", 0));
        label_6->setText(QApplication::translate("ClientLobby", "Game name:", 0));
        label_5->setText(QApplication::translate("ClientLobby", "Map:", 0));
        button_changue_maps_folder->setText(QApplication::translate("ClientLobby", "Choose Map", 0));
        label_7->setText(QApplication::translate("ClientLobby", "Current Map:", 0));
        text_current_map_path->setText(QApplication::translate("ClientLobby", "Not selected. Please, choose a map!", 0));
        label_14->setText(QString());
        background_2->setText(QString());
        groupBox->setTitle(QApplication::translate("ClientLobby", "Waiting players list", 0));
        button_start_waiting_match->setText(QApplication::translate("ClientLobby", "Start Match!", 0));
        button_refresh_waiting_players->setText(QApplication::translate("ClientLobby", "Refresh", 0));
        background_3->setText(QString());
        label_8->setText(QString());
        button_cancel_waiting_match->setText(QApplication::translate("ClientLobby", "Cancel", 0));
        groupBox_2->setTitle(QApplication::translate("ClientLobby", "Esperando inicio de partida", 0));
        label_9->setText(QApplication::translate("ClientLobby", "Creador: ", 0));
        text_game_creator->setText(QString());
        button_exit_waiting_match->setText(QApplication::translate("ClientLobby", "Exit", 0));
        text_waiting_match_notification->setText(QString());
        background_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ClientLobby: public Ui_ClientLobby {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTLOBBY_H
