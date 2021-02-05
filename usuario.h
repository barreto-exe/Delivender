// Declaración de la clase Usuario
// Implementación en usuario.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using std::string;

class Usuario
{
    private:
        string nombre;
        string telefono;
        string correo;
        string direccion;
    public:
        Usuario(string nombre = "", string telefono = "", string correo = "", string direccion = "");

        // Funciones set
        Usuario &setNombre(string nombre);
        Usuario &setTelefono(string telefono);
        Usuario &setCorreo(string correo);
        Usuario &setDireccion(string direccion);

        // Funciones get
        string getNombre() const;
        string getTelefono() const;
        string getCorreo() const;
        string getDireccion() const;
};

#endif // USUARIO_H
