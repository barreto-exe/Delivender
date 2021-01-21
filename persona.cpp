// Implementación de la clase Persona
#include "persona.h"

// Constructor de la clase
Persona::Persona(string nombre, string apellido, string cedula, string telefono, string direccion, time_t fechaNacimiento)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->cedula = cedula;
    this->telefono = telefono;
    this->direccion = direccion;
    this->fechaNacimiento = fechaNacimiento;
}

// Establece el nombre
Persona &Persona::setNombre(string nombre)
{
    this->nombre = nombre;

    return *this; // Permite el proceso en cascada
}

// Establece el apellido
Persona &Persona::setApellido(string apellido)
{
    this->apellido = apellido;

    return *this; // Permite el proceso en cascada
}

// Establece la cedula
Persona &Persona::setCedula(string cedula)
{
    this->cedula = cedula;

    return *this; // Permite el proceso en cascada
}

// Establece el teléfono
Persona &Persona::setTelefono(string telefono)
{
    this->telefono = telefono;

    return *this; // Permite el proceso en cascada
}

// Establece la dirección
Persona &Persona::setDireccion(string direccion)
{
    this->direccion = direccion;

    return *this; // Permite el proceso en cascada
}

// Establece la fecha de nacimiento
Persona &Persona::setFechaNacimiento(time_t fechaNacimiento)
{
    this->fechaNacimiento = fechaNacimiento;

    return *this; // Permite el proceso en cascada
}

// Devuelve el nombre
string Persona::getNombre() const { return nombre; }

// Devuelve el apellido
string Persona::getApellido() const { return apellido; }

// Devuelve la cedula
string Persona::getCedula() const { return cedula; }

// Devuelve el teléfono
string Persona::getTelefono() const { return telefono; }

// Devuelve la direccion
string Persona::getDireccion() const { return direccion; }

// Devuelve la fecha de nacimiento
time_t Persona::getFechaNacimiento() const { return fechaNacimiento; }
