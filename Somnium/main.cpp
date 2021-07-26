#include "editor/editor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication mainApp(argc, argv);

    Editor txtEditor;
    txtEditor.show();

    return mainApp.exec();
}
