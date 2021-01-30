// Declaración de la clase Vehiculo
// Implementación en vehiculo.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
#include "solicitud.h"

using std::string;

// Clase para vehiculos correspondientes a transportistas
class Vehiculo
{
    private:
        // Atributos
        string modelo;
        string placa;
        string tipo;
    public:
        // Constructor
        Vehiculo(string modelo = "", string placa = "", string tipo = "");

        // Funciones set
        Vehiculo &setModelo(string modelo);
        Vehiculo &setPlaca(string placa);
        Vehiculo &setTipo(string tipo);

        // Funciones get
        string getModelo() const;
        string getPLaca() const;
        string getTipo() const;

};

#endif // VEHICULO_H
