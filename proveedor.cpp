// Implementación de la clase Proveedor
#include "proveedor.h"
#include"mysql_connection.h"
#include"global.h"

// Constructor de la clase
Proveedor::Proveedor() : Usuario()
{
    descripcion = "";
    tipoProveedor = "";
    almacen = vector <producto_cantidad>();
}

Proveedor::Proveedor(string nombre, string descripcion, string telefono, string correo, string direccion, string tipoProveedor, vector <producto_cantidad> almacen)
    : Usuario(nombre, telefono, correo, direccion)
{
    this->descripcion = descripcion;
    this->tipoProveedor = tipoProveedor;
    this->almacen = almacen;
}

Proveedor::Proveedor(string nombre, string descripcion, string telefono, string correo, string direccion, string tipoProveedor)
    : Usuario(nombre, telefono, correo, direccion)
{
    this->descripcion = descripcion;
    this->tipoProveedor = tipoProveedor;
    almacen = vector <producto_cantidad>();
}

// Establece la descripcion
Proveedor &Proveedor::setDescripcion(string descripcion)
{
    this->descripcion = descripcion;

    return *this; // Permite el proceso en cascada
}

// Establece el tipo de proveedor
Proveedor &Proveedor::setTipoProveedor(string tipoProveedor)
{
    this->tipoProveedor = tipoProveedor;

    return *this; // Permite el proceso en cascada
}

// Establece el almacén
Proveedor &Proveedor::setAlmacen(vector <producto_cantidad> almacen)
{
    this->almacen = almacen;

    return *this; // Permite el proceso en cascada
}

// Devuelve la descripcion
string Proveedor::getDescripcion() const { return descripcion; }

// Devuelve el tipo de proveedor
string Proveedor::getTipoProveedor() const { return tipoProveedor; }

// Devuelve el almacen
vector <producto_cantidad> Proveedor::getAlmacen() const { return almacen; }

