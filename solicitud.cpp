// Impplementación de la clase Solicitud
#include "solicitud.h"

Solicitud::Solicitud(Proveedor proveedor, Persona cliente, string tipoPago, float monto, string fechaPedido, string fechaEntrega, string direccion)
{
    this->proveedor = proveedor;
    this->cliente = cliente;
    this->tipoPago = tipoPago;
    this->monto = monto;
    this->fechaPedido = fechaPedido;
    this->fechaEntrega = fechaEntrega;
    this->direccion = direccion;
}

// Establece el proveedor
Solicitud &Solicitud::setProveedor(Proveedor proveedor)
{
    this->proveedor = proveedor;

    return *this; // Permite el proceso en cascada
}

// Establece el cliente
Solicitud &Solicitud::setCliente(Persona cliente)
{
    this->cliente = cliente;

    return *this; // Permite el proceso en cascada
}

// Establece el tipo de pago
Solicitud &Solicitud::setTipoPago(string tipoPago)
{
    this->tipoPago = tipoPago;
    
    return  *this; // Permite el proceso en cascada
}

// Establece el monto
Solicitud &Solicitud::setMonto(float monto)
{
    this->monto = monto;
    
    return  *this; // Permite el proceso en cascada
}

// Establece la fecha de realizacion de pedido
Solicitud &Solicitud::setFechaPedido(string fechaPedido)
{
    this->fechaPedido = fechaPedido;
    
    return  *this; // Permite el proceso en cascada
}

// Establece la fecha de realizacion de entrega
Solicitud &Solicitud::setFechaEntrega(string fechaEntrega)
{
    this->fechaEntrega = fechaEntrega;
    
    return  *this; // Permite el proceso en cascada
}

// Establece el estatus
Solicitud &Solicitud::setEstatus(string estatus)
{
    this->estatus = estatus;
    
    return  *this; // Permite el proceso en cascada
}

// Establece la dirección
Solicitud &Solicitud::setDireccion(string direccion)
{
    this->direccion = direccion;

    return *this; // Permite el proceso en cascada
}

// Devuelve el proveedor
Proveedor Solicitud::getProveedor() const { return proveedor; }

// Devuelve el cliente
Persona Solicitud::getCliente() const { return cliente; }

// Devuelve el tipo de pago
string Solicitud::getTipoPago() const { return tipoPago; }

// Devuelve el monto
float Solicitud::getMonto() const { return monto; }

// Devuelve la fecha de realización del pedido
string Solicitud::getFechaPedido() const { return fechaPedido; }

// Devuelve la fecha de realización de la entrega
string Solicitud::getFechaEntrega() const { return fechaEntrega; }

// Devuelve el estatus
string Solicitud::getEstatus() const { return estatus; }

// Devuelve la direccion
string Solicitud::getDireccion() const { return direccion; }
