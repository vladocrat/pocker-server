QT -= gui
QT += network sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "..\\pocker\\" \
               "..\\common\\" \


HEADERS += \
    LoginData.h \
    Message.h \
    RegisterData.h \
    card.h \
    gamelogic.h \
    profile.h \
    protocol.h \
    room.h \
    server.h \
    user.h \
    userrepository.h \
    ../common/*.h \
    controllers\\*.h \
    connections\\*.h \

SOURCES += \
        card.cpp \
        gamelogic.cpp \
        main.cpp \
        profile.cpp \
        room.cpp \
        server.cpp \
        user.cpp \
        userrepository.cpp \
        controllers\\*.cpp \
        connections\\*.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DEFINES += DATABASE_PASSWORD=\\\"Adwxsqezc14\\\"\
           DATABASE_HOSTNAME=\\\"localhost\\\"\
           DATABASE_NAME=\\\"pocker\\\"\
           DATABASE_USERNAME=\\\"postgres\\\"\


