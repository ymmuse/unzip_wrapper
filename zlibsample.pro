TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += /usr/local/opt/zlib/include
INCLUDEPATH += ./minizip

HEADERS += \
    zipextract.h

SOURCES += main.c zipextract.c

SOURCES += ./minizip/zip.c \
            ./minizip/unzip.c \
            ./minizip/mztools.c \
            ./minizip/ioapi.c

win32 {
SOURCES += ./minizip/iowin32.c
}

LIBS += -L/usr/local/opt/zlib/lib
LIBS += -lz

