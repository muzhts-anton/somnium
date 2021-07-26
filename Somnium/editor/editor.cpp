#include "editor.h"
#include "ui_editor.h"
#include "regulations/workflow.h"

Editor::Editor(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::Editor)
{
    this->_ui->setupUi(this);
    this->_database = new DataTree;
    _database->getFolderTree();
}

Editor::~Editor()
{
    delete _ui;
}


void Editor::on_openRepoButton_clicked()
{
    _ui->mainWorkSpace->setCurrentIndex(workflow::workspacePage.value(workflow::MainWorkspacePage::REPO));
}

