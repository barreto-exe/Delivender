// Declaración de la clase ProductoCantidad
// Implementación en producto_cantidad.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PRODUCTOCANTIDAD_H
#define PRODUCTOCANTIDAD_H

#include <string>
#include "producto.h"

using std::string;

// Clase que relaciona la cantidad de un producto dentro de un almacén o pedido
class ProductoCantidad
{
private:
    // Atributos
    Producto producto;
    int cantidad;

public:
    // Cosntructor
    ProductoCantidad(Producto producto, int cantidad);

    // Funciones set
    ProductoCantidad &setProducto(Producto producto);
    ProductoCantidad &setCantidad(int cantidad);

    // Funciones get
    Producto getProducto() const;
    int getCantidad() const;
};

#endif // PRODUCTOCANTIDAD_H
