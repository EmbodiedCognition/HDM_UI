#-------------------------------------------------
#
# Project created by QtCreator 2011-07-13T11:16:41
#
#-------------------------------------------------

QT += core gui opengl sql printsupport widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

#CONFIG += console c++11

TARGET = QtVR
TEMPLATE = app

SOURCES += \
    src/main.cpp\
    src/mainwindow.cpp \
    src/myglwidget.cpp \
    src/quatcamera.cpp \
    src/markerwidget.cpp \
    src/simworld.cpp \
    src/CapBody.cpp \
    src/jointwidget.cpp \
    src/jointplotwidget.cpp \
    src/markerdata.cpp \
    src/c3ddata.cpp \
    src/sequence.cpp \
    src/colorlabel.cpp \
    src/dsboxwithparams.cpp \
    src/experimentscript.cpp \
    src/scriptbase.cpp \
    src/testscript.cpp \
    src/qcustomplot.cpp

HEADERS += \
    include/mainwindow.h \
    include/myglwidget.h \
    include/quatcamera.h \
    include/markerwidget.h \
    include/simworld.h \
    include/CapBody.h \
    include/jointwidget.h \
    include/jointplotwidget.h \
    include/markerdata.h \
    include/c3ddata.h \
    include/DataCValues.h \
    include/sequence.h \
    include/colorlabel.h \
    include/dsboxwithparams.h \
    include/experimentscript.h \
    include/scriptbase.h \
    include/testscript.h \
    include/gaussrand.h \
    include/qcustomplot.h

FORMS += \
    ui/mainwindow.ui \
    ui/markerwidget.ui \
    ui/jointwidget.ui \
    ui/jointplotwidget.ui

RESOURCES += \
    resources.qrc

INCLUDEPATH += ./include
INCLUDEPATH += /usr/local/include

LIBS += -L /usr/local/lib -lode


LIBS += -L./ode/lib
INCLUDES += -I./ode/include

# We use ODE with double precision
DEFINES += dDOUBLE QT_DEPRECATED_WARNINGS

# In MSVC, we want to turn off some annoying warnings
win32:DEFINES += _CRT_SECURE_NO_WARNINGS

# If we've captured marker data and balance board data
# simultaneously, we'll need BoardData instead of MarkerData
#DEFINES += BOARD_DATA

# Telling QT where the ODE code source is allows the creator
# to provide more code completion and source help
win32:INCLUDEPATH += ../ode/include

# Point to Boost library for the random number generator
win32:INCLUDEPATH += $$(BOOST_ROOT)

# Link the lab-specific copy of ODE
win32 {
  debug:LIBS += ../ode/lib/DebugDoubleLib/ode_doubled.lib
  else:LIBS += ../ode/lib/ReleaseDoubleLib/ode_double.lib
}

# This linker flag is for MSVC.  It makes the stack larger.
# This might not be necessary any more, but old versions of
# ODE were prone to overflow the stack.
win32:QMAKE_LFLAGS += /STACK:8000000

# On Unix, add specific compiler flags for dependent libraries.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
