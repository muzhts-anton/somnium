#include <QDebug>

#include "workfiles/basefile/datafile.h"


DataFile::DataFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum)
    : _bookNum(bookNum)
    , _chapterNum(chapterNum)
    , _subsectionNum(subsectionNum)
{
    if (bookNum == 0 || chapterNum == 0 || subsectionNum == 0)
        qDebug() << "smth went wrong actually. DATAFILE class";
}

bool DataFile::defineName(systemregulation::FileType fileType)
{
    bool isError = false;

    switch(fileType) {
    case systemregulation::FileType::BOOK:
        _extension = systemregulation::Extension::TEXT;
        break;

    case systemregulation::FileType::COMMS:
        _extension = systemregulation::Extension::COMMENTS;
        break;

    case systemregulation::FileType::LEGEND:
        _extension = systemregulation::Extension::LEGEND;
        break;

    default:
        isError = true;
        qDebug() << "smth definitely went wrong. DATAFILE class DEFINENAME";
    }


    switch(this->getLevel()) {
    case Level::IN_BOOK:
        _name = systemregulation::dirName.total.value(fileType);
        break;

    case Level::IN_CHAPTER:
        _name = systemregulation::dirName.sectional.value(fileType);
        break;

    case Level::IN_SUBSECTION:
        _name = systemregulation::dirName.subsectional.value(fileType);
        break;

    default:
        isError = true;
        qDebug() << "smth definitely went wrong. DATAFILE class DEFINENAME";
    }

    return isError;
}

Level DataFile::getLevel() {
    if(_subsectionNum != -1)
        return Level::IN_SUBSECTION;
    if(_chapterNum != -1)
        return Level::IN_CHAPTER;
    if(_bookNum != -1)
        return Level::IN_BOOK;

    return Level::IN_ROOT;
}

DataFile::~DataFile()
{

}
