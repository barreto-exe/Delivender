// Implementación de la clase Cliente
#include "cliente.h"

// Constructor de la clase
Cliente::Cliente() : Persona() { }

Cliente::Cliente (string nombre, string apellido, string cedula, string telefono, string correo, string direccion, QDate fechaNacimiento)
    : Persona(nombre, apellido, cedula, telefono, correo, direccion, fechaNacimiento) { }
