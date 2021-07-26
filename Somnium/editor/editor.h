#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

#include "../systemtree/systemtree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();

private slots:
    void on_openRepoButton_clicked();

private:
    Ui::Editor *_ui;
    DataTree *_database;
};
#endif // EDITOR_H
