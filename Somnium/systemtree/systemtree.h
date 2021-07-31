#ifndef SYSTEMTREE_H
#define SYSTEMTREE_H

#include <QString>
#include <QVariant>

#include "regulations/systemreg.h"

#include "workfiles/bookfile/lowbookfile.h"
#include "workfiles/bookfile/highbookfile.h"

#include "workfiles/commfile/lowcommfile.h"
#include "workfiles/commfile/highcommfile.h"

#include "workfiles/legfile/legendfile.h"


typedef struct {
    LowBookFile *bookfile;
    LowCommFile *commfile;
} lowlevelfiles_t;

Q_DECLARE_METATYPE(lowlevelfiles_t)

typedef struct {
    HighBookFile *bookfile;
    HighCommFile *commfile;
} highlevelfiles_t;

Q_DECLARE_METATYPE(highlevelfiles_t)


class DataTree
{
public:
    DataTree(const QString rootPath = systemregulation::dirName.folderSig.value(systemregulation::FolderType::ROOT));

    DataTree *getFolderTree();

    QString getRootPath();

    // ??? {
    void addSubsection(size_t bookNum, size_t chapterNum);
    void addChapter(size_t bookNum);
    void addBook();

    void removeSubsection(size_t num = 0);
    void removeChapter(size_t num = 0);
    void removeBook(size_t num = 0);
    // ??? }

    // void ();

    ~DataTree();

protected:
    void deleteNode(DataTree *node = nullptr);
    void setParent(DataTree * const parent = nullptr);

private slots:
    void noteCreated(...);  // TODO(Tony): implement and connect it

private:
    QString _rootPath;

    DataTree *_rootNode;
    DataTree *_up;
    QList<DataTree *> _subNode;

    LegendFile *_legfile;

    QVariant _levelfiles;
};

#endif // SYSTEMTREE_H
