// Declaración de la clase MySQLConnection
// Implementación en mysql_connection.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

// MySQL
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
// Clases
#include "persona.h"
#include "proveedor.h"
#include "vehiculo.h"

using std::string;

// Clase para conectar el Front con la BDD remota a través de funciones
class MySQLConnection
{
    private:
        // Atributos
        sql::Driver *driver;
        sql::Connection *con;

        // Funciones
        char *encriptar(char *password);
        char *timeToString(time_t *fecha);
        int obtenerIdUsuario(char *correo);
        int registrarUsuario(char *correo, char *password, char *tipo);
        int registrarPersona(Persona cliente, int id_usuario);

    public:
        // Constructor
        MySQLConnection();

        // Funciones get
        sql::Connection *getConnection() const;

        // Funciones
        int iniciarSesion(char *correo, char *password);
        int registrarCliente(Persona cliente, char *correo, char *password);
        int registrarProveedor(Proveedor proveedor, char *correo, char *password);
        int registrarTransportista(Persona transportista, Vehiculo vehiculo, char *correo, char *password);
        int registrarVehiculo(Vehiculo vehiculo, char const *cedula_transportista);
};

#endif // MYSQLCONNECTION_H
