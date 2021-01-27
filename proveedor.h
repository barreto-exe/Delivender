// Declaración de la clase Proveedor
// Implementación en proveedor.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <string>
#include "producto_cantidad.h"

using std::string;

// Clase para empresas afilidadas a Delivender
class Proveedor {
    private:
        // Atributos
        string nombre;
        string descripcion;
        string telefono;
        string direccion;
        string tipoProveedor;
        producto_cantidad *almacen;

    public:
        // Constructor
        Proveedor();
        Proveedor(string nombre = "", string descripcion = "", string telefono = "", string direccion = "", string tipoProveedor = "", producto_cantidad *almacen = nullptr);
        Proveedor(string nombre = "", string descripcion = "", string telefono = "", string direccion = "", string tipoProveedor = "");

        // Funciones set
        Proveedor &setNombre(string nombre);
        Proveedor &setDescripcion(string descripcion);
        Proveedor &setTelefono(string telefono);
        Proveedor &setDireccion(string direccion);
        Proveedor &setTipoProveedor(string tipoProveedor);
        Proveedor &setAlmacen(producto_cantidad *almacen);

        // Funciones get
        string getNombre() const;
        string getDescripcion() const;
        string getTelefono() const;
        string getDireccion() const;
        string getTipoProveedor() const;
        producto_cantidad *getAlmacen() const;

        // Funciones
        int agregarProductoAlmacen(Producto producto, int cantidad);
};

#endif
