#include "repobuttons.h"


static systemregulation::FolderType defineReponame(workflow::DataLevel);
static void appendDir(QDir &, workflow::DataLevel, unsigned short);

RepoButtons::RepoButtons(QWidget *parent, const QString path)
    : QWidget(parent)
    , _currentDir(path)
{
    _folders = new QList<QPushButton *>;

    _foldersLayout = new QGridLayout(this);
    _foldersLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);


    if(!_currentDir.exists())
        return;

    RepoPlacement buttonPosition(0, 1);

    // FOLDERS
    unsigned short numDir = 1;

    while(_currentDir.exists(systemregulation::dirName.folderSig.value(systemregulation::FolderType::BOOK) + QString::number(numDir))) {
        _folders->append(new QPushButton(QString::number(numDir) + "[ as Qlist member: " + QString::number(numDir - 1) + "]" /* FIXME(Tony) */, this));
        _foldersLayout->addWidget(_folders->at(numDir - 1), buttonPosition.getRow(), buttonPosition.getColumn());

        connect(_folders->at(numDir - 1), &QPushButton::clicked, this, [numDir, this](){
            _currentDir.cd(systemregulation::dirName.folderSig.value(systemregulation::FolderType::BOOK) + QString::number(numDir));
            emit dirChanged(workflow::levelDown(workflow::DataLevel::IN_ROOT));
        });

        _folders->at(numDir - 1)->setStyleSheet("QPushButton{background: #E6E6FA; height: 75px;}");

        ++buttonPosition;
        ++numDir;
    }

    // NEW
    _folders->append(new QPushButton("new", this));
    _foldersLayout->addWidget(_folders->at(numDir - 1), 1, 0);

    _folders->at(numDir - 1)->setStyleSheet("QPushButton{background: #98FB98; height: 75px;}");

    connect(_folders->at(numDir - 1), &QPushButton::clicked, this, [numDir, this](){
        appendDir(_currentDir, workflow::levelDown(workflow::DataLevel::IN_ROOT), numDir);
        emit dirChanged(workflow::levelDown(workflow::DataLevel::IN_ROOT));
    });
}


void RepoButtons::recollect(workflow::DataLevel inLevel)
{
    for(size_t i = 0; (qsizetype)i < _folders->size(); ++i)
        delete _folders->at(i);
    delete _folders;
    _folders = new QList<QPushButton *>;

    // UP
    unsigned short numButton = 0;
    if(inLevel != workflow::DataLevel::IN_ROOT) {
        _folders->append(new QPushButton("up", this));
        _foldersLayout->addWidget(_folders->at(numButton), 0, 0);

        connect(_folders->at(numButton), &QPushButton::clicked, this, [inLevel, this](){
            _currentDir.cdUp();
            emit dirChanged(workflow::levelUp(inLevel));
        });

        _folders->at(numButton)->setStyleSheet("QPushButton{background: #FF6347; height: 75px;}");

        ++numButton;
    }

    RepoPlacement buttonPosition(0, 1);

    // FOLDERS
    unsigned short numDir = 1;

    systemregulation::FolderType type = defineReponame(inLevel);
    QString folderSig = systemregulation::dirName.folderSig.value(type);

    while(_currentDir.exists(folderSig + QString::number(numDir))) {
        _folders->append(new QPushButton(QString::number(numDir) /* FIXME(Tony) */, this));
        _foldersLayout->addWidget(_folders->at(numButton), buttonPosition.getRow(), buttonPosition.getColumn());

        connect(_folders->at(numButton), &QPushButton::clicked, this, [numDir, folderSig, inLevel, this](){
            _currentDir.cd(folderSig + QString::number(numDir));
            emit dirChanged(workflow::levelDown(inLevel));
        });

        _folders->at(numButton)->setStyleSheet("QPushButton{background: #E6E6FA; height: 75px;}");

        ++buttonPosition;
        ++numDir;
        ++numButton;
    }

    // NEW
    _folders->append(new QPushButton("new", this));
    _foldersLayout->addWidget(_folders->at(numButton), 1, 0);
    _folders->at(numButton)->setStyleSheet("QPushButton{background: #98FB98; height: 75px;}");

    connect(_folders->at(numButton), &QPushButton::clicked, this, [numDir, inLevel, this](){
        appendDir(_currentDir, inLevel, numDir);
        emit dirChanged(workflow::levelDown(inLevel));
    });
}
// add the opportunity to append an empty book/chapter etc. end to add full notepath straightaway

static systemregulation::FolderType defineReponame(workflow::DataLevel level)
{
    switch(level){
    case workflow::DataLevel::IN_ROOT:
        return systemregulation::FolderType::BOOK;

    case workflow::DataLevel::IN_BOOK:
        return systemregulation::FolderType::CHAPTER;

    case workflow::DataLevel::IN_CHAPTER:
        return systemregulation::FolderType::SUBSECTION;

    case workflow::DataLevel::IN_SUBSECTION:
        qDebug() << "wrooong in defineReponame in RepoButtons";
        return systemregulation::FolderType::SUBSECTION;  // error
    }
}

static void appendBook(QDir &directory, unsigned short numDir)
{
    const QString foldername(systemregulation::dirName.folderSig.value(systemregulation::FolderType::BOOK) + QString::number(numDir));

    directory.mkdir(foldername);
    directory.cd(foldername);

    QFile cmt(directory.absolutePath() + "/" + systemregulation::dirName.total.value(systemregulation::FileType::COMMS));
    cmt.open(QFile::WriteOnly | QFile::Text);  // just for creating a file
    cmt.close();

    QFile bk(directory.absolutePath() + "/" + systemregulation::dirName.total.value(systemregulation::FileType::BOOK));
    bk.open(QFile::WriteOnly | QFile::Text);  // just for creating a file
    bk.close();

    QFile lgnd(directory.absolutePath() + "/" + systemregulation::dirName.total.value(systemregulation::FileType::LEGEND));
    lgnd.open(QFile::WriteOnly | QFile::Text);  // just for creating a file
    lgnd.close();
}
static void appendChapter(QDir &directory, unsigned short numDir)
{
    const QString foldername(systemregulation::dirName.folderSig.value(systemregulation::FolderType::CHAPTER) + QString::number(numDir));

    directory.mkdir(foldername);
    directory.cd(foldername);

    QFile cmt(directory.absolutePath() + "/" + systemregulation::dirName.sectional.value(systemregulation::FileType::COMMS));
    cmt.open(QFile::WriteOnly | QFile::Text);  // just for creating a file
    cmt.close();

    QFile bk(directory.absolutePath() + "/" + systemregulation::dirName.sectional.value(systemregulation::FileType::BOOK));
    bk.open(QFile::WriteOnly | QFile::Text);  // just for creating a file
    bk.close();
}
static void appendSubsection(QDir &directory, unsigned short numDir)
{
    const QString foldername(systemregulation::dirName.folderSig.value(systemregulation::FolderType::SUBSECTION) + QString::number(numDir));

    directory.mkdir(foldername);
    directory.cd(foldername);

    QFile cmt(directory.absolutePath() + "/" + systemregulation::dirName.subsectional.value(systemregulation::FileType::COMMS));
    cmt.open(QFile::WriteOnly | QFile::Text);  // just for creating a file
    cmt.close();

    QFile bk(directory.absolutePath() + "/" + systemregulation::dirName.subsectional.value(systemregulation::FileType::BOOK));
    bk.open(QFile::WriteOnly | QFile::Text);  // just for creating a file
    bk.close();
}

static void appendDir(QDir &directory, workflow::DataLevel newLevel, unsigned short numDir)
{
    switch (newLevel) {
    case workflow::DataLevel::IN_ROOT:
        return appendBook(directory, numDir);

    case workflow::DataLevel::IN_BOOK:
        return appendChapter(directory, numDir);

    case workflow::DataLevel::IN_CHAPTER:
        return appendSubsection(directory, numDir);

    default:
        return;
    }
}

RepoButtons::~RepoButtons()
{
    for(size_t i = 0; (qsizetype)i < _folders->size(); ++i)
        delete _folders->at(i);
    delete _folders;

    delete _foldersLayout;
}
