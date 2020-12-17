// Declaración de la clase Producto
// Implementación en producto.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using std::string;

class Producto{
    public:
        // Constructor
        Producto(string descripcion, float precio, float peso, float volumen);
        
        // Funciones set
        Producto &setDescripcion(string descripcion);
        Producto &setPrecio(float precio);
        Producto &setPeso(float peso);
        Producto &setVolumen(float volumen);

        // Funciones get
        string getDescripcion() const;
        float getPrecio() const;
        float getPeso() const;
        float getVolumen() const;

    private:
        string descripcion;
        float precio;
        float peso;
        float volumen;

};

#endif