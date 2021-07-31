#ifndef REPOSCROLL_H
#define REPOSCROLL_H

#include <QScrollArea>

#include "../regulations/systemreg.h"
#include "../regulations/workflow.h"
#include "repobuttons.h"


class RepoScroll : public QScrollArea
{
    Q_OBJECT
public:
    RepoScroll(QWidget *parent, const QString path = systemregulation::dirName.folderSig.value(systemregulation::FolderType::ROOT));
    ~RepoScroll();

signals:
    void repoChosen(ssize_t numSubsection);

private slots:
    void renew(workflow::DataLevel toLevel);


private:
    RepoButtons *_repos;

    workflow::DataLevel _newLevel;
};

#endif // REPOSCROLL_H
