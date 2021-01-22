// Declaración de la clase Solicitud
// Implementación en solicitud.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <ctime>
#include <string>
#include "proveedor.h"
#include "persona.h"
#include "producto_cantidad.h"

using std::string;

// Clase para solicitudes de compra
class Solicitud
{
    private:
        // Atributos
        Proveedor proveedor;
        Persona cliente;
        string tipoPago;
        float monto;
        time_t fechaPedido;
        time_t fechaEntrega;
        string estatus;
        string direccion;
        ProductoCantidad funcionaaaaaa; // Hay que ponerlo en el constructor también y todo esop
        // falta declarar la estructura que relaciona el producto con su cantidad --- arreglo de struct para ver detalles de la solicitud

    public:
        // Constructor
        Solicitud(Proveedor proveedor, Persona cliente, string tipoPago = "", float monto = 0, time_t fechaPedido = 0, time_t fechaEntrega = 0, string direccion = "");

        //Funciones set
        Solicitud &setProveedor(Proveedor proveedor);
        Solicitud &setCliente(Persona cliente);
        Solicitud &setTipoPago(string tipoPago);
        Solicitud &setMonto(float monto);
        Solicitud &setFechaPedido(time_t fechaPedido);
        Solicitud &setFechaEntrega(time_t fechaEntrega);
        Solicitud &setEstatus(string estatus);
        Solicitud &setDireccion(string direccion);

        //Funciones get
        Proveedor getProveedor() const;
        Persona getCliente() const;
        string getTipoPago() const;
        float getMonto() const;
        time_t getFechaPedido() const;
        time_t getFechaEntrega() const;
        string getEstatus() const;
        string getDireccion() const;
};

#endif // SOLICITUD_H
