// Declaración de la clase Global
// Implementación en global.cpp

// Evita más de una inclusión del archivo de encabezado

#ifndef GLOBAL_H
#define GLOBAL_H

#include "mysql_connection.h"
#include "persona.h"
#include "proveedor.h"

class Global
{
public:
    // MySQL
    static MySQLConnection db;

    // Delivender
    static Proveedor *proveedor, proveedorSeleccionado;
    static Persona *cliente, *transportista;
    static vector <producto_cantidad> pedido;
};

#endif // GLOBAL_H
