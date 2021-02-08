QT       += core gui
LIBS += -lmysqlcppconn
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cliente.cpp \
    entregawidget.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    mysql_connection.cpp \
    pantalla_principal.cpp \
    pantalla_proveedor.cpp \
    pantalla_registro.cpp \
    pantalla_transportista.cpp \
    persona.cpp \
    producto.cpp \
    proveedor.cpp \
    solicitud.cpp \
    solicitudwidget.cpp \
    tiendawidget.cpp \
    transportista.cpp \
    usuario.cpp \
    vehiculo.cpp

HEADERS += \
    cliente.h \
    entregawidget.h \
    global.h \
    mainwindow.h \
    mysql_connection.h \
    pantalla_principal.h \
    pantalla_proveedor.h \
    pantalla_registro.h \
    pantalla_transportista.h \
    persona.h \
    producto.h \
    producto_cantidad.h \
    proveedor.h \
    solicitud.h \
    solicitudwidget.h \
    tiendawidget.h \
    transportista.h \
    usuario.h \
    vehiculo.h \
    vehiculo_transportista.h

FORMS += \
    entregawidget.ui \
    mainwindow.ui \
    pantalla_principal.ui \
    pantalla_proveedor.ui \
    pantalla_registro.ui \
    pantalla_transportista.ui \
    solicitudwidget.ui \
    tiendawidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
