// Declaración de la clase Transportista
// Implementación en transportista.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef TRANSPORTISTA_H
#define TRANSPORTISTA_H

#include <string>
#include "transportista.h"

using std::string;

class Transportista : public Persona{
	public:
		// Constructor
		Transportista(Persona persona, Vehiculo vehiculo);

		// Funciones set
		Transportista &setPersona(Persona persona);
        Transportista &setVehiculo(Vehiculo vehiculo);

		// Funciones get
		Persona getPersona() const;
        Vehiculo getVehiculo() const;

	private:
		Persona persona; // Datos personales del transportista
        Vehiculo vehiculo; // Datos del vehiculo transporte
		
};

#endif