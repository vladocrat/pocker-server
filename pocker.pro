QT -= gui
QT += network sql

CONFIG += c++14 console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD\\pocker-common\\headers\\ \
               #..\\server\\ \
               #..\\server\\pocker-common\\ \

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

DEFINES += DATABASE_PASSWORD=\\\"Adwxsqezc14\\\"\
           DATABASE_HOSTNAME=\\\"192.168.88.96\\\"\
           DATABASE_NAME=\\\"pocker\\\"\
           DATABASE_USERNAME=\\\"postgres\\\"\


