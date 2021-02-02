// Implementación de la clase Usuario
#include "usuario.h"

// Constructor de la clase
Usuario::Usuario(string nombre, string telefono, string correo, string direccion)
{
    this->nombre = nombre;
    this->telefono = telefono;
    this->correo = correo;
    this->direccion = direccion;
}

// Establece el nombre
Usuario &Usuario::setNombre(string nombre)
{
    this->nombre = nombre;

    return *this; // Permite el proceso en cascada
}

// Establece el teléfono
Usuario &Usuario::setTelefono(string telefono)
{
    this->telefono = telefono;

    return *this; // Permite el proceso en cascada
}

// Establece el correo
Usuario &Usuario::setCorreo(string correo)
{
    this->correo = correo;

    return *this; // Permite el proceso en cascada
}

// Establece la dirección
Usuario &Usuario::setDireccion(string direccion)
{
    this->direccion = direccion;

    return *this; // Permite el proceso en cascada
}

// Devuelve el nombre
string Usuario::getNombre() const { return nombre; }

// Devuelve el teléfono
string Usuario::getTelefono() const { return telefono; }

// Devuelve el correo
string Usuario::getCorreo() const { return correo; }

// Devuelve la direccion
string Usuario::getDireccion() const { return direccion; }
