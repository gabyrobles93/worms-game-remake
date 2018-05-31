#include "editor_launcher.h"
#include "ui_editor_launcher.h"

EditorLauncher::EditorLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorLauncher)
{
    ui->setupUi(this);
}

EditorLauncher::~EditorLauncher()
{
    delete ui;
}

void EditorLauncher::connectEvents(void) {
    // Conecto el evento del boton exit

    QPushButton* exitLobbyButton = findChild<QPushButton*>("exitLobbyButton");
    QObject::connect(exitLobbyButton, &QPushButton::clicked,
                    this, &client_lobby::close);

    // Conecto el evento del boton join
    QPushButton* joinGameButton = findChild<QPushButton*>("joinGameButton");
    QObject::connect(joinGameButton, &QPushButton::clicked,
                     this, &client_lobby::close);

    // Conecto el evento del boton create
    QPushButton* createGameButton = findChild<QPushButton*>("createGameButton");
    QObject::connect(createGameButton, &QPushButton::clicked,
                     this, &client_lobby::close);
}
