// Declaración de la estructura que relaciona un producto con su cantidad

// Evita más de una inclusión del archivo de encabezado
#ifndef PRODUCTO_CANTIDAD_H
#define PRODUCTO_CANTIDAD_H

#include "producto.h"

struct producto_cantidad
{
    Producto producto;
    int cantidad;
};

#endif // PRODUCTO_CANTIDAD_H
