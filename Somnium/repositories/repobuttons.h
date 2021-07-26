#ifndef REPOBUTTONS_H
#define REPOBUTTONS_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

#include "repoplacement.h"
#include "../regulations/systemreg.h"


class RepoButtons : public QWidget
{
    Q_OBJECT
public:
    RepoButtons(QWidget *parent, const QString path = systemregulation::dirName.folderSig.value(systemregulation::FolderType::ROOT));
    ~RepoButtons();

signals:
    void renew(size_t numDir);

private slots:
    void sendRenew();

private:
    void collect(const QString path);

private:
    QGridLayout *_foldersLayout;
    QList<QPushButton *> *_folders;
};

#endif // REPOBUTTONS_H
