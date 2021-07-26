#ifndef HIGHBOOKFILE_H
#define HIGHBOOKFILE_H

#include "workfiles/basefile/datafile.h"
#include "workfiles/interfile/highlevelfile.h"


class HighBookFile : public DataFile, public IHighLevelFile
{
public:
    HighBookFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum);

    void collect() override;

    ~HighBookFile();
};

#endif // HIGHBOOKFILE_H
