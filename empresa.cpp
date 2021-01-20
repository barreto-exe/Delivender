// Implementación de la clase Empresa
#include "empresa.h"

// Constructor de la clase
Empresa::Empresa(string nombre, string descripcion, string rif, string telefono, Usuario usuario) : Proveedor(nombre, descripcion, rif, telefono)
{
    this->usuario = usuario;
}

// Establece los datos de usuario de la empresa
Empresa &Empresa::setUsuario(Usuario usuario)
{
    this->usuario = usuario;

    return *this; // Permite el proceso en cascada
}

// Devuelve los datos de usuario de la empresa
Usuario Empresa::getUsuario() const { return usuario; }
