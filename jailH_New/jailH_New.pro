#-------------------------------------------------
#
# Project created by QtCreator 2017-09-25T17:06:56
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11\
          debug
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jailH_New
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
    MemRegion.cpp \
    PciDevice.cpp \
    IrqChip.cpp \
    JailHouseCell.cpp \
    JailHouseCellList.cpp \
    RootCell.cpp \
    util.cpp \
    GenConfig.cpp \
    import.cpp \
    readfromdump/ReadDmp.cpp \
    readfromdump/cell_type_util.cpp \
    eula.cpp \
    transfer.cpp

HEADERS  += mainwindow.h\
    HwResource.h \
    MemRegion.h \
    PciDevice.h \
    IrqChip.h \
    JailHouseCell.h \
    JailHouseCellList.h \
    util.h \
    RootCell.h \
    GenConfig.h \
    import.h \
    readfromdump/types.h \
    readfromdump/ReadDmp.h \
    readfromdump/cell_type_util.h \
    readfromdump/cell-config.h \
    eula.h \
    transfer.h \
    Header.h

FORMS    += mainwindow.ui\
    import.ui \
    eula.ui \
    transfer.ui

