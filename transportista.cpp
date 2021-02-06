// Implementación de la clase Transportista
#include "transportista.h"

// Constructor de la clase
Transportista::Transportista() : Persona()
{
    vehiculos = vector <Vehiculo>();
}

Transportista::Transportista (string nombre, string apellido, string cedula, string telefono, string correo, string direccion, QDate fechaNacimiento, vector <Vehiculo> vehiculos)
    : Persona(nombre, apellido, cedula, telefono, correo, direccion, fechaNacimiento)
{
    this->vehiculos = vehiculos;
}

// Establece el almacén
Transportista &Transportista::setVehiculos(vector<Vehiculo> vehiculos)
{
    this->vehiculos = vehiculos;

    return *this; // Permite el proceso en cascada
}

// Devuelve los vehiculos
vector <Vehiculo> Transportista::getVehiculos() const { return vehiculos; }

Transportista &Transportista::agregarVehiculo(Vehiculo vehiculo)
{
    vehiculos.push_back(vehiculo);
    return *this;
}
