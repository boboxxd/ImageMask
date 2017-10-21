#-------------------------------------------------
#
# Project created by QtCreator 2017-10-19T18:05:28
#
#-------------------------------------------------

QT       += core gui xml
 INCLUDEPATH += /usr/local/opt/opencv3/include
 LIBS+=-L/usr/local/Cellar/opencv3/3.2.0/lib\
-lopencv_shape -lopencv_stitching\
-lopencv_objdetect -lopencv_superres -lopencv_videostab\
-lopencv_calib3d -lopencv_features2d\
-lopencv_highgui -lopencv_videoio -lopencv_imgcodecs\
-lopencv_video -lopencv_photo -lopencv_ml\
-lopencv_imgproc -lopencv_flann\
-lopencv_core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Imagemark
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    common.cpp \
    showlabel.cpp \
    xmltool.cpp \
    getimage.cpp

HEADERS  += widget.h \
    common.h \
    showlabel.h \
    xmltool.h \
    getimage.h

FORMS    += widget.ui

RESOURCES += \
    icon.qrc
