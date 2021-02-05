// Declaración de la clase Cliente
// Implementación en cliente.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef CLIENTE_H
#define CLIENTE_H

#include"persona.h"

class Cliente : public Persona
{
    public:
        Cliente();
        Cliente(string nombre, string apellido, string cedula, string telefono, string correo, string direccion, QDate fechaNacimiento);
};

#endif // CLIENTE_H
