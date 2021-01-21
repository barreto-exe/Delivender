// Impplementación de la clase Vehiculo
#include "vehiculo.h"

Vehiculo::Vehiculo(string modelo, string placa, string tipo)
{
    this->modelo = modelo;
    this->placa = placa;
    this->tipo = tipo;
}

// Establece el modelo
Vehiculo &Vehiculo::setModelo(string modelo)
{
    this->modelo = modelo;

    return  *this; // Permite el proceso en cascada
}

// Establece la placa
Vehiculo &Vehiculo::setPlaca(string placa)
{
    this->placa = placa;

    return  *this; // Permite el proceso en cascada
}

// Establece el tipo
Vehiculo &Vehiculo::setTipo(string tipo)
{
    this->tipo = tipo;

    return  *this; // Permite el proceso en cascada
}

// Devuelve el tipo de pago
string Vehiculo::getModelo() const { return modelo; }

// Devuelve el tipo de pago
string Vehiculo::getPLaca() const { return placa; }

// Devuelve el tipo
string Vehiculo::getTipo() const { return tipo; }
