#include "global.h"

MySQLConnection Global::db = MySQLConnection();
Persona *Global::cliente = 0;
Persona *Global::transportista = 0;
Proveedor *Global::proveedor = 0;
Proveedor Global::proveedorSeleccionado;
vector <producto_cantidad> Global::pedido;
