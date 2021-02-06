// Declaración de la estructura que relaciona un vehículo con su transportista

// Evita más de una inclusión del archivo de encabezado
#ifndef VEHICULO_TRANSPORTISTA_H
#define VEHICULO_TRANSPORTISTA_H

#include<vector>
#include "vehiculo.h"
#include"transportista.h"

struct vehiculo_transportista
{
    Vehiculo vehiculo;
    Transportista transportista;
};

#endif // VEHICULO_TRANSPORTISTA_H
