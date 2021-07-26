#ifndef LOWCOMMFILE_H
#define LOWCOMMFILE_H

#include "workfiles/basefile/datafile.h"
#include "workfiles/interfile/lowlevelfile.h"


class LowCommFile : public DataFile, public ILowLevelFile
{
public:
    LowCommFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum);

    void *parse() override;
    void write(void *) override;

    void append(void *) override;

    ~LowCommFile();
};

#endif // LOWCOMMFILE_H
