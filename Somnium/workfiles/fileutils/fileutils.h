#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include <QStringList>
#include <QMap>


enum class Level {
    IN_ROOT = -1,
    IN_BOOK,
    IN_CHAPTER,
    IN_SUBSECTION,
};


namespace commutils {
    enum class CommType {  // add all the types (in QMap in .cpp too)
        ERROR = -1,
        TOADD,  // !?
        THINKABOUT,  // ?
        REWRITE,  // *
        SPECIFY,  // ...
    };

    typedef struct {
        qint64 part;
        CommType type;
        QString comment;
    } commstruct_t;

    enum class ParseKey {
        COMMENT = 0,
        OPENTYPE,
        CLOSETYPE,
        BODY,
    };

    const QMap<ParseKey, QString> parseLiterals = {{ParseKey::COMMENT, "####"},
                                                   {ParseKey::OPENTYPE, "<<"},
                                                   {ParseKey::CLOSETYPE, ">>"},
                                                   {ParseKey::BODY, "###"}};

    const QMap<CommType, QString> TypeLiterals = {{CommType::REWRITE, "*"},
                                                  {CommType::THINKABOUT, "?"},
                                                  {CommType::TOADD, "!?"},
                                                  {CommType::SPECIFY, "..."}};
}


namespace bookutils {
    typedef struct {
        QString title;
        bool hasPart;
        qint64 part;
        QString text;
    } bookstruct_t;

    enum class ParseKey {
        TITLE = 0,
        BRANCH,
    };

    const QMap<ParseKey, QString> parseLiterals = {{ParseKey::TITLE, "####"},
                                                   {ParseKey::BRANCH, "@!"}};
}


namespace legutils {
    typedef struct {
        QString theme;
        QString color;
        QStringList term;
        QString definition;
    } legstruct_t;

    enum class ParseKey {
        LEGEND = 0,
        COLOR,
        TERMSOPEN,
        TERMSCLOSE,
        DEFINITION,
    };


    const QMap<ParseKey, QString> parseLiterals = {{ParseKey::LEGEND, "####"},
                                                   {ParseKey::COLOR, "@!"},
                                                   {ParseKey::TERMSOPEN, "##{"},
                                                   {ParseKey::TERMSCLOSE, "##}"},
                                                   {ParseKey::DEFINITION, "###"},};
}

#endif // FILEUTILS_H
