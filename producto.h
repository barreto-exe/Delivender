// Declaración de la clase Producto
// Implementación en producto.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using std::string;

// Clase para productos que posee un proveedor
class Producto {
    private:
        // Atributos
        string nombre;
        string descripcion;
        float precio;

    public:
        // Constructor
        Producto(string nombre = "", string descripcion = "", float precio = 0);

        // Funciones set
        Producto &setNombre(string nombre);
        Producto &setDescripcion(string descripcion);
        Producto &setPrecio(float precio);

        // Funciones get
        string getNombre() const;
        string getDescripcion() const;
        float getPrecio() const;
};

#endif
