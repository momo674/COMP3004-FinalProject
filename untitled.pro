QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    JSONInteractor.cpp \
    SystemInteraction.cpp \
    UserInfo.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    JSONInteractor.h \
    SystemInteraction.h \
    UserInfo.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += images \
    resources.qrc

DISTFILES += \
    HealthDataUser.json \
    images/rado1.jpeg \
    test.json
# Copy test.json to the build directory
CONFIG += in_source_build
#QMAKE_POST_LINK += $$quote(cp $$PWD/test.json $$OUT_PWD/)
