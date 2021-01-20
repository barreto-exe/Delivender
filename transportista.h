// Declaración de la clase Transportista
// Implementación en transportista.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef TRANSPORTISTA_H
#define TRANSPORTISTA_H

#include <string>
#include "vehiculo.h"

using std::string;

class Transportista : public Persona
{
public:
    // Constructor
    Transportista(string nombre, string apellido, string cedula, string telefono, time_t fechaNacimiento, Vehiculo vehiculo);

    // Funciones set
    Transportista &setVehiculo(Vehiculo vehiculo);

    // Funciones get
    Vehiculo getVehiculo() const;

private:
    Vehiculo vehiculo; // Datos del vehiculo transporte

};

#endif
