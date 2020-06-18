QT       += core gui thelib
SHARE_APP_NAME = theGrades

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
TARGET = thegrades

# Include the-libs build tools
include(/usr/share/the-libs/pri/buildmaster.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    grades/grades.cpp \
    grades/widget/gradewidget.cpp \
    averages/averages.cpp

HEADERS += \
    mainwindow.h \
    grades/grades.h \
    grades/widget/gradewidget.h \
    averages/averages.h

FORMS += \
    mainwindow.ui \
    grades/grades.ui \
    grades/widget/gradewidget.ui \
    averages/averages.ui

unix {
    target.path = /usr/bin/

    defaults.files = defaults.conf
    defaults.path = /etc/theGrades/

    desktop.path = /usr/share/applications
    desktop.files = com.zumid.theGrades.desktop

    icon.path = /usr/share/icons/hicolor/scalable/apps/
    icon.files = icons/theApp.svg

    INSTALLS += target desktop icon defaults
}

# Turn off stripping as this causes the install to fail :(
QMAKE_STRIP = echo

RESOURCES += \
    resources.qrc

DISTFILES += \
    com.zumid.theGrades.desktop \
    defaults.conf
