#-------------------------------------------------
#
# Project created by QtCreator 2018-06-30T14:52:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Library
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    menuadmin.cpp \
    book.cpp \
    reader.cpp \
    database.cpp \
    menureader.cpp \
    user.cpp \
    record.cpp

HEADERS  += widget.h \
    menuadmin.h \
    book.h \
    admin.h \
    reader.h \
    database.h \
    main.h \
    menureader.h \
    user.h \
    record.h

FORMS    += widget.ui \
    menuadmin.ui \
    menureader.ui
