#include <QDir>

#include "reposcroll.h"


RepoScroll::RepoScroll(QWidget *parent)
    : QScrollArea(parent)
{

}

void RepoScroll::renew(size_t numDir)
{
    QDir currentDir(...);
}

RepoScroll::~RepoScroll() {}
