// Implementación de la clase Producto
#include "producto.h"

// Constructor de la clase
Producto::Producto(string descripcion, float precio, float peso, float volumen)
{
    this->descripcion = descripcion;
    this->precio = precio;
    this->peso = peso;
    this->volumen = volumen;
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

// Establece el peso del producto
Producto &Producto::setPeso(float peso)
{
    this->peso = peso;

    return *this; // Permite el proceso en cascada
}

// Establece el volumen del producto
Producto &Producto::setPeso(float volumen)
{
    this->volumen = volumen;

    return *this; // Permite el proceso en cascada
}

// Devuelve la descripción
string Producto::getDescripcion() const { return descripcion; }

// Devuelve el precio
float Producto::getPrecio() const { return precio; }

// Devuelve el peso
float Producto::getPeso() const { return peso; }

// Devuelve el volumen
float Producto::getVolumen() const { return volumen; }