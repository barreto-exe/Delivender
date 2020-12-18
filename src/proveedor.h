// Declaración de la clase Proveedor
// Implementación en proveedor.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <ctime>
#include <string>

using std::string;

class Proveedor {
	public:
		// Constructor
		Proveedor(string nombre = "", string descripcion = "", string rif = "", string telefono = "");

		// Funciones set
		Proveedor &setNombre(string nombre);
		Proveedor &setDescripcion(string descripcion);
		Proveedor &setRif(string rif);
		Proveedor &setTelefono(string telefono);

		// Funciones get
		string getNombre() const;
		string getDescripcion() const;
		string getRif() const;
		string getTelefono() const;

	private:
		string nombre;
		string descripcion;
		string rif;
		string telefono;
		
};

#endif