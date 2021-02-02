// Declaración de la clase Transportista
// Implementación en transportista.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef TRANSPORTISTA_H
#define TRANSPORTISTA_H

#include<vector>
#include"persona.h"
//#include"vehiculo.h"

class Transportista : public Persona
{
    /*private:
        *vector <Vehiculo> vehiculos;*/
    public:
        Transportista();
        Transportista(string nombre, string apellido, string cedula, string telefono, string correo, string direccion, QDate fechaNacimiento);
};

#endif // TRANSPORTISTA_H
