// Declaración de la clase MySQLConnection
// Implementación en mysql_connection.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using std::string;

// Clase para conectar el Front con la BDD remota a través de funciones
class MySQLConnection
{
    private:
        // Atributos
        sql::Driver *driver;

    public:
        // Constructor
        MySQLConnection();
        sql::Connection *con;

        // Funciones get (RECUERDA ENCAPSULAR *CON)

        // Funciones
        int iniciarSesion(char *correo, char *password);
};

#endif // MYSQLCONNECTION_H
