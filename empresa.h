// Declaración de la clase Empresa
// Implementación en empresa.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef EMPRESA_H
#define EMPRESA_H

#include <string>
#include "usuario.h"

using std::string;

class Empresa : public Proveedor
{
public:
    // Constructor
    Empresa(string nombre, string descripcion, string rif, string telefono, Usuario usuario);

    // Funciones set
    Empresa &setUsuario(Usuario usuario);

    // Funciones get
    Empresa getUsuario() const;

private:
    Usuario usuario; // Datos de usuario de la empresa

};

#endif
