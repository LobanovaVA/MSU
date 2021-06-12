TARGET = a.out

QT += core gui widgets opengl
QMAKE_CXXFLAGS += -std=c++17
LIBS += -pthread

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++17

SOURCES += \
    addition.cpp \
    approximation.cpp \
    grid_info.cpp \
    in_out.cpp \
    main.cpp \
    msr_matr/msr_matr_fill.cpp \
    msr_matr/msr_matr_ind.cpp \
    msr_matr/msr_matr_pattern.cpp \
    msr_matr/msr_matr_operation.cpp \
    msr_matr/msr_matr_solve.cpp \
    painter/gl_painter.cpp \
    painter/gl_painter_W.cpp \
    painter/gl_painter_draw.cpp \
    painter/surface.cpp \
    painter/surface_draw.cpp \
    threads/th_time.cpp \
    threads/thread_info.cpp \
    window/windiw_gui_base.cpp \
    window/window_init.cpp \
    window/window_labels.cpp \
    window/window_slots.cpp \
    window/window_solve.cpp

HEADERS += \
    addition.h \
    approximation.h \
    grid_info.h \
    in_out.h \
    msr_matr/msr_matr.h \
    msr_matr/msr_matr_ind.h \
    painter/gl_painter.h \
    painter/surface.h \
    struct.h \
    threads/th_time.h \
    threads/thread_info.h \
    window/window.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
