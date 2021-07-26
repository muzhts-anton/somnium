#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include "systemtree.h"
#include "regulations/systemreg.h"


DataTree::DataTree(const QString rootPath) : _rootPath(rootPath)
                                           , _rootNode(nullptr)
                                           , _up(nullptr)
                                           , _legfile(nullptr)
                                           , _levelfiles(0)
{
    this->_subNode = {};
}

QString DataTree::getRootPath()
{
    return _rootPath;
}

void DataTree::setParent(DataTree * const parent)
{
    this->_rootNode = parent->_rootNode;
    this->_up = parent;
    parent->_subNode.append(this);
}

static DataTree *errorInFolderTree(size_t error)
{
    qDebug() << "Error " << error << " DATATREE class GETFOLDERTREE function";
    return (DataTree *)nullptr;
}


// FIXME(Tony): release add-opportunity
// Ну ваще, наверно тут ничего добавлять и не надо. тут только создаю, а добавлять/удалять - другие задачи => другие методы.
// А еще когда создается первая заметка с соответсвующим каталогом должны быть все папки в пути. хотя бы по одной шт. так что если нет, то это рил ошибка. НИФИГА :: УДАЛЕНИЕ!
DataTree *DataTree::getFolderTree() {
    this->_rootNode = this;

    QDir currentDir(_rootPath);
    if(!currentDir.exists())
        return errorInFolderTree(0);

    unsigned short numBook = 1;
    if(!currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::BOOK) + QString::number(numBook))) {
        return errorInFolderTree(11);
    }

    while(currentDir.cdUp(), currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::BOOK) + QString::number(numBook))) {
        DataTree *currentBook = new DataTree;
        currentBook->setParent(this);

        highlevelfiles_t inBookFiles;

        /* * file-filling part * */
        /* .bk */
        QString workFile = systemregulation::dirName.total.value(systemregulation::FileType::BOOK);
        if(!QFileInfo(currentDir, workFile).exists()) {
            return errorInFolderTree(101);  // FIXME(Tony): no return in loop
        }
        inBookFiles.bookfile = new HighBookFile(numBook, -1, -1);

        /* .cmt */
        workFile = systemregulation::dirName.total.value(systemregulation::FileType::COMMS);
        if(!QFileInfo(currentDir, workFile).exists())
            return errorInFolderTree(102);
        inBookFiles.commfile = new HighCommFile(numBook, -1, -1);

        /* .lgnd */
        workFile = systemregulation::dirName.total.value(systemregulation::FileType::LEGEND);
        if(!QFileInfo(currentDir, workFile).exists())
            return errorInFolderTree(102);
        currentBook->_legfile = new LegendFile(numBook, -1, -1);


        this->_levelfiles = QVariant::fromValue(inBookFiles);

        /* * chapter-filling part * */

        unsigned short numChapter = 1;
        if(!currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::CHAPTER) + QString::number(numChapter)))
            return errorInFolderTree(21);


        while(currentDir.cdUp(), currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::CHAPTER) + QString::number(numChapter))) {
            DataTree *currentChapter = new DataTree;
            currentChapter->setParent(this->_subNode.at(numBook - 1));

            highlevelfiles_t inChapterFiles;

            /* * file-filling part * */
            /* .bk */
            workFile = systemregulation::dirName.sectional.value(systemregulation::FileType::BOOK);
            if(!QFileInfo(currentDir, workFile).exists())
                return errorInFolderTree(201);
            inChapterFiles.bookfile = new HighBookFile(numBook, numChapter, -1);

            /* .cmt */
            workFile = systemregulation::dirName.sectional.value(systemregulation::FileType::COMMS);
            if(!QFileInfo(currentDir, workFile).exists())
                return errorInFolderTree(203);
            inChapterFiles.commfile = new HighCommFile(numBook, numChapter, -1);


            this->_subNode.at(numBook - 1)->_levelfiles = QVariant::fromValue(inChapterFiles);

            /* * subsection-filling part * */

            unsigned short numSubsection = 1;
            if(!currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::SUBSECTION) + QString::number(numSubsection)))
                return errorInFolderTree(31);  // FIXME


            while(currentDir.cdUp(), currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::SUBSECTION) + QString::number(numSubsection))) {
                DataTree *currentSubsection = new DataTree;
                currentSubsection->setParent(this->_subNode.at(numBook - 1)->_subNode.at(numChapter - 1));

                lowlevelfiles_t inSubsectionFiles;

                /* * file-filling part * */
                /* .bk */
                workFile = systemregulation::dirName.subsectional.value(systemregulation::FileType::BOOK);
                if(!QFileInfo(currentDir, workFile).exists())
                    return errorInFolderTree(301);
                inSubsectionFiles.bookfile = new LowBookFile(numBook, numChapter, numSubsection);

                /* .cmt */
                workFile = systemregulation::dirName.subsectional.value(systemregulation::FileType::COMMS);
                if(!QFileInfo(currentDir, workFile).exists())
                    return errorInFolderTree(303);
                inSubsectionFiles.commfile = new LowCommFile(numBook, numChapter, numSubsection);


                this->_subNode.at(numBook - 1)->_subNode.at(numChapter - 1)->_levelfiles = QVariant::fromValue(inSubsectionFiles);

                ++numSubsection;
            }

            ++numChapter;
        }

        ++numBook;
    }

    return _rootNode;  // maybe ->void? or this is the way to initialize?
}

void DataTree::deleteNode(DataTree *node)
{
    if(node) {
        if(node->_subNode.size()) {
            for(int currentNodeNum = 0; currentNodeNum < node->_subNode.size(); ++currentNodeNum)
                deleteNode(node->_subNode.at(currentNodeNum));
        }

        if(node->_levelfiles.canConvert<highlevelfiles_t>()) {
            delete node->_levelfiles.value<highlevelfiles_t>().bookfile;
            delete node->_levelfiles.value<highlevelfiles_t>().commfile;
        } else if(node->_levelfiles.canConvert<lowlevelfiles_t>()) {
            delete node->_levelfiles.value<lowlevelfiles_t>().bookfile;
            delete node->_levelfiles.value<lowlevelfiles_t>().commfile;
        }

        if(node->_legfile)
            delete node->_legfile;
    }
}


void DataTree::addSubsection(size_t bookNum, size_t chapterNum)
{
    if(bookNum == 0 || chapterNum == 0)
        exit(911);

    QDir currentDir(systemregulation::dirName.folderSig.value(systemregulation::FolderType::ROOT));
    if(!currentDir.exists())
        exit(912);

    currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::BOOK) + QString::number(bookNum));
    currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::CHAPTER) + QString::number(chapterNum));

    size_t subsectionNum = 1;
    while(currentDir.exists(systemregulation::dirName.folderSig.value(systemregulation::FolderType::SUBSECTION) + QString::number(subsectionNum)))
        ++subsectionNum;

    currentDir.mkdir(systemregulation::dirName.folderSig.value(systemregulation::FolderType::SUBSECTION) + QString::number(subsectionNum));
    currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::SUBSECTION) + QString::number(subsectionNum));

    QString filepath = currentDir.path() + "/";

    QFile bookfile(filepath + systemregulation::dirName.subsectional.value(systemregulation::FileType::BOOK));
    if(!bookfile.open(QFile::WriteOnly))
            exit(922);

    QFile commfile(filepath + systemregulation::dirName.subsectional.value(systemregulation::FileType::COMMS));
    if(!commfile.open(QFile::WriteOnly))
            exit(923);

    QFile legfile(filepath + systemregulation::dirName.subsectional.value(systemregulation::FileType::LEGEND));
    if(!legfile.open(QFile::WriteOnly))
            exit(924);

    currentDir.cdUp();
    qDebug()<<currentDir.rmdir(systemregulation::dirName.folderSig.value(systemregulation::FolderType::SUBSECTION) + QString::number(subsectionNum));
}

DataTree::~DataTree()
{
    if(this != _rootNode)
        qDebug() << "Hmm smth strange -_- in dtor DATATREE class";
    this->deleteNode(_rootNode);
}
