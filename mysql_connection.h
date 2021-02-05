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
#include"transportista.h"
#include"cliente.h"

using std::string;

// Clase para conectar el Front con la BDD remota a través de funciones
class MySQLConnection
{
    private:
        // Atributos
        sql::Driver *driver;
        sql::Connection *con;

        /******************************************** FUNCIONES PRIVADAS ********************************************/
        char *encriptar(const char *password); //
        // Verificaciones
        int verificarCorreo(const char *correo); //
        int verificarCedula(const char *cedula); //
        int verificarPlaca(const char *placa); //
        // Registros
        int registrarUsuario(const char *correo, const char *password, const char *tipo); //
        int registrarPersona(const Persona persona); //
        int registrarPedido(const char *correo_proveedor, vector <producto_cantidad> pedido, const int id_solicitud); //
        int registrarProducto(const char *correo_proveedor, producto_cantidad pxq); //
        int registrarTipoDePago(const char *correo_proveedor, const char *descripcion); //
        // Instancias
        Proveedor *instanciarProveedor(const char *correo); //
        vector<producto_cantidad> instanciarAlmacen(Proveedor *proveedor);
        Cliente *instanciarCliente(const char *correo); //
        Transportista *instanciarTransportista(const char *correo); //
        vector<producto_cantidad> instanciarPedido(Solicitud *solicitud);
        producto_cantidad instanciarProductoCantidad(const int id);
        Solicitud *instanciarSolicitud(Persona cliente, const int id);
        Solicitud *instanciarSolicitud(Proveedor proveedor, const int id);
        // Obtener ID
        int obtenerIdTipoDePago(const char *correo_proveedor, const char *tipo); //
        int obtenerIdProducto(const char *correo_proveedor, Producto producto); //
        int obtenerIdSolicitud(Solicitud solicitud); //
        const char *obtenerTipoDePago(const int id); //
        // Actualización de datos
        int modificarEstatusSolicitud(const int id_solicitud, const char *estatus);//*******************
        int actualizarAlmacen(const char *correo_proveedor, const int id_producto, const int cantidad);

    public:
        // Constructor
        MySQLConnection();

        // Funciones get
        sql::Connection *getConnection() const;

        /******************************************** FUNCIONES PÚBLICAS ********************************************/
        producto_cantidad structProductoCantidad(Producto producto, int cantidad);
        // Inicio de sesión
        int iniciarSesion(const char *correo, const char *password); //
        // Registro de usuarios
        int registrarCliente(Persona cliente, const char *correo, const char *password);
        int registrarProveedor(Proveedor proveedor, const char *correo, const char *password);
        int registrarTransportista(Persona transportista, Vehiculo vehiculo, const char *correo, const char *password);
        int registrarVehiculo(Vehiculo vehiculo, const char *correo_transportista);
        // Funciones para CLIENTES
        int registrarSolicitud(Solicitud solicitud); //
        vector <string> listarTiposDePago(Proveedor proveedor); //
        //Funciones para PROVEEDORES
        vector <string> listarTiposDePago(); //
        int agregarProductoAlmacen(Producto producto, int cantidad); //
        int agregarTipoDePago(const char *descripcion); //
        int aprobarSolicitud(const int id_solicitud); //
        int rechazarSolicitud(const int id_solicitud); //
        // Funciones GENÉRICAS
        vector <Proveedor> listarProveedores(); //
        vector <Solicitud> listarSolicitudes(); //

        /* Notas para mi:
         * Recuerda mover la verificacion de producto de la funcion de registro
         * Recuerda cambiar los parámetros de modificar estatus solicitud
         */

};
#endif // MYSQLCONNECTION_H
