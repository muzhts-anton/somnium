#include <QDir>

#include "reposcroll.h"


RepoScroll::RepoScroll(QWidget *parent, const QString path)
    : QScrollArea(parent)
{
    _repos = new RepoButtons(this, path);
    this->setWidget(_repos);

    _newLevel = workflow::DataLevel::IN_ROOT;

    connect(this->_repos, &RepoButtons::dirChanged, this, &RepoScroll::renew);
}


void RepoScroll::renew(workflow::DataLevel newLevel)
{
    if(newLevel == workflow::DataLevel::IN_SUBSECTION) {
        qDebug() << "the subsection level reached successfully";
        exit(5553535);
    }

    _repos->recollect(newLevel);
}

RepoScroll::~RepoScroll()
{
    delete _repos;
}
