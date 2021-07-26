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
}

#endif // WORKFLOW_H
