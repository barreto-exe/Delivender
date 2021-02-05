// Declaración de la clase Global
// Implementación en global.cpp

// Evita más de una inclusión del archivo de encabezado

#ifndef GLOBAL_H
#define GLOBAL_H

#include "mysql_connection.h"
#include "usuario.h"

class Global
{
public:
    // MySQL
    static MySQLConnection db;

    // Delivender
    static Usuario *usuario;
    static vector <producto_cantidad> pedido;
    static Proveedor proveedorSeleccionado;
};

#endif // GLOBAL_H
