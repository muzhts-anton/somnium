#ifndef WORKFLOW_H
#define WORKFLOW_H

#include <QMap>


namespace workflow {
    enum class MainWorkspacePage {
        REPO = 0,
        TXTEDIT,
    };

    const QMap<MainWorkspacePage, int> workspacePage = {{MainWorkspacePage::REPO, 0},
                                                        {MainWorkspacePage::TXTEDIT, 1}};


    enum class DataLevel {
        IN_ROOT = -1,
        IN_BOOK,
        IN_CHAPTER,
        IN_SUBSECTION,
    };


    DataLevel levelUp(DataLevel level);  // move level closer to root

    DataLevel levelDown(DataLevel level);  // move level closer to subsection
}

#endif // WORKFLOW_H
