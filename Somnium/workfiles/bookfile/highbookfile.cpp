#include <QFile>
#include <QTextStream>

#include "highbookfile.h"


HighBookFile::HighBookFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum)
    : DataFile(bookNum, chapterNum, subsectionNum)
{
    if(this->defineName(systemregulation::FileType::BOOK)) {
        // TODO(Tony): do smth if error
    }
}


// I need to get somehow info from the database DataTree. maybe move void collect() -to-> DataTree?
void HighBookFile::collect()  // if n parts?
{
    QList<QFile *> files;
    for(size_t n = 1; n < 4; ++n) {
        files.append(new QFile((QString)"file" + QString::number(n) + ".bk"));
        if(!files.last()->open(QFile::ReadOnly | QFile::Text))
            exit(100);
    }

    QFile fresult("result.bk");
    if(!fresult.open(QFile::WriteOnly | QFile::Text))
        exit(101);


    QTextStream writeflow(&fresult);
    for(auto &file : files)
    {
        QTextStream parseflow(file);
        QString currentLine = parseflow.readLine();
        while(currentLine = parseflow.readLine(), currentLine != bookutils::parseLiterals.value(bookutils::ParseKey::TITLE))
            ;

        currentLine = parseflow.readLine();
        while(currentLine = parseflow.readLine(), !parseflow.atEnd()) {
            writeflow << currentLine;
            if(currentLine != "")
                writeflow << "\n";
        }
    }
}

HighBookFile::~HighBookFile() {};
