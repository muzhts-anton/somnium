#ifndef LOWLEVELFILE_H
#define LOWLEVELFILE_H


class ILowLevelFile
{
protected:
    virtual void write(void *) = 0;
    virtual void *parse() = 0;

    virtual void append(void *) = 0;
};

#endif // LOWLEVELFILE_H
