#ifndef EDITOR_LAUNCHER_H
#define EDITOR_LAUNCHER_H

#include <QMainWindow>
#include <string>
#include "yaml.h"

namespace Ui {
class EditorLauncher;
}

class EditorLauncher : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorLauncher(QWidget *parent = 0);
    ~EditorLauncher();

private:
    Ui::EditorLauncher *ui;
    std::string background_path;
    bool background_choosed;
    std::string background_mode;
    int water_level;
    int teams_amount;
    int worms_health;
    std::map<int, size_t> weapons_ammo;
    size_t mortar_ammo;
    size_t red_bomb_ammo;
    size_t banana_ammo;
    size_t green_bomb_ammo;
    size_t holy_bomb_ammo;
    size_t dynamite_ammo;
    size_t fly_bombs_ammo;
    size_t teleport_ammo;
    size_t bat_ammo;

    void connectEvents(void);
    void chooseBackground(void);
    void goCreate(void);
    void launchEditor(YAML::Node, std::string &);
};

#endif // EDITOR_LAUNCHER_H
