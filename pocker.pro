QT -= gui
QT += network sql

CONFIG += c++11 console
CONFIG -= app_bundle

WORKING_SHADOW_BUILD_DIR = $$PWD

message("pass $${WORKING_SHADOW_BUILD_DIR}")

WORKING_SHADOW_BUILD_DIR = $$system(cd ..)

message("new pass $${WORKING_SHADOW_BUILD_DIR}")

INCLUDEPATH += $$PWD\\pocker-common\\headers\\ \
               $$PWD\\ \
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
           DATABASE_HOSTNAME=\\\"localhost\\\"\
           DATABASE_NAME=\\\"pocker\\\"\
           DATABASE_USERNAME=\\\"postgres\\\"\


