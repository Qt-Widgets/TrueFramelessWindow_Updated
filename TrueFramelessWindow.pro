#-------------------------------------------------
#
# TrueFramelessWindow.pro
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrueFramelessWindow
TEMPLATE = app
CONFIG += app_bundle

SOURCES += main.cpp\
    widget.cpp \
    thememanager.cc

HEADERS  += widget.h \
    thememanager.h

win32 {
    # Only include / compile these files on Windows
    SOURCES += \
        qwinwidget.cpp \
        winnativewindow.cpp

    HEADERS += \
        qwinwidget.h \
        winnativewindow.h

    LIBS += dwmapi.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib
}

mac {
    # Only include / compile these files on OS X
    OBJECTIVE_SOURCES += \
        OSXHideTitleBar.mm
    HEADERS  +=\
        OSXHideTitleBar.h

    # Additionally include Cocoa for OS X code

    LIBS += -framework Foundation -framework Cocoa
    INCLUDEPATH += /System/Library/Frameworks/Foundation.framework/Versions/C/Headers
}

RESOURCES += \
    window.qrc

DISTFILES += \
    window.css
