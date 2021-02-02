// Declaración de la clase Persona
// Implementación en persona.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PERSONA_H
#define PERSONA_H

#include<QDate>
#include"usuario.h"


// Clase para clientes y transportistas
class Persona : public Usuario
{
    private:
        // Atributos
        string apellido;
        string cedula;
        QDate fechaNacimiento;
        
    public:
        // Constructor
        Persona();
        Persona(string nombre, string apellido, string cedula, string telefono, string correo, string direccion, QDate fechaNacimiento);
    
        // Funciones set
        Persona &setApellido(string apellido);
        Persona &setCedula(string cedula);
        Persona &setFechaNacimiento(QDate fechaNacimiento);
    
        // Funciones get
        string getApellido() const;
        string getCedula() const;
        QDate getFechaNacimiento() const;
};

#endif
