#include <iostream>
#include <QFileDialog>
#include "editor_launcher.h"
#include "types.h"
#include "ui_editor_launcher.h"

EditorLauncher::EditorLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorLauncher)
{
    ui->setupUi(this);
    this->background_choosed = false;
    connectEvents();
}

EditorLauncher::~EditorLauncher()
{
    delete ui;
}

void EditorLauncher::connectEvents(void) {
    // Conecto el evento del boton exit

    QPushButton* choose_background = findChild<QPushButton*>("background_path");
    QObject::connect(choose_background, &QPushButton::clicked,
                     this, &EditorLauncher::chooseBackground);

    QPushButton* go_create = findChild<QPushButton*>("go_create");
    QObject::connect(go_create, &QPushButton::clicked,
                     this, &EditorLauncher::goCreate);
}

void EditorLauncher::chooseBackground(void) {
    QString bg_path;
    bg_path = QFileDialog::getOpenFileName(this, tr("Choose Background"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    this->background_path = bg_path.toUtf8().constData();
    QLabel* label_background_path = findChild<QLabel*>("label_background_path");
    label_background_path->setText(bg_path);
    this->background_choosed = true;
}

void EditorLauncher::goCreate(void) {

    QString error_msg;
    bool error = false;

    this->weapons_ammo[w_mortar] = findChild<QSpinBox*>("mortar_ammo")->value();
    this->weapons_ammo[w_red_bomb] = findChild<QSpinBox*>("red_bomb_ammo")->value();
    this->weapons_ammo[w_banana] = findChild<QSpinBox*>("banana_ammo")->value();
    this->weapons_ammo[w_green_bomb] = findChild<QSpinBox*>("green_bomb_ammo")->value();
    this->weapons_ammo[w_holy_bomb] = findChild<QSpinBox*>("holy_bomb_ammo")->value();
    this->weapons_ammo[w_dynamite] = findChild<QSpinBox*>("dynamite_ammo")->value();
    this->weapons_ammo[w_fly_bomb] = findChild<QSpinBox*>("fly_bombs_ammo")->value();
    this->weapons_ammo[w_teleport] = findChild<QSpinBox*>("teleport_ammo")->value();
    this->weapons_ammo[w_bat] = findChild<QSpinBox*>("bat_ammo")->value();

    this->water_level = findChild<QSpinBox*>("water_level")->value();
    this->teams_amount = findChild<QSpinBox*>("teams_amount")->value();
    this->worms_health = findChild<QSpinBox*>("worms_health")->value();
    this->background_mode = findChild<QComboBox*>("background_options")->currentText();

    if (!this->background_choosed) {
        error_msg += "Choose a background! \n";
        error = true;
    }

    if (findChild<QComboBox*>("background_options")->currentText() == "Background Options") {
        error_msg += "Background option is missing.";
        error = true;
    }

    if (error = true) {
        findChild<QLabel*>("label_errors")->setText(error_msg);
    }

    launchEditor(this->background_path,
                this->background_mode,
                this->water_level,
                this->teams_amount,
                this->worms_health,
                this->weapons_ammo)
}
