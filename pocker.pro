QT -= gui
QT += network sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "..\\pocker\\" \
               "..\\pocker\\pocker-common\\" \


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
    pocker-common\\*.h \

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
        pocker-common\\*.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DEFINES += DATABASE_PASSWORD=\\\"Adwxsqezc14\\\"\
           DATABASE_HOSTNAME=\\\"localhost\\\"\
           DATABASE_NAME=\\\"pocker\\\"\
           DATABASE_USERNAME=\\\"postgres\\\"\


