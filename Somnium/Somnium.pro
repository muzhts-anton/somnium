QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editor/editor.cpp \
    main.cpp \
    regulations/workflow.cpp \
    repositories/repobuttons.cpp \
    repositories/repoplacement.cpp \
    repositories/reposcroll.cpp \
    systemtree/systemtree.cpp \
    workfiles/basefile/datafile.cpp \
    workfiles/bookfile/highbookfile.cpp \
    workfiles/bookfile/lowbookfile.cpp \
    workfiles/commfile/highcommfile.cpp \
    workfiles/commfile/lowcommfile.cpp \
    workfiles/legfile/legendfile.cpp

HEADERS += \
    editor/editor.h \
    regulations/systemreg.h \
    regulations/workflow.h \
    repositories/repobuttons.h \
    repositories/repoplacement.h \
    repositories/reposcroll.h \
    systemtree/systemtree.h \
    workfiles/basefile/datafile.h \
    workfiles/bookfile/highbookfile.h \
    workfiles/bookfile/lowbookfile.h \
    workfiles/commfile/highcommfile.h \
    workfiles/commfile/lowcommfile.h \
    workfiles/fileutils/fileutils.h \
    workfiles/interfile/highlevelfile.h \
    workfiles/interfile/lowlevelfile.h \
    workfiles/legfile/legendfile.h

FORMS += \
    editor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
