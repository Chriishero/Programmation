QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    font/OFL.txt \
    font/README.txt \
    font/SourceCodePro-Italic-VariableFont_wght.ttf \
    font/SourceCodePro-VariableFont_wght.ttf \
    font/static/SourceCodePro-Black.ttf \
    font/static/SourceCodePro-BlackItalic.ttf \
    font/static/SourceCodePro-Bold.ttf \
    font/static/SourceCodePro-BoldItalic.ttf \
    font/static/SourceCodePro-ExtraBold.ttf \
    font/static/SourceCodePro-ExtraBoldItalic.ttf \
    font/static/SourceCodePro-ExtraLight.ttf \
    font/static/SourceCodePro-ExtraLightItalic.ttf \
    font/static/SourceCodePro-Italic.ttf \
    font/static/SourceCodePro-Light.ttf \
    font/static/SourceCodePro-LightItalic.ttf \
    font/static/SourceCodePro-Medium.ttf \
    font/static/SourceCodePro-MediumItalic.ttf \
    font/static/SourceCodePro-Regular.ttf \
    font/static/SourceCodePro-SemiBold.ttf \
    font/static/SourceCodePro-SemiBoldItalic.ttf
