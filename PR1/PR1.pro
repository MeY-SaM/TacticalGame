QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hexagon.cpp \
    bp.cpp \
    main.cpp \
    page.cpp \
    page1.cpp \
    pagegallery.cpp \
    pagename.cpp

HEADERS += \
    hexagon.h \
    bp.h \
    page.h \
    page1.h \
    pagegallery.h \
    pagename.h

FORMS += \
    page.ui \
    page1.ui \
    pagegallery.ui \
    pagename.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Boards.qrc \
    bp.qrc \
    page.qrc \
    page1.qrc \
    pageGallery.qrc \
    pageName.qrc \
    bp.qrc \
    pageName.qrc

DISTFILES +=
