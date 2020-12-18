// Declaración de la clase Cliente
// Implementación en cliente.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include "usuario.h"

using std::string;

class Cliente : public Persona
{
	public:
		// Constructor
		Cliente(string nombre, string apellido, string cedula, string telefono, time_t fechaNacimiento, Usuario usuario);

		// Funciones set
        Cliente &setUsuario(Usuario usuario);

		// Funciones get
        Cliente getUsuario() const;

	private:
        Usuario usuario; // Datos de usuario del cliente
		
};

#endif