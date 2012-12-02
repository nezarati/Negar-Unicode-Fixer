#-------------------------------------------------
#
# Project created by QtCreator 2011-07-12T00:35:01
#
#-------------------------------------------------

QT       += core gui

TARGET = PersianFixer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    unicodepresavedialog.cpp \
    dialogunicodexmlfileeditor.cpp \
    convertor.cpp \
    checkboxeditdelegate.cpp \
    dialogabout.cpp

HEADERS  += mainwindow.h \
    unicodepresavedialog.h \
    dialogunicodexmlfileeditor.h \
    convertor.h \
    checkboxeditdelegate.h \
    check_box_delegate.h \
    dialogabout.h

FORMS    += mainwindow.ui \
    unicodepresavedialog.ui \
    dialogunicodexmlfileeditor.ui \
    dialogabout.ui

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    myapp.rc
RC_FILE = myapp.rc
