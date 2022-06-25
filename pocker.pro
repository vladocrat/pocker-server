QT -= gui
QT += network sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS += \
    ../common/Singleton.h \
    LoginData.h \
    Message.h \
    RegisterData.h \
    card.h \
    connection.h \
    gamelogic.h \
    pendingconnection.h \
    profile.h \
    protocol.h \
    room.h \
    server.h \
    user.h \
    userconnection.h \
    usercontroller.h \
    userrepository.h \
    ../common/*.h

SOURCES += \
        card.cpp \
        connection.cpp \
        gamelogic.cpp \
        main.cpp \
        pendingconnection.cpp \
        profile.cpp \
        room.cpp \
        server.cpp \
        user.cpp \
        userconnection.cpp \
        usercontroller.cpp \
        userrepository.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DEFINES += DATABASE_PASSWORD=\\\"Adwxsqezc14\\\"\
           DATABASE_HOSTNAME=\\\"localhost\\\"\
           DATABASE_NAME=\\\"pocker\\\"\
           DATABASE_USERNAME=\\\"postgres\\\"\


