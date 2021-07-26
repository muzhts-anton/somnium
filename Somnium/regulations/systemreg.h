#ifndef SYSTEMREG_H
#define SYSTEMREG_H

#include <QString>
#include <QMap>


namespace systemregulation {
    enum class Extension {
        FOLDER = -1,
        TEXT,
        LEGEND,
        COMMENTS,
        RELEASE,
    };

    const QMap<Extension, QString> extension = {{Extension::FOLDER, ""},
                                                {Extension::TEXT, ".bk"},
                                                {Extension::COMMENTS, ".cmt"},
                                                {Extension::LEGEND, ".lgnd"},
                                                {Extension::RELEASE, ".txt"}};

    enum class FolderType {
        ROOT = -1,
        BOOK,
        CHAPTER,
        SUBSECTION,
    };

    enum class FileType {
        BOOK = 0,
        LEGEND,
        COMMS,
    };

    typedef const struct {
        const QMap<FolderType, QString> folderSig = {{FolderType::ROOT, "Data"},
                                                     {FolderType::BOOK, "Book_"},
                                                     {FolderType::CHAPTER, "Chapter_"},
                                                     {FolderType::SUBSECTION, "Subsection_"}};

        const QMap<FileType, QString> total = {{FileType::BOOK, "totalBook" + extension.value(Extension::TEXT)},
                                               {FileType::COMMS, "abstractComms" + extension.value(Extension::COMMENTS)},
                                               {FileType::LEGEND, "legend" + extension.value(Extension::LEGEND)}};

        const QMap<FileType, QString> sectional = {{FileType::BOOK, "totalChapter" + extension.value(Extension::TEXT)},
                                                   {FileType::COMMS, "sectionalComms" + extension.value(Extension::COMMENTS)}};

        const QMap<FileType, QString> subsectional = {{FileType::BOOK, "note" + extension.value(Extension::TEXT)},
                                                      {FileType::COMMS, "comms" + extension.value(Extension::COMMENTS)}};
    } leveltype_t;

    const leveltype_t dirName;
}  // systemregulation

#endif // SYSTEMREG_H
