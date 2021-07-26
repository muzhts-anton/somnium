#ifndef LEGENDFILE_H
#define LEGENDFILE_H

#include <QList>

#include "workfiles/basefile/datafile.h"
#include "workfiles/interfile/lowlevelfile.h"


/* .lgnd */
class LegendFile : public DataFile, public ILowLevelFile
{
public:
    LegendFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum);

    void *parse() override;
    void write(void * /* [QList<legendStruct_t *> *] */) override;

    void append(void * /* [legendStruct_t *] */) override;
    void remove(size_t);

    ~LegendFile();
};

#endif // LEGENDFILE_H
