// Implementación de la clase Usuario
#include "usuario.h"

// Constructor de la clase
Usuario::Usuario(string usuario, string correo, string contrasena)
{
    this->usuario = usuario;
    this->correo = correo;
    this->contrasena = contrasena;
}

// Establece el nombre de usuario
Usuario &Usuario::setUsuario(string usuario)
{
    this->usuario = usuario;

    return *this; // Permite el proceso en cascada
}

// Establece el correo
Usuario &Usuario::setCorreo(string correo)
{
    this->correo = correo;

    return *this; // Permite el proceso en cascada
}

// Establece la contraseña
Usuario &Usuario::setContrasena(string contrasena)
{
    this->contrasena = contrasena;

    return *this; // Permite el proceso en cascada
}

// Devuelve el nombre de usuario
string Usuario::getUsuario() const { return usuario; }

// Devuelve el correo
string Usuario::getCorreo() const { return correo; }

// Devuelve la contraseña
string Usuario::getContrasena() const { return contrasena; }
