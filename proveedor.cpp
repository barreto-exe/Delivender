// Implementación de la clase Proveedor
#include "proveedor.h"
#include"mysql_connection.h"

// Constructor de la clase
Proveedor::Proveedor()
{
    nombre = "";
    descripcion = "";
    telefono = "";
    correo = "";
    direccion = "";
    tipoProveedor = "";
    almacen.clear();
}

Proveedor::Proveedor(string nombre, string descripcion, string telefono, string correo, string direccion, string tipoProveedor, vector <producto_cantidad> almacen)
{
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->telefono = telefono;
    this->correo = correo;
    this->direccion = direccion;
    this->tipoProveedor = tipoProveedor;
    this->almacen = almacen;
}

Proveedor::Proveedor(string nombre, string descripcion, string telefono, string correo, string direccion, string tipoProveedor)
{
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->telefono = telefono;
    this->correo = correo;
    this->direccion = direccion;
    this->tipoProveedor = tipoProveedor;
    almacen.clear();
}

// Establece el nombre
Proveedor &Proveedor::setNombre(string nombre)
{
    this->nombre = nombre;

    return *this; // Permite el proceso en cascada
}

// Establece la descripcion
Proveedor &Proveedor::setDescripcion(string descripcion)
{
    this->descripcion = descripcion;

    return *this; // Permite el proceso en cascada
}

// Establece el teléfono
Proveedor &Proveedor::setTelefono(string telefono)
{
    this->telefono = telefono;

    return *this; // Permite el proceso en cascada
}

// Establece el correo
Proveedor &Proveedor::setCorreo(string correo)
{
    this->correo = correo;

    return *this; // Permite el proceso en cascada
}

// Establece la dirección
Proveedor &Proveedor::setDireccion(string direccion)
{
    this->direccion = direccion;

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

// Devuelve el nombre
string Proveedor::getNombre() const { return nombre; }

// Devuelve la descripcion
string Proveedor::getDescripcion() const { return descripcion; }

// Devuelve el teléfono
string Proveedor::getTelefono() const { return telefono; }

// Devuelve el correo
string Proveedor::getCorreo() const { return correo; }

// Devuelve la direccion
string Proveedor::getDireccion() const { return direccion; }

// Devuelve el tipo de proveedor
string Proveedor::getTipoProveedor() const { return tipoProveedor; }

// Devuelve el almacen
vector <producto_cantidad> Proveedor::getAlmacen() const { return almacen; }

int Proveedor::agregarProductoAlmacen(Producto *producto, int cantidad)
{
    MySQLConnection *db = new MySQLConnection();

    db->registrarProducto(producto);
    //db->agregarProductoAlmacen();

    return 0;
}
