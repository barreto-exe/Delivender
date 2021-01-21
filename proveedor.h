// Declaración de la clase Proveedor
// Implementación en proveedor.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <ctime>
#include <string>

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
        // falta declarar la estructura que relaciona el producto con su cantidad --- arreglo de struct para ver el almacén

    public:
        // Constructor
        Proveedor(string nombre = "", string descripcion = "", string telefono = "", string direccion = "", string tipoProveedor = "");

        // Funciones set
        Proveedor &setNombre(string nombre);
        Proveedor &setDescripcion(string descripcion);
        Proveedor &setTelefono(string telefono);
        Proveedor &setDireccion(string direccion);
        Proveedor &setTipoProveedor(string tipoProveedor);

        // Funciones get
        string getNombre() const;
        string getDescripcion() const;
        string getTelefono() const;
        string getDireccion() const;
        string getTipoProveedor() const;
};

#endif
