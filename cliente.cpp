// Implementación de la clase Cliente
#include "cliente.h"

// Constructor de la clase
Cliente::Cliente(string nombre, string apellido, string cedula, string telefono, time_t fechaNacimiento, Usuario usuario) : Persona(nombre, apellido, cedula, telefono, fechaNacimiento)
{
    this->usuario = usuario;
}

// Establece los datos de usuario del cliente
Cliente &Cliente::setUsuario(Usuario usuario)
{
    this->usuario = usuario;

    return *this; // Permite el proceso en cascada
}

// Devuelve los datos de usuario del cliente
Usuario Cliente::getUsuario() const { return usuario; }


