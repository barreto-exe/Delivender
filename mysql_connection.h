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
        char *timeToString(time_t fecha);
        int verificarCorreo(const char *correo);
        int verificarCedula(const char *cedula);
        int verificarPlaca(const char *placa);
        int registrarUsuario(const char *correo, const char *password, const char *tipo);
        int registrarPersona(const Persona persona);
        Proveedor *instanciarProveedor(const char *correo);
        void instanciarAlmacen(Proveedor proveedor);
        Persona *instanciarPersona(const char *correo);
        Solicitud *instanciarSolicitud(Persona cliente, const int id);
        Solicitud *instanciarSolicitud(Proveedor proveedor, const int id);
        int obtenerIdTipoDePago(const char *correo_proveedor, const char *tipo);
        const char *obtenerTipoDePago(const int id);

    public:
        // Constructor
        MySQLConnection();

        // Funciones get
        sql::Connection *getConnection() const;

        // Funciones
        producto_cantidad structProductoCantidad(Producto producto, int cantidad);
        int iniciarSesion(const char *correo, const char *password);
        int registrarCliente(Persona cliente, const char *correo, const char *password);
        int registrarProveedor(Proveedor proveedor, const char *correo, const char *password);
        int registrarTransportista(Persona transportista, Vehiculo vehiculo, const char *correo, const char *password);
        int registrarVehiculo(Vehiculo vehiculo, const char *correo_transportista);
        int registrarSolicitud(Solicitud solicitud);
        vector <Proveedor> listarProveedores();
        vector <Solicitud> listarSolicitudes(Persona cliente);
        vector <Solicitud> listarSolicitudes(Proveedor proveedor);
        vector <string> listarTiposDePago(Proveedor proveedor);

        // Funciones que están son pública, pero NO deben usarse en FRONT. grasias ;)
        int registrarProducto(const char *correo_proveedor, producto_cantidad pxq);
        int registrarTipoDePago(const char *correo_proveedor, const char *descripcion);

};
#endif // MYSQLCONNECTION_H
