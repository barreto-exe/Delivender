// Declaración de la clase Usuario
// Implementación en usuario.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using std::string;

class Usuario {
	public:
		// Constructor
		Usuario(string usuario, string correo, string contrasena);

		// Funciones set
		Usuario &setUsuario(string usuario);
		Usuario &setCorreo(string correo);
		Usuario &setContrasena(string contrasena);

		// Funciones get
		string getUsuario() const;
		string getCorreo() const;
		string getContrasena() const;

	private:
		string usuario; // Nombre de usuario
		string correo;
		string contrasena;
		
};

#endif