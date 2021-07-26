#ifndef DATAFILE_H
#define DATAFILE_H

#include "../../regulations/systemreg.h"
#include "../fileutils/fileutils.h"


class DataFile {
public:
    DataFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum);
    ~DataFile();

protected:
    Level getLevel();
    bool defineName(systemregulation::FileType);

private:
    ssize_t _bookNum;
    ssize_t _chapterNum;
    ssize_t _subsectionNum;

    QString _name;
    systemregulation::Extension _extension;
};

#endif // DATAFILE_H
