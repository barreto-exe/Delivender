// Declaración de la clase Producto
// Implementación en producto.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

using std::string;

// Clase para productos que posee un proveedor
class Producto {
    private:
        // Atributos
        string nombre;
        string descripcion;
        float precio;
        int id;

    public:
        // Constructor
        Producto(string nombre = "", string descripcion = "", float precio = 0);

        // Funciones set
        Producto &setNombre(string nombre);
        Producto &setDescripcion(string descripcion);
        Producto &setPrecio(float precio);
        Producto &setId(int id);

        // Funciones get
        string getNombre() const;
        string getDescripcion() const;
        float getPrecio() const;
        int getId() const;
};

#endif
