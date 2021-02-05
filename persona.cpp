// Implementación de la clase Persona
#include "persona.h"

// Constructor de la clase
Persona::Persona() : Usuario()
{
    apellido = "";
    cedula = "";
    fechaNacimiento = QDate();
}

Persona::Persona(string nombre, string apellido, string cedula, string telefono, string correo, string direccion, QDate fechaNacimiento)
    : Usuario(nombre, telefono, correo, direccion)
{
    this->apellido = apellido;
    this->cedula = cedula;
    this->fechaNacimiento = fechaNacimiento;
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

// Establece la fecha de nacimiento
Persona &Persona::setFechaNacimiento(QDate fechaNacimiento)
{
    this->fechaNacimiento = fechaNacimiento;

    return *this; // Permite el proceso en cascada
}

// Devuelve el apellido
string Persona::getApellido() const { return apellido; }

// Devuelve la cedula
string Persona::getCedula() const { return cedula; }

// Devuelve la fecha de nacimiento
QDate Persona::getFechaNacimiento() const { return fechaNacimiento; }
