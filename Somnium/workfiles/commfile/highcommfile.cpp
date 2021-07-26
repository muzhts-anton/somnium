#include "highcommfile.h"


HighCommFile::HighCommFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum)
    : DataFile(bookNum, chapterNum, subsectionNum)
{
    if(this->defineName(systemregulation::FileType::BOOK)) {
        // TODO(Tony): do smth if error
    }
}

void HighCommFile::collect()
{
    // ...
}

HighCommFile::~HighCommFile() {};
