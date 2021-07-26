#include <QDir>

#include "repobuttons.h"


RepoButtons::RepoButtons(QWidget *parent, const QString path)
    : QWidget(parent)
{
    _folders = new QList<QPushButton *>;

    _foldersLayout = new QGridLayout(this);
    _foldersLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    this->collect(path);

    // connect(this, SIGNAL(sendRenew()), this->_folders->last(), SLOT(clicked()));
}

void RepoButtons::collect(const QString path)
{
    //QDir currentDir(path);
    //if(!currentDir.exists())
    //    return;

    //unsigned short numDir = 1;
    //if(!currentDir.cd(/* systemregulation::dirName.folderSig.value(systemregulation::FolderType::BOOK) + QString::number(numBook)) */)
    //    return;

    //while(currentDir.cdUp(), currentDir.cd(/* systemregulation::dirName.folderSig.value(systemregulation::FolderType::BOOK) + QString::number(numBook) */)) {

    //}
}

void RepoButtons::sendRenew()
{
    //emit renew(this->);
}

RepoButtons::~RepoButtons()
{
    delete _folders;
    delete _foldersLayout;
}
