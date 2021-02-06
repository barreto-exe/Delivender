// Declaración de la clase Solicitud
// Implementación en solicitud.cpp

// Evita más de una inclusión del archivo de encabezado
#ifndef SOLICITUD_H
#define SOLICITUD_H

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
        QDate fechaPedido;
        QDate fechaEntrega;
        string estatus;
        string direccion;
        vector <producto_cantidad> pedido;
        int id;

    public:
        // Constructor
        Solicitud();
        Solicitud(Proveedor proveedor, Persona cliente, string tipoPago, float monto, QDate fechaPedido, QDate fechaEntrega, string direccion, vector <producto_cantidad> pedido);
        Solicitud(Persona cliente, string tipoPago, float monto, QDate fechaPedido, QDate fechaEntrega, string direccion, vector <producto_cantidad> pedido);
        Solicitud(Proveedor proveedor, string tipoPago, float monto, QDate fechaPedido, QDate fechaEntrega, string direccion, vector <producto_cantidad> pedido);

        //Funciones set
        Solicitud &setProveedor(Proveedor proveedor);
        Solicitud &setCliente(Persona cliente);
        Solicitud &setTipoPago(string tipoPago);
        Solicitud &setMonto(float monto);
        Solicitud &setFechaPedido(QDate fechaPedido);
        Solicitud &setFechaEntrega(QDate fechaEntrega);
        Solicitud &setEstatus(string estatus);
        Solicitud &setDireccion(string direccion);
        Solicitud &setPedido(vector <producto_cantidad> pedido);
        Solicitud &setId(int id);

        //Funciones get
        Proveedor getProveedor() const;
        Persona getCliente() const;
        string getTipoPago() const;
        float getMonto() const;
        QDate getFechaPedido() const;
        QDate getFechaEntrega() const;
        string getEstatus() const;
        string getDireccion() const;
        vector <producto_cantidad> getPedido() const;
        int getId() const;

        // Funciones
        Solicitud &agregarProducto(producto_cantidad producto);
};

#endif // SOLICITUD_H
