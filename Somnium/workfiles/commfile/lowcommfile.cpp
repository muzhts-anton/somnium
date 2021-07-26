#include <QTextStream>
#include <QFile>

#include "lowcommfile.h"


LowCommFile::LowCommFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum)
    : DataFile(bookNum, chapterNum, subsectionNum)
{
    if(this->defineName(systemregulation::FileType::BOOK)) {
        // TODO(Tony): do smth if error
    }
}


static commutils::CommType defineType(QString sType)  // дополнить и обобщить, не хардкодить. думаю снова через QMap
{
    if(sType == commutils::TypeLiterals.value(commutils::CommType::TOADD))
        return commutils::CommType::TOADD;

    if(sType == commutils::TypeLiterals.value(commutils::CommType::THINKABOUT))
        return commutils::CommType::THINKABOUT;

    if(sType == commutils::TypeLiterals.value(commutils::CommType::REWRITE))
        return commutils::CommType::REWRITE;

    if(sType == commutils::TypeLiterals.value(commutils::CommType::SPECIFY))
        return commutils::CommType::SPECIFY;

    return commutils::CommType::ERROR;
}

static void *parseEachComment(QTextStream &parseflow)
{
    if(parseflow.atEnd())
        return nullptr;

    commutils::commstruct_t *currentObject = new commutils::commstruct_t;

    QString currentLine = parseflow.readLine();

    if(currentLine != commutils::parseLiterals.value(commutils::ParseKey::COMMENT))
        exit(12);

    currentLine = parseflow.readLine();

    /* придумать как обработать ошибку */
    currentObject->part = currentLine.split(commutils::parseLiterals.value(commutils::ParseKey::OPENTYPE)).at(0).toLongLong();
    currentObject->type = defineType(currentLine.split(commutils::parseLiterals.value(commutils::ParseKey::CLOSETYPE)).at(0).split(commutils::parseLiterals.value(commutils::ParseKey::OPENTYPE)).at(1));

    currentLine = parseflow.readLine();
    if(currentLine != commutils::parseLiterals.value(commutils::ParseKey::BODY))
        exit(13);

    while(currentLine = parseflow.readLine(), currentLine != commutils::parseLiterals.value(commutils::ParseKey::COMMENT)) {
        if(parseflow.atEnd())
            exit(14);
        currentObject->comment += currentLine + "\n";
    }

    currentLine = parseflow.readLine();
    if(currentLine != "")
        exit(15);


    // qDebug() << currentObject->part << (int)currentObject->type << currentObject->comment;

    return currentObject;
}


void *LowCommFile::parse()
{
    QFile currentComment("pups.cmt");
    if(!currentComment.open(QFile::ReadOnly | QFile::Text))
        exit(11);

    QTextStream parseflow(&currentComment);

    QList<commutils::commstruct_t *> *value = new QList<commutils::commstruct_t *>;
    commutils:: commstruct_t *tmp;
    // size_t i = 0;
    while((tmp = (commutils::commstruct_t *)parseEachComment(parseflow)) != nullptr) {
        value->append(tmp);

        // qDebug() << value->at(i)->part << (int)value->at(i)->type << value->at(i)->comment;
        // ++i;
    }

    currentComment.close();

    return value;
}

void LowCommFile::write(void *commentsInfo_)
{
    QList<commutils::commstruct_t *> *commentsInfo = static_cast<QList<commutils::commstruct_t *> *>(commentsInfo_);

    QFile currentComment("pups.cmt");
    if(!currentComment.open(QFile::ReadOnly | QFile::Text))
        exit(31);

    QTextStream out(&currentComment);

    for(size_t i = 0; i < (size_t)commentsInfo->size(); ++i) {  /* rework */
        out << commutils::parseLiterals.value(commutils::ParseKey::COMMENT) + "\n";
        out << QString::number(commentsInfo->at(i)->part) + commutils::parseLiterals.value(commutils::ParseKey::OPENTYPE) +
               commutils::TypeLiterals.value(commentsInfo->at(i)->type) + commutils::parseLiterals.value(commutils::ParseKey::CLOSETYPE) + "\n";
        out << commutils::parseLiterals.value(commutils::ParseKey::BODY) + "\n";
        out << commentsInfo->at(i)->comment + "\n";
        out << commutils::parseLiterals.value(commutils::ParseKey::COMMENT) + "\n" + "\n";
    }

    currentComment.close();
}

void LowCommFile::append(void *)
{
    // ...
}

LowCommFile::~LowCommFile() {};
