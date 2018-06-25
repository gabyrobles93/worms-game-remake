#include <iostream>
#include <fstream>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <sstream>
#include <QLineEdit>
#include "editor_launcher.h"
#include "types.h"
#include "ui_editor_launcher.h"
#include "yaml.h"
#include "editor.h"

#define DEFAULT_AMMO_QTY 10
#define DEFAULT_WORMS_HEALTH 200
#define DEFAULT_TEAMS_AMOUNT 2
#define DEFAULT_WATER_LEVEL 300

#define DEFAULT_SAVED_MAPS_PATH "/usr/etc/worms/maps/"
#define MAPS_EXT ".yml"

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

    QAction* load_and_edit = findChild<QAction*>("actionLoad_and_Edit");
    QObject::connect(load_and_edit, &QAction::triggered, this, &EditorLauncher::loadAndEdit);

    QAction* create_new_map = findChild<QAction*>("actionNew_map");
    QObject::connect(create_new_map, &QAction::triggered, this, &EditorLauncher::createNewMap);
}

void EditorLauncher::chooseBackground(void) {
    QString bg_path;
    bg_path = QFileDialog::getOpenFileName(this, tr("Choose Background"), "/home", tr("Image Files (*.png)"));
    this->background_path = bg_path.toUtf8().constData();
    QLabel* label_background_path = findChild<QLabel*>("label_background_path");
    label_background_path->setText(bg_path);
    if (bg_path.length() > 0) {
        this->background_choosed = true;
        QFileInfo bg_info(bg_path);
        this->background_name = bg_info.fileName().toUtf8().constData();
    }
}

void EditorLauncher::goCreate(void) {

    QString error_msg;
    bool error = false;
    std::string map_name;
    YAML::Node mapNode;

    if (!this->background_choosed) {
        error_msg += "Choose a background! \n";
        error = true;
    }

    if (findChild<QComboBox*>("background_options")->currentText() == "Background Options") {
        error_msg += "Background option is missing.\n";
        error = true;
    }

    if (findChild<QLineEdit*>("map_name")->text().length() == 0) {
        error_msg += "Write a map name!.\n";
    }

    if (error == true) {
        findChild<QLabel*>("label_errors")->setText(error_msg);
        return;
    }

    map_name = findChild<QLineEdit*>("map_name")->text().toUtf8().constData();
    mapNode["static"]["background"]["file"] = this->background_path;
    mapNode["static"]["background"]["display"] = findChild<QComboBox*>("background_options")->currentText().toUtf8().constData();
    mapNode["static"]["water_level"] = findChild<QSpinBox*>("water_level")->value();
    mapNode["static"]["teams_amount"] = findChild<QSpinBox*>("teams_amount")->value();
    mapNode["static"]["worms_health"] = findChild<QSpinBox*>("worms_health")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_bazooka)]["item_name"] = "Bazooka";
    mapNode["static"]["init_inventory"][std::to_string(w_bazooka)]["supplies"] = findChild<QSpinBox*>("bazooka_ammo")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_mortar)]["item_name"] = "Mortar";
    mapNode["static"]["init_inventory"][std::to_string(w_mortar)]["supplies"] = findChild<QSpinBox*>("mortar_ammo")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_cluster)]["item_name"] = "Cluster";
    mapNode["static"]["init_inventory"][std::to_string(w_cluster)]["supplies"] = findChild<QSpinBox*>("red_bomb_ammo")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_banana)]["item_name"] = "Banana";
    mapNode["static"]["init_inventory"][std::to_string(w_banana)]["supplies"] = findChild<QSpinBox*>("banana_ammo")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_green_grenade)]["item_name"] = "Grenade";
    mapNode["static"]["init_inventory"][std::to_string(w_green_grenade)]["supplies"] = findChild<QSpinBox*>("green_bomb_ammo")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_holy_grenade)]["item_name"] = "Holy bomb";
    mapNode["static"]["init_inventory"][std::to_string(w_holy_grenade)]["supplies"] = findChild<QSpinBox*>("holy_bomb_ammo")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_dynamite)]["item_name"] = "Dynamite";
    mapNode["static"]["init_inventory"][std::to_string(w_dynamite)]["supplies"] = findChild<QSpinBox*>("dynamite_ammo")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_air_strike)]["item_name"] = "Air Strike";
    mapNode["static"]["init_inventory"][std::to_string(w_air_strike)]["supplies"] = findChild<QSpinBox*>("fly_bombs_ammo")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_teleport)]["item_name"] = "Teleport";
    mapNode["static"]["init_inventory"][std::to_string(w_teleport)]["supplies"] = findChild<QSpinBox*>("teleport_ammo")->value();

    mapNode["static"]["init_inventory"][std::to_string(w_bat)]["item_name"] = "Bat";
    mapNode["static"]["init_inventory"][std::to_string(w_bat)]["supplies"] = findChild<QSpinBox*>("bat_ammo")->value();

    std::string map_path = DEFAULT_SAVED_MAPS_PATH + map_name + MAPS_EXT;

/*     std::stringstream ss;
    ss << mapNode;
    std::cout << ss.str() << std::endl; */

    launchEditor(mapNode, map_name);
}

void EditorLauncher::launchEditor(YAML::Node mapNode, std::string & map_name) {
    std::cout << "About to construct the_editor" << std::endl;
    Editor the_editor(mapNode, map_name, this->background_name);
    std::cout << "Finish constructing the_editor" << std::endl;
    this->hide();
    int err_code;
    err_code = the_editor.start();
    if (err_code == 0) {
        std::string maps_path(DEFAULT_SAVED_MAPS_PATH);
        std::string cmd_cp_background = "cp  \"" + this->background_path + "\" " + maps_path + "background.png";
        std::system(cmd_cp_background.c_str());
        std::string cmd_tar_gz = "tar -zcf \"" + maps_path + map_name + ".tar.gz\" --directory=" + maps_path + " map.yml background.png";
        std::system(cmd_tar_gz.c_str());
        std::string cmd_rmv_temp = "rm " + maps_path + "background.png " + maps_path + "map.yml";
        std::system(cmd_rmv_temp.c_str());
    }
    this->close();
}

void EditorLauncher::loadAndEdit(void) {
    //YAML::Node mapNode;
    //mapNode = YAML::Load();
    //launchEditor(mapNode, map_name);
    //std::cout << "Se carga un mapa existente para editarlo." << std::endl;
}

void EditorLauncher::createNewMap(void) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Crear nuevo mapa");
    msgBox.setText("Perderá los cambios actuales. ¿Está seguro que desea reiniciar la configuración actual?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if(msgBox.exec() == QMessageBox::No) {
        return;
    }
    findChild<QLineEdit*>("map_name")->clear();
    findChild<QLabel*>("label_background_path")->clear();
    findChild<QComboBox*>("background_options")->setCurrentIndex(0);
    findChild<QSpinBox*>("water_level")->setValue(DEFAULT_WATER_LEVEL);
    findChild<QSpinBox*>("teams_amount")->setValue(DEFAULT_TEAMS_AMOUNT);
    findChild<QSpinBox*>("worms_health")->setValue(DEFAULT_WORMS_HEALTH);

    findChild<QSpinBox*>("mortar_ammo")->setValue(DEFAULT_AMMO_QTY);
    findChild<QSpinBox*>("red_bomb_ammo")->setValue(DEFAULT_AMMO_QTY);
    findChild<QSpinBox*>("banana_ammo")->setValue(DEFAULT_AMMO_QTY);
    findChild<QSpinBox*>("green_bomb_ammo")->setValue(DEFAULT_AMMO_QTY);
    findChild<QSpinBox*>("holy_bomb_ammo")->setValue(DEFAULT_AMMO_QTY);
    findChild<QSpinBox*>("dynamite_ammo")->setValue(DEFAULT_AMMO_QTY);
    findChild<QSpinBox*>("fly_bombs_ammo")->setValue(DEFAULT_AMMO_QTY);
    findChild<QSpinBox*>("teleport_ammo")->setValue(DEFAULT_AMMO_QTY);
    findChild<QSpinBox*>("bat_ammo")->setValue(DEFAULT_AMMO_QTY);
    findChild<QSpinBox*>("bazooka_ammo")->setValue(DEFAULT_AMMO_QTY);

    this->background_path.clear();
    this->background_name.clear();
    this->background_choosed = false;
    this->background_mode.clear();
    this->water_level = DEFAULT_WATER_LEVEL;
    this->teams_amount = DEFAULT_TEAMS_AMOUNT;
    this->worms_health = DEFAULT_WORMS_HEALTH;

}