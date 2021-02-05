#include "global.h"

MySQLConnection Global::db = MySQLConnection();
Usuario *Global::usuario = 0;
vector <producto_cantidad> Global::pedido;
Proveedor Global::proveedorSeleccionado;
