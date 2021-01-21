// Implementación de la clase Producto
#include "producto.h"

// Constructor de la clase
Producto::Producto(string nombre, string descripcion, float precio)
{
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->precio = precio;
}

// Establece el nombre del producto
Producto &Producto::setNombre(string nombre)
{
    this->nombre = nombre;

    return *this; // Permite el proceso en cascada
}

// Establece la descripción del producto
Producto &Producto::setDescripcion(string descripcion)
{
    this->descripcion = descripcion;

    return *this; // Permite el proceso en cascada
}

// Establece el precio del producto
Producto &Producto::setPrecio(float precio)
{
    this->precio = precio;

    return *this; // Permite el proceso en cascada
}

// Devuelve el nombre
string Producto::getNombre() const { return nombre; }

// Devuelve la descripción
string Producto::getDescripcion() const { return descripcion; }

// Devuelve el precio
float Producto::getPrecio() const { return precio; }
