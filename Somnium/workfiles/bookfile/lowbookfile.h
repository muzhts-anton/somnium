#ifndef LOWBOOKFILE_H
#define LOWBOOKFILE_H

#include "workfiles/basefile/datafile.h"
#include "workfiles/interfile/lowlevelfile.h"


class LowBookFile : public DataFile, public ILowLevelFile
{
public:
    LowBookFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum);

    void *parse() override;
    void write(void *) override;
    void append(void *) override;

    ~LowBookFile();
};

#endif // LOWBOOKFILE_H
