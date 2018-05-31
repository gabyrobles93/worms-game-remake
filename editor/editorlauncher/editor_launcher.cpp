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
