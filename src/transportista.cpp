// Implementación de la clase Transportista
#include "transportista.h"

// Constructor de la clase
Transportista::Transportista(Persona persona, Vehiculo vehiculo)
{
    this->persona = persona;
    this->vehiculo = vehiculo;
}

// Establece los datos personales del transportista
Transportista &Transportista::setPersona(Persona persona)
{
    this->persona = persona;

    return *this; // Permite el proceso en cascada
}

// Establece los datos personales del transportista
Transportista &Transportista::setVehiculo(Vehiculo vehiculo)
{
    this->vehiculo = vehiculo;

    return *this; // Permite el proceso en cascada
}

// Devuelve los datos personales
Persona Transportista::getPersona() const { return persona; }

// Devuelve los datos del vehiculo
Vehiculo Transportista::getVehiculo() const { return vehiculo; }
