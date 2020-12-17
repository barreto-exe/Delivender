// Declaración de la clase Persona
// Implementación en persona.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PERSONA_H
#define PERSONA_H

#include <ctime>
#include <string>

using std::string;

class Persona {
	public:
		// Constructor
		Persona(string nombre = "", string apellido = "", string cedula = "", string telefono = "", time_t fechaNacimiento = 0);

		// Funciones set
		Persona &setNombre(string nombre);
		Persona &setApellido(string apellido);
		Persona &setCedula(string cedula);
		Persona &setTelefono(string telefono);
		Persona &setFechaNacimiento(time_t fechaNacimiento);

		// Funciones get
		string getNombre() const;
		string getApellido() const;
		string getCedula() const;
		string getTelefono() const;
		time_t getFechaNacimiento() const;

	private:
		string nombre;
		string apellido;
		string cedula;
		string telefono;
		time_t fechaNacimiento;
		
};

#endif