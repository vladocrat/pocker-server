QT -= gui
QT += network sql

CONFIG += c++11 console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD\\pocker-common\\headers\\ \
               $$PWD\\ \

HEADERS += \
    LoginData.h \
    Message.h \
    RegisterData.h \
    card.h \
    gamelogic.h \
    lobby.h \
    profile.h \
    protocol.h \
    server.h \
    user.h \
    userrepository.h \
    controllers\\*.h \
    connections\\*.h \
    pocker-common\\headers\\*.h \

SOURCES += \
        card.cpp \
        gamelogic.cpp \
        lobby.cpp \
        main.cpp \
        profile.cpp \
        server.cpp \
        user.cpp \
        userrepository.cpp \
        controllers\\*.cpp \
        connections\\*.cpp \
        pocker-common\\\sources\*.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



