#include "global.h"

MySQLConnection Global::db = MySQLConnection();
Usuario *Global::usuario = 0;
string Global::tipoDeUsuario = "";
Solicitud Global::solicitud = Solicitud();
Proveedor Global::proveedorSeleccionado;
