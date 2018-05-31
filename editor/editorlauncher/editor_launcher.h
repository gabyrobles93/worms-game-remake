#ifndef EDITOR_LAUNCHER_H
#define EDITOR_LAUNCHER_H

#include <QMainWindow>

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
};

#endif // EDITOR_LAUNCHER_H
