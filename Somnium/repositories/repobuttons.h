#ifndef REPOBUTTONS_H
#define REPOBUTTONS_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDir>

#include "repoplacement.h"
#include "../regulations/systemreg.h"
#include "../regulations/workflow.h"

class RepoButtons : public QWidget
{
    Q_OBJECT
public:
    RepoButtons(QWidget *parent, const QString path);

    void recollect(workflow::DataLevel inLevel);

    ~RepoButtons();

protected:


signals:
    void dirChanged(workflow::DataLevel toLevel);  // chosenDir in <1 ... n> as in real Data
    //void noteCreated(.../*pseudopath or QDir*/);

private:
    QGridLayout *_foldersLayout;
    QList<QPushButton *> *_folders;

    QDir _currentDir;
};

#endif // REPOBUTTONS_H
