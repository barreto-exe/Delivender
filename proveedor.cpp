// Implementación de la clase Proveedor
#include "proveedor.h"

/ Constructor de la clase
Proveedor::Proveedor(string nombre, string descripcion, string rif, string telefono)
{
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->rif = rif;
    this->telefono = telefono;
}

// Establece el nombre
Proveedor &Proveedor::setNombre(string nombre)
{
    this->nombre = nombre;

    return *this; // Permite el proceso en cascada
}

// Establece la descripcion
Proveedor &Proveedor::setDescripcion(string descripcion)
{
    this->descripcion = descripcion;

    return *this; // Permite el proceso en cascada
}

// Establece el rif
Proveedor &Proveedor::setRif(string rif)
{
    this->rif = rif;

    return *this; // Permite el proceso en cascada
}

// Establece el teléfono
Proveedor &Proveedor::setTelefono(string telefono)
{
    this->telefono = telefono;

    return *this; // Permite el proceso en cascada
}

// Devuelve el nombre
string Proveedor::getNombre() const { return nombre; }

// Devuelve la descripcion
string Proveedor::getDescripcion() const { return descripcion; }

// Devuelve el rif
string Proveedor::getRif() const { return rif; }

// Devuelve el teléfono
string Proveedor::getTelefono() const { return telefono; }
