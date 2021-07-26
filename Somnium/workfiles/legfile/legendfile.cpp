#include <QTextStream>
#include <QDebug>
#include <QFile>

#include "legendfile.h"


LegendFile::LegendFile(ssize_t bookNum, ssize_t chapterNum, ssize_t subsectionNum)
    : DataFile(bookNum, chapterNum, subsectionNum)
{
    if(this->defineName(systemregulation::FileType::LEGEND)) {
        // TODO(Tony): do smth if error
    }
}


static void *parseEachLegend(QTextStream &parseflow)
{
    if(parseflow.atEnd())
        return nullptr;

    legutils::legstruct_t *tmp = new legutils::legstruct_t;

    QString currentLine = parseflow.readLine();
    while(currentLine == "")
        currentLine = parseflow.readLine();

    if(currentLine != legutils::parseLiterals.value(legutils::ParseKey::LEGEND))
        exit(62);

    currentLine = parseflow.readLine();
    tmp->theme = currentLine;

    currentLine = parseflow.readLine();
    if(currentLine != legutils::parseLiterals.value(legutils::ParseKey::COLOR)) {

        exit(63);
    }

    currentLine = parseflow.readLine();
    tmp->color = currentLine;

    currentLine = parseflow.readLine();
    if(currentLine != legutils::parseLiterals.value(legutils::ParseKey::COLOR)) {
        qDebug() << currentLine;
        exit(64);
    }

    currentLine = parseflow.readLine();
    if(currentLine != legutils::parseLiterals.value(legutils::ParseKey::TERMSOPEN))
        exit(65);

    while(currentLine = parseflow.readLine(), currentLine != legutils::parseLiterals.value(legutils::ParseKey::TERMSCLOSE))
        tmp->term.append(currentLine);

    currentLine = parseflow.readLine();
    if(currentLine != legutils::parseLiterals.value(legutils::ParseKey::DEFINITION))
        exit(66);

    while(currentLine = parseflow.readLine(), currentLine != legutils::parseLiterals.value(legutils::ParseKey::LEGEND))
        tmp->definition += currentLine + "\n";

    currentLine = parseflow.readLine();
    if(currentLine != "")
        exit(67);

    // qDebug() << tmp->theme << tmp->color << tmp->term << tmp->definition;
    return tmp;
}

void *LegendFile::parse()
{
    QFile currentLegends("helpme.lgnd");
    if(!currentLegends.open(QFile::ReadOnly | QFile::Text))
        exit(61);

    QTextStream parseflow(&currentLegends);

    QList<legutils::legstruct_t *> *value = new QList<legutils::legstruct_t *>;
    legutils::legstruct_t *tmp;

    while((tmp = (legutils::legstruct_t *)parseEachLegend(parseflow)) != nullptr) {
        value->append(tmp);
        // qDebug() << value->at(0)->term;
    }

    currentLegends.close();

    return value;
}

void LegendFile::write(void * /* QList<legstruct_t *> * */ legendsInfo_)
{
    QList<legutils::legstruct_t *> *legendsInfo = static_cast<QList<legutils::legstruct_t *> *>(legendsInfo_);

    QFile currentLegends("helpme.lgnd");
    if(!currentLegends.open(QFile::WriteOnly | QFile::Text))
        exit(71);

    QTextStream out(&currentLegends);

    for(size_t i = 0; (int)i < legendsInfo->size(); ++i) {
        out << legutils::parseLiterals.value(legutils::ParseKey::LEGEND) + "\n";
        out << legendsInfo->at(i)->theme + "\n";
        out << legutils::parseLiterals.value(legutils::ParseKey::COLOR) + "\n";
        out << legendsInfo->at(i)->color + "\n";
        out << legutils::parseLiterals.value(legutils::ParseKey::COLOR) + "\n";
        out << legutils::parseLiterals.value(legutils::ParseKey::TERMSOPEN) + "\n";

        for(size_t j = 0; (int)j < legendsInfo->at(i)->term.size(); ++j)
            out << legendsInfo->at(i)->term.at(j) + "\n";

        out << legutils::parseLiterals.value(legutils::ParseKey::TERMSCLOSE) + "\n";
        out << legutils::parseLiterals.value(legutils::ParseKey::DEFINITION) + "\n";
        out << legendsInfo->at(i)->definition + "\n";
        out << legutils::parseLiterals.value(legutils::ParseKey::LEGEND) + "\n";
        out << "\n";
    }

    currentLegends.close();
}

void LegendFile::append(void * /* legstruct_t * */ newLegend_)
{
    legutils::legstruct_t *newLegend = static_cast<legutils::legstruct_t *>(newLegend_);

    QFile currentLegends("helpme.lgnd");
    if(!currentLegends.open(QIODevice::Append))
        exit(81);

    QTextStream out(&currentLegends);

    out << "\n";
    out << legutils::parseLiterals.value(legutils::ParseKey::LEGEND) + "\n";
    out << newLegend->theme + "\n";
    out << legutils::parseLiterals.value(legutils::ParseKey::COLOR) + "\n";
    out << newLegend->color + "\n";
    out << legutils::parseLiterals.value(legutils::ParseKey::COLOR) + "\n";
    out << legutils::parseLiterals.value(legutils::ParseKey::TERMSOPEN) + "\n";

    for(size_t j = 0; (int)j < newLegend->term.size(); ++j)
        out << newLegend->term.at(j) + "\n";

    out << legutils::parseLiterals.value(legutils::ParseKey::TERMSCLOSE) + "\n";
    out << legutils::parseLiterals.value(legutils::ParseKey::DEFINITION) + "\n";
    out << newLegend->definition + "\n";
    out << legutils::parseLiterals.value(legutils::ParseKey::LEGEND) + "\n";

    currentLegends.close();
}

void LegendFile::remove(size_t index)
{
    QFile oldLegend("helpme.lgnd");
    if(!oldLegend.open(QFile::ReadOnly | QFile::Text))
        exit(91);

    QFile newLegend("torename.lgnd");
    if(!newLegend.open(QFile::WriteOnly | QFile::Text))
        exit(92);

    QTextStream parseflow(&oldLegend);
    QTextStream writeflow(&newLegend);

    QString currentLine = parseflow.readLine();
    size_t i = 0;
    while(i < 2 * index && !parseflow.atEnd()) {
        writeflow << currentLine + "\n";

        if(currentLine == legutils::parseLiterals.value(legutils::ParseKey::LEGEND))
            ++i;
        currentLine = parseflow.readLine();
    }
    if(parseflow.atEnd()) {
        writeflow << currentLine + "\n";
        return;
    }
    currentLine = parseflow.readLine();
    while(currentLine = parseflow.readLine(), currentLine != legutils::parseLiterals.value(legutils::ParseKey::LEGEND))
        ;

    while(currentLine = parseflow.readLine(), currentLine == "" && !parseflow.atEnd())
        ;

    if(!parseflow.atEnd())
        writeflow << "\n";

    while(!parseflow.atEnd()) {
        writeflow << currentLine + "\n";
        currentLine = parseflow.readLine();
    }
    writeflow << currentLine + "\n";

    oldLegend.close();
    newLegend.close();
    oldLegend.remove();
    newLegend.rename("helpme.lgnd");
}


LegendFile::~LegendFile() {};
