#ifndef REPOSCROLL_H
#define REPOSCROLL_H

#include <QScrollArea>

#include "../systemtree/systemtree.h"
#include "repobuttons.h"


class RepoScroll : public QScrollArea
{
    Q_OBJECT
public:
    RepoScroll(QWidget *parent);

    void print(QList<RepoButtons *>);

    ~RepoScroll();

private slots:
    void renew(size_t numDir);
};

#endif // REPOSCROLL_H
