// Declaración de la clase Proveedor
// Implementación en proveedor.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include "usuario.h"
#include "producto_cantidad.h"

using std::string;
using std::vector;

// Clase para empresas afilidadas a Delivender
class Proveedor : public Usuario
{
    private:
        // Atributos
        string descripcion;
        string tipoProveedor;
        vector <producto_cantidad> almacen;

    public:
        // Constructor
        Proveedor();
        Proveedor(string nombre, string descripcion, string telefono, string correo, string direccion, string tipoProveedor);
        Proveedor(string nombre, string descripcion, string telefono, string correo, string direccion, string tipoProveedor, vector <producto_cantidad> almacen);

        // Funciones set
        Proveedor &setDescripcion(string descripcion);
        Proveedor &setTipoProveedor(string tipoProveedor);
        Proveedor &setAlmacen(vector <producto_cantidad> almacen);

        // Funciones get
        string getDescripcion() const;
        string getTipoProveedor() const;
        vector <producto_cantidad> getAlmacen() const;
};

#endif
