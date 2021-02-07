#include "global.h"

MySQLConnection Global::db = MySQLConnection();
Usuario *Global::usuario = 0;
string Global::tipoDeUsuario = "";
vector <producto_cantidad> Global::pedido;
Proveedor Global::proveedorSeleccionado;
