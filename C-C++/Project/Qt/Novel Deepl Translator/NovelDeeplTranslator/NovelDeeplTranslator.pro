QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    translationdialog.cpp

HEADERS += \
    mainwindow.h \
    translationdialog.h

FORMS += \
    mainwindow.ui \
    translationdialog.ui

QMAKE_CXXFLAGS += -fstack-protector-all
QMAKE_LFLAGS += -fstack-protector-all
QMAKE_LFLAGS += -Wl,--subsystem,windows


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    TEXT/BAKEMONOGATARI Part 1.pdf \
    TEXT/BAKEMONOGATARI-Part-1.txt \
    TEXT/bodybuilding.txt \
    build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/python/translate.py

