######################################################################
# Automatically generated by qmake (3.1) Sat Dec 21 05:02:06 2024
######################################################################

TEMPLATE = app
TARGET = team7_messenger
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += build-team7_messenger_client-Desktop-Debug/ui_chatclient.h \
           team7_messenger_client/chatclient.h \
           team7_messenger_client/ui_chatclient.h
FORMS += team7_messenger_client/chatclient.ui
SOURCES += client.cpp \
           server.c \
           team7_messenger_client/chatclient.cpp \
           team7_messenger_client/main.cpp