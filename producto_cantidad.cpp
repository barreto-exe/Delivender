// Implementación de la clase ProductoCantidad
#include "producto_cantidad.h"

// Constructor de la clase
ProductoCantidad::ProductoCantidad(Producto producto, int cantidad)
{
    this->producto = producto;
    this->cantidad = cantidad;
}

// Establece el roducto
ProductoCantidad &ProductoCantidad::setProducto(Producto producto)
{
    this->producto = producto;

    return *this; // Permite el proceso en cascada
}

// Establece la cantidad del producto
ProductoCantidad &ProductoCantidad::setCantidad(int cantidad)
{
    this->cantidad = cantidad;

    return *this; // Permite el proceso en cascada
}

// Devuelve el producto
Producto ProductoCantidad::getProducto() const { return producto; }

// Devuelve la cantidad
int ProductoCantidad::getCantidad() const { return cantidad; }
