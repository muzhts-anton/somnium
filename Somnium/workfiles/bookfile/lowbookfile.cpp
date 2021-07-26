#include <QDebug>
#include <QFile>

#include "lowbookfile.h"


LowBookFile::LowBookFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum)
    : DataFile(bookNum, chapterNum, subsectionNum)
{
    if(this->defineName(systemregulation::FileType::BOOK)) {
        // TODO(Tony): do smth if error
    }
}

void *LowBookFile::parse()
{
    QFile currentBook("testiiiiiing.bk");
    if(!currentBook.open(QFile::ReadOnly | QFile::Text))
        exit(1);

    QTextStream parseflow(&currentBook);

    QString currentLine = parseflow.readLine();  // 1

    if(currentLine != bookutils::parseLiterals.value(bookutils::ParseKey::TITLE)) {
        qDebug() << "BOOKPARSE error 1";
        exit(2);
    }

    QString title = parseflow.readLine();  // 2

    currentLine = parseflow.readLine();  // 3

    qint64 part = 0;
    bool hasPart = false;
    if(currentLine == bookutils::parseLiterals.value(bookutils::ParseKey::BRANCH)) {
        part = parseflow.readLine().toLongLong();  // 4
        hasPart = true;

        currentLine = parseflow.readLine();  // 5

        if(currentLine != bookutils::parseLiterals.value(bookutils::ParseKey::BRANCH)) {
            qDebug() << "BOOKPARSE error 2";
            exit(2);
        }
        currentLine = parseflow.readLine();  // 6
    }


    if(currentLine != bookutils::parseLiterals.value(bookutils::ParseKey::TITLE)) {
        qDebug() << "BOOKPARSE error 3";
        exit(2);
    }

    currentLine = parseflow.readLine();  // 7
    if(currentLine != "") {
        qDebug() << "BOOKPARSE error 4";
        exit(2);
    }

    currentLine = parseflow.readAll();

    bookutils::bookstruct_t *tmp = new bookutils::bookstruct_t;
    tmp->title = title;
    tmp->hasPart = hasPart;
    tmp->part = part;
    tmp->text = currentLine;

    currentBook.close();

    return tmp;
}

void LowBookFile::write(void *bookInfo_)
{
    bookutils::bookstruct_t *bookInfo = static_cast<bookutils::bookstruct_t *>(bookInfo_);

    QFile currentBook("testiiiiiing.bk");
    if(!currentBook.open(QFile::WriteOnly | QFile::Text))
        exit(1);

    QTextStream out(&currentBook);

    // проверить bookInfo
    out << bookutils::parseLiterals.value(bookutils::ParseKey::TITLE) + "\n" + bookInfo->title + "\n";
    if(bookInfo->hasPart)
        out << bookutils::parseLiterals.value(bookutils::ParseKey::BRANCH) + "\n" + QString::number(bookInfo->part) + "\n" + bookutils::parseLiterals.value(bookutils::ParseKey::BRANCH) + "\n";
    out << bookutils::parseLiterals.value(bookutils::ParseKey::TITLE) + "\n" + "\n";
    out << bookInfo->text;

    currentBook.close();
}

void LowBookFile::append(void *)
{
    // ??? error'it
}

LowBookFile::~LowBookFile() {};
