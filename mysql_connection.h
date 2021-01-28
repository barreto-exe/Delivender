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
        char *encriptar(const char *password);
        char *timeToString(time_t *fecha);
        int obtenerIdProducto(Producto *producto);
        int verificarCorreo(const char *correo);
        int verificarCedula(const char *cedula);
        int verificarPlaca(const char *placa);
        int registrarUsuario(const char *correo, const char *password, const char *tipo);
        int registrarPersona(const Persona persona);
        Proveedor *instanciarProveedor(const char *correo);
        Producto *instanciarProducto(const int id_producto);
        Persona *instanciarPersona(const char *correo);

    public:
        // Constructor
        MySQLConnection();

        // Funciones get
        sql::Connection *getConnection() const;

        // Funciones
        int iniciarSesion(const char *correo, const char *password);
        int registrarCliente(Persona cliente, const char *correo, const char *password);
        int registrarProveedor(Proveedor proveedor, const char *correo, const char *password);
        int registrarTransportista(Persona transportista, Vehiculo vehiculo, const char *correo, const char *password);
        int registrarVehiculo(Vehiculo vehiculo, const char *correo_transportista);
        vector <Proveedor> listarProveedores();

        // Funciones que están son pública, pero NO deben usarse en FRONT. grasias ;)
        int registrarProducto(Producto *producto);
        int agregarProductoAlmacen(const char *correo_proveedor, producto_cantidad *pxq);

};
#endif // MYSQLCONNECTION_H
