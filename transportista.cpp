// Implementación de la clase Transportista
#include "transportista.h"

// Constructor de la clase
Transportista::Transportista(string nombre, string apellido, string cedula, string telefono, time_t fechaNacimiento, Vehiculo vehiculo) : Persona(nombre, apellido, cedula, telefono, fechaNacimiento)
{
    this->vehiculo = vehiculo;
}

// Establece los datos del vehiculo
Transportista &Transportista::setVehiculo(Vehiculo vehiculo)
{
    this->vehiculo = vehiculo;

    return *this; // Permite el proceso en cascada
}

// Devuelve los datos del vehiculo
Vehiculo Transportista::getVehiculo() const { return vehiculo; }
