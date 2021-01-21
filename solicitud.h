// Declaración de la clase Solicitud
// Implementación en solicitud.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <ctime>
#include <string>
#include <proveedor.h>
#include <persona.h>
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
        string fechaPedido;
        string fechaEntrega;
        string estatus;
        string direccion;
        // falta declarar la estructura que relaciona el producto con su cantidad --- arreglo de struct para ver detalles de la solicitud

    public:
        // Constructor
        Solicitud(Proveedor proveedor, Persona cliente, string tipoPago, float monto, string fechaPedido, string fechaEntrega, string direccion);

        //Funciones set
        Solicitud &setProveedor(Proveedor proveedor);
        Solicitud &setCliente(Persona cliente);
        Solicitud &setTipoPago(string tipoPago);
        Solicitud &setMonto(float monto);
        Solicitud &setFechaPedido(string fechaPedido);
        Solicitud &setFechaEntrega(string fechaEntrega);
        Solicitud &setEstatus(string estatus);
        Solicitud &setDireccion(string direccion);

        //Funciones get
        Proveedor getProveedor() const;
        Persona getCliente() const;
        string getTipoPago() const;
        float getMonto() const;
        string getFechaPedido() const;
        string getFechaEntrega() const;
        string getEstatus() const;
        string getDireccion() const;
};

#endif // SOLICITUD_H
