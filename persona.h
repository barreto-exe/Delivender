// Declaración de la clase Persona
// Implementación en persona.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include<QDate>

using std::string;

// Clase para clientes y transportistas
class Persona {
    private:
        // Atributos
        string nombre;
        string apellido;
        string cedula;
        string telefono;
        string correo;
        string direccion;
        QDate fechaNacimiento;
        
    public:
        // Constructor
        Persona(string nombre = "", string apellido = "", string cedula = "", string telefono = "", string correo = "", string direccion = "", QDate fechaNacimiento = QDate());
    
        // Funciones set
        Persona &setNombre(string nombre);
        Persona &setApellido(string apellido);
        Persona &setCedula(string cedula);
        Persona &setTelefono(string telefono);
        Persona &setCorreo(string correo);
        Persona &setDireccion(string direccion);
        Persona &setFechaNacimiento(QDate fechaNacimiento);
    
        // Funciones get
        string getNombre() const;
        string getApellido() const;
        string getCedula() const;
        string getTelefono() const;
        string getCorreo() const;
        string getDireccion() const;
        QDate getFechaNacimiento() const;
};

#endif
