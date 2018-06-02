#include "editor_launcher.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditorLauncher w;
    w.show();

    return a.exec();
}
