#ifndef HIGHCOMMFILE_H
#define HIGHCOMMFILE_H

#include "workfiles/basefile/datafile.h"
#include "workfiles/interfile/highlevelfile.h"


class HighCommFile : public DataFile, public IHighLevelFile
{
public:
    HighCommFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum);

    void collect() override;  // in 'abstract' realization is a lot harder, connected with the phone => working with the server etc.

    ~HighCommFile();
};

#endif // HIGHCOMMFILE_H
