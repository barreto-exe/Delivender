#include "mysql_connection.h"
#include"global.h"
#include <QDebug>
#include <QMessageBox>
#include<ctime>

// Constructor
MySQLConnection::MySQLConnection()
{
    try
    {
        sql::ConnectOptionsMap connection_properties;

        // Opciones de conexión
        connection_properties["hostName"] = "remotemysql.com";
        connection_properties["userName"] = "yIcFv8vCet";
        connection_properties["password"] = "2ZauAV6dye";
        connection_properties["schema"] = "yIcFv8vCet";
        connection_properties["port"] = 3306;
        connection_properties["OPT_RECONNECT"] = true;
        connection_properties["OPT_CONNECT_TIMEOUT"] = 4;
        connection_properties["OPT_READ_TIMEOUT"] = 2;
        connection_properties["OPT_WRITE_TIMEOUT"] = 2;

        // Establece la conexión a la base de datos
        driver = get_driver_instance();
        con = driver->connect(connection_properties);

    }
    catch (sql::SQLException &e)
    {
        con = 0;
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
        con = 0;
    }
}


// Devuelve connection SQL
sql::Connection *MySQLConnection::getConnection() const { return con; }


/*********************************************************** FUNCIONES PRIVADAS *****************************************************************/
// Retorna el parámetro encriptado
char *MySQLConnection::encriptar(const char *password)
{
    if (!password)
        return nullptr;

    int size = strlen(password);
    int i = 0;
    char *str = new char[size + 1]();

    for (; password[i] != '\0'; i++)
        str[i] = password[i] + i + 3;
    str[i] = '\0';

    return str;
}

char *MySQLConnection::timeToString(time_t fecha)
{
    struct tm * timeinfo;
    char *str = new char[11] ();

    time(&fecha);
    timeinfo = localtime(&fecha);

    strftime(str, 11, "%d/%m/%Y", timeinfo);
    return str;
}

int MySQLConnection::verificarCorreo(const char *correo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM usuarios WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        if (res->next())
        {
            delete pstmt;
            delete res;
            return 1;
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete pstmt;
    delete res;
    return 0;
}

// Verifica si la cédula corresponde a una persona registrada
int MySQLConnection::verificarCedula(const char *cedula)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM personas WHERE cedula = ?");
        pstmt->setString(1, cedula);
        res = pstmt->executeQuery();

        if (res->next())
        {
            delete pstmt;
            delete res;
            return 1;
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete pstmt;
    delete res;
    return 0;
}

// Verifica si la placa corresponde a un vehiculo registrado
int MySQLConnection::verificarPlaca(const char *placa)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM vehiculos WHERE placa = ?");
        pstmt->setString(1, placa);
        res = pstmt->executeQuery();

        if (res->next())
        {
            delete pstmt;
            delete res;
            return 1;
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete pstmt;
    delete res;
    return 0;
}

int MySQLConnection::registrarUsuario(const char *correo, const char *password, const char *tipo)
{
    sql::PreparedStatement *pstmt;
    try
    {
        pstmt = con->prepareStatement("INSERT INTO usuarios(correo,password,tipo_de_usuario) VALUES (?, ?, ?)");

        pstmt->setString(1, correo);
        pstmt->setString(2, encriptar(password));
        pstmt->setString(3, tipo);
        pstmt->execute();
        qDebug() << "El usuario se registró con éxito uwu";
        delete pstmt;
        return 1;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";        
    }
    delete pstmt;
    return 0;
}

int MySQLConnection::registrarPersona(Persona persona)
{
    sql::PreparedStatement *pstmt;

    // Registro los datos de la persona en la tabla personas
    try
    {
        pstmt = con->prepareStatement("INSERT INTO personas(correo,nombre,apellido,cedula,telefono,direccion,fecha_nacimiento) VALUES (?, ?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, persona.getCorreo().c_str());
        pstmt->setString(2, persona.getNombre().c_str());
        pstmt->setString(3, persona.getApellido().c_str());
        pstmt->setString(4, persona.getCedula().c_str());
        pstmt->setString(5, persona.getTelefono().c_str());
        pstmt->setString(6, persona.getDireccion().c_str());
        pstmt->setString(7, timeToString(persona.getFechaNacimiento()));
        pstmt->execute();
        qDebug() << "La persona se registró con éxito uwu";
        delete pstmt;
        return 1;

    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete pstmt;
    return 0;
}

int MySQLConnection::registrarPedido(const char *correo_proveedor, vector<producto_cantidad> pedido, const int id_solicitud)
{
    sql::PreparedStatement *pstmt;

    for (std::size_t i = 0; i < pedido.size(); i++)
    {
        try
        {
            pstmt = con->prepareStatement("INSERT INTO solicitudes_detalles(id_solicitud,id_producto,cantidad) VALUES (?, ?, ?)");
            pstmt->setInt(1, id_solicitud);
            pstmt->setInt(2, obtenerIdProducto(correo_proveedor, pedido[i].producto));
            pstmt->setInt(3, pedido[i].cantidad);
            pstmt->execute();
        }
        catch (sql::SQLException &e)
        {
            // Error de conexión
            qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
            qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
            delete pstmt;
            return 0;
        }
        delete pstmt;
    }
    return 1;
}

Proveedor *MySQLConnection::instanciarProveedor(const char *correo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    Proveedor *proveedor = 0;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM proveedores WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        if (res->next())
        {
            proveedor = new Proveedor();
            proveedor->setNombre(res->getString("nombre"));
            proveedor->setDescripcion(res->getString("descripcion"));
            proveedor->setTelefono(res->getString("telefono"));
            proveedor->setDireccion(res->getString("direccion"));
            proveedor->setTipoProveedor(res->getString("tipo_de_proveedor"));
            proveedor->setCorreo(correo);
        }
        else
        {
            delete res;
            delete pstmt;
            return 0;
        }

        delete res;
        delete pstmt;

        instanciarAlmacen(proveedor);
        return proveedor;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete res;
    delete pstmt;
    return 0;
}

void MySQLConnection::instanciarAlmacen(Proveedor *proveedor)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM productos WHERE correo_proveedor = ?");
        pstmt->setString(1, (*proveedor).getCorreo());
        res = pstmt->executeQuery();

        while (res->next())
        {
            Producto producto = Producto();
            producto.setNombre(res->getString("nombre"));
            producto.setDescripcion(res->getString("descripcion"));
            producto.setPrecio(res->getDouble("precio"));
            int cantidad = res->getInt("cantidad");
            (*proveedor).getAlmacen().push_back(structProductoCantidad(producto, cantidad));
        }

    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete res;
    delete pstmt;
    return;

}

Persona *MySQLConnection::instanciarPersona(const char *correo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM personas WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        if (res->next())
        {
            Persona *persona = new Persona();
            persona->setNombre(res->getString("nombre"));
            persona->setApellido(res->getString("apellido"));
            persona->setTelefono(res->getString("telefono"));
            persona->setDireccion(res->getString("direccion"));
            persona->setFechaNacimiento(time_t());
            persona->setCorreo(correo);

            delete res;
            delete pstmt;
            return persona;
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return 0;
}

void MySQLConnection::instanciarPedido(Solicitud *solicitud)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    vector <producto_cantidad> pedido = vector <producto_cantidad>();

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM solicitudes_detalles WHERE id_solicitud = ?");
        pstmt->setInt(1, obtenerIdSolicitud(*solicitud));
        res = pstmt->executeQuery();

        while (res->next())
        {
            (*solicitud).getPedido().push_back(instanciarProductoCantidad(res->getInt("id_producto")));
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
}

producto_cantidad MySQLConnection::instanciarProductoCantidad(const int id)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM productos WHERE id_producto = ?");
        pstmt->setInt(1, id);
        res = pstmt->executeQuery();

        if (res->next())
        {
            Producto producto = Producto();
            producto.setNombre(res->getString("nombre"));
            producto.setDescripcion(res->getString("descripcion"));
            producto.setPrecio(res->getDouble("precio"));
            int cantidad = res->getInt("cantidad");

            delete res;
            delete pstmt;
            return structProductoCantidad(producto, cantidad);
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return producto_cantidad();
}

Solicitud *MySQLConnection::instanciarSolicitud(Persona cliente, const int id)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE id_solicitud = ?");
        pstmt->setInt(1, id);
        res = pstmt->executeQuery();

        if (res->next())
        {
            Solicitud *solicitud = new Solicitud();
            solicitud->setCliente(cliente);
            solicitud->setProveedor(*instanciarProveedor(res->getString("correo_proveedor").c_str()));
            solicitud->setMonto(res->getDouble("monto"));
            solicitud->setTipoPago(obtenerTipoDePago(res->getInt("id_tipo_de_pago")));
            solicitud->setDireccion(res->getString("direccion"));
            solicitud->setFechaPedido(time_t());
            solicitud->setFechaEntrega(time_t());
            solicitud->setEstatus(res->getString("estatus"));

            delete res;
            delete pstmt;
            return solicitud;
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return 0;
}

Solicitud *MySQLConnection::instanciarSolicitud(Proveedor proveedor, const int id)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE id_solicitud = ?");
        pstmt->setInt(1, id);
        res = pstmt->executeQuery();

        if (res->next())
        {
            Solicitud *solicitud = new Solicitud();
            solicitud->setCliente(*instanciarPersona(res->getString("correo_cliente").c_str()));
            solicitud->setProveedor(proveedor);
            solicitud->setMonto(res->getDouble("monto"));
            solicitud->setTipoPago(obtenerTipoDePago(res->getInt("id_tipo_de_pago")));
            solicitud->setDireccion(res->getString("direccion"));
            solicitud->setFechaPedido(time_t());
            solicitud->setFechaEntrega(time_t());
            solicitud->setEstatus(res->getString("estatus"));

            delete res;
            delete pstmt;
            return solicitud;
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return 0;
}

int MySQLConnection::obtenerIdTipoDePago(const char *correo_proveedor, const char *tipo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    int id = 0;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM tipos_de_pago WHERE correo_proveedor = ? AND descripcion = ?");
        pstmt->setString(1, correo_proveedor);
        pstmt->setString(2, tipo);
        res = pstmt->executeQuery();

        if (res->next())
            id = res->getInt("id_tipo_de_pago");
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return id;
}

int MySQLConnection::obtenerIdProducto(const char *correo_proveedor, Producto producto)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    int id = 0;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM productos WHERE correo_proveedor = ? AND nombre = ? AND precio = ?");
        pstmt->setString(1, correo_proveedor);
        pstmt->setString(2, producto.getNombre());
        pstmt->setDouble(3, producto.getPrecio());
        res = pstmt->executeQuery();

        if (res->next())
            id = res->getInt("id_producto");
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return id;
}

int MySQLConnection::obtenerIdSolicitud(Solicitud solicitud)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    int id = 0;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE correo_proveedor = ? AND correo_cliente = ? AND monto = ? AND fecha_de_creacion = ? AND direccion = ? AND estatus = ?");
        pstmt->setString(1, solicitud.getProveedor().getCorreo().c_str());
        pstmt->setString(2, solicitud.getCliente().getCorreo().c_str());
        pstmt->setDouble(3, solicitud.getMonto());
        pstmt->setString(4, timeToString(solicitud.getFechaPedido()));
        pstmt->setString(5, solicitud.getDireccion().c_str());
        pstmt->setString(6, solicitud.getEstatus().c_str());
        res = pstmt->executeQuery();

        if (res->next())
            id = res->getInt("id_solicitud");
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return id;
}

const char *MySQLConnection::obtenerTipoDePago(const int id)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM tipos_de_pago WHERE id_tipo_de_pago = ?");
        pstmt->setInt(1, id);
        res = pstmt->executeQuery();

        if (res->next())
        {
            const char *tipo= new char(30);
            tipo = res->getString("descripcion").c_str();
            delete res;
            delete pstmt;
            return tipo;
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return 0;
}

/*********************************************************** FUNCIONES PÚBLICAS ****************************************************************/
producto_cantidad MySQLConnection::structProductoCantidad(Producto producto, int cantidad)
{
    producto_cantidad pxq = producto_cantidad();
    pxq.producto = producto;
    pxq.cantidad = cantidad;
    return pxq;
}

/* Entra a la BDD y comprueba el inicio de sesión
*  Retorna 1: cuando los datos son válidos y se inicia sesión
*  Retorna -1: cuando el correo está registrado, pero la contraseña no coincide
*  Retorna 0: cuando el correo no está registrado en la BDD
*  Retorna -2: cuando no se pudo conectar a la BDD
*/
int MySQLConnection::iniciarSesion(const char *correo, const char *password)
{
    if (con == 0)
        return -2;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM usuarios WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        if (res->next())
        {
            if (!strcmp(encriptar(password), res->getString("password").c_str()))
            {  // Entonces el correo está registrado y la contraseña coincide
                const string tipo = res->getString("tipo_de_usuario");
                delete res;
                delete pstmt;

                qDebug() << "Ha iniciado sesión como" << tipo.c_str();

                // Instanciando proveedor global con los atributos de la BDD
                if (!strcmp(tipo.c_str(), "proveedor"))
                {
                    Global::proveedor = instanciarProveedor(correo);
                }
                else
                {
                    pstmt = con->prepareStatement("SELECT * FROM personas WHERE correo = ?");
                    pstmt->setString(1, correo);
                    res = pstmt->executeQuery();

                    Persona *persona;

                    if (res->next())
                    {
                        persona = instanciarPersona(correo);

                        // Instanciando cliente global con los atributos de la BDD
                        if (!strcmp(tipo.c_str(), "cliente"))
                        {
                            Global::cliente = persona;
                        }
                        // Instanciando transportista global con los atributos de la BDD
                        else if (!strcmp(tipo.c_str(), "transportista"))
                        {
                            Global::transportista = persona;
                        }
                        else
                        {
                            delete res;
                            delete pstmt;
                            return -2;
                        }
                    }
                }
                delete res;
                delete pstmt;
                return 1;
            }
            // Entonces se encontró el correo, pero la contraseña no coincide
            delete res;
            delete pstmt;
            qDebug() << "Contraseña incorrecta";
            return -1;
        }

        // Si llega aquí es porque el correo no está registrado
        delete res;
        delete pstmt;
        qDebug() << "El correo no está registrado";
        return 0;


    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete res;
    delete pstmt;
    return -2;
}

int MySQLConnection::registrarCliente(Persona cliente, const char *correo, const char *password)
{
    if (con == 0)
        return 0;

    if (verificarCorreo(correo))
    {
        qDebug() << "Este correo ya fue registrado";
        return 0;
    }

    if (verificarCedula(cliente.getCedula().c_str()))
    {
        qDebug() << "Esta cédula ya fue registrada";
        return 0;
    }

    char tipo[8] = "cliente";
    registrarUsuario(correo, password, tipo);
    registrarPersona(cliente);
    Global::cliente = &cliente;
    return 1;
}

int MySQLConnection::registrarProveedor(Proveedor proveedor, const char *correo, const char *password)
{
    if (con == 0)
        return 0;

    if (verificarCorreo(correo))
    {
        qDebug() << "Este correo ya fue registrado";
        return 0;
    }

    char tipo[10] = "proveedor";
    registrarUsuario(correo, password, tipo);

    sql::PreparedStatement *pstmt;

    // Registro los datos de la empresa en la tabla proovedores
    try
    {
        pstmt = con->prepareStatement("INSERT INTO proveedores(correo,nombre,descripcion,tipo_de_proveedor,telefono,direccion) VALUES (?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, correo);
        pstmt->setString(2, proveedor.getNombre().c_str());
        pstmt->setString(3, proveedor.getDescripcion().c_str());
        pstmt->setString(4, proveedor.getTipoProveedor().c_str());
        pstmt->setString(5, proveedor.getTelefono().c_str());
        pstmt->setString(6, proveedor.getDireccion().c_str());
        pstmt->executeQuery();
        delete pstmt;
        qDebug() << "El proveedor se registró con éxito uwu";
        Global::proveedor = &proveedor;
        return 1;

    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    return 0;
}

int MySQLConnection::registrarTransportista(Persona transportista, Vehiculo vehiculo, const char *correo,  const char *password)
{
    if (con == 0)
        return 0;

    if (verificarCorreo(correo))
    {
        qDebug() << "Este correo ya fue registrado";
        return 0;
    }

    if (verificarCedula(transportista.getCedula().c_str()))
    {
        qDebug() << "Esta cédula ya fue registrada";
        return 0;
    }

    if (verificarPlaca(vehiculo.getPLaca().c_str()))
    {
        qDebug() << "Esta placa ya fue registrada";
        return 0;
    }


    char tipo[15] = "transportista";
    registrarUsuario(correo, password, tipo);
    registrarPersona(transportista);
    registrarVehiculo(vehiculo, transportista.getCedula().c_str());
    Global::transportista = &transportista;
    return 1;
}

int MySQLConnection::registrarVehiculo(Vehiculo vehiculo, const char *correo_transportista)
{
    if (con == 0)
        return 0;

    sql::PreparedStatement *pstmt;

    // Registro los datos del vehiculo en la tabla vehiculos
    try
    {
        pstmt = con->prepareStatement("INSERT INTO vehiculos(placa,correo_transportista,modelo,tipo_de_vehiculo) VALUES (?, ?, ?, ?)");
        pstmt->setString(1, vehiculo.getPLaca().c_str());
        pstmt->setString(2, correo_transportista);
        pstmt->setString(3, vehiculo.getModelo().c_str());
        pstmt->setString(4, vehiculo.getTipo().c_str());
        pstmt->executeQuery();
        delete pstmt;
        qDebug() << "El vehiculo se registró con éxito uwu";
        return 1;

    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    return 0;
}

int MySQLConnection::registrarSolicitud(Solicitud solicitud)
{
    if (obtenerIdTipoDePago(solicitud.getProveedor().getCorreo().c_str(), solicitud.getTipoPago().c_str()))
    {
        qDebug() << "Ya existe este tipo de pago";
        return 0;
    }

    sql::PreparedStatement *pstmt;
    try
    {
        pstmt = con->prepareStatement("INSERT INTO solicitudes(correo_cliente,correo_proveedor,monto,id_tipo_de_pago,direccion,fecha_de_creacion,fecha_de_entrega,estatus) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, solicitud.getCliente().getCorreo().c_str());
        pstmt->setString(2, solicitud.getProveedor().getCorreo().c_str());
        pstmt->setDouble(3, solicitud.getMonto());
        pstmt->setInt(4, obtenerIdTipoDePago(solicitud.getProveedor().getCorreo().c_str(), solicitud.getTipoPago().c_str()));
        pstmt->setString(5, solicitud.getDireccion().c_str());
        pstmt->setString(6, timeToString(solicitud.getFechaPedido()));
        pstmt->setString(7, timeToString(solicitud.getFechaEntrega()));
        pstmt->setString(8, solicitud.getEstatus().c_str());
        pstmt->execute();
        qDebug() << "La solicitud fue registrada con éxito uwu";
        delete pstmt;

        int id = obtenerIdSolicitud(solicitud);

        return registrarPedido(solicitud.getProveedor().getCorreo().c_str(), solicitud.getPedido(), id);
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete pstmt;
    return 0;
}

vector <Proveedor> MySQLConnection::listarProveedores()
{
    vector <Proveedor> lista;

    sql::Statement *stmt;
    sql::ResultSet *res;

    try
    {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM proveedores");

        while (res->next())
            lista.push_back(*instanciarProveedor(res->getString("correo").c_str()));

    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete stmt;
    return lista;
}

vector <Solicitud> MySQLConnection::listarSolicitudes(Persona cliente)
{
    vector <Solicitud> lista;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE correo_cliente = ?");
        pstmt->setString(1, cliente.getCorreo().c_str());
        res = pstmt->executeQuery();

        while (res->next())
            lista.push_back(*instanciarSolicitud(cliente,res->getInt("id_solicitud")));
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return lista;
}


vector <Solicitud> MySQLConnection::listarSolicitudes(Proveedor proveedor)
{
    vector <Solicitud> lista;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE correo_proveedor = ?");
        pstmt->setString(1, proveedor.getCorreo().c_str());
        res = pstmt->executeQuery();

        while (res->next())
            lista.push_back(*instanciarSolicitud(proveedor,res->getInt("id_solicitud")));
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return lista;
}

vector <string> MySQLConnection::listarTiposDePago(Proveedor proveedor)
{
    vector <string> lista;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM tipos_de_pago WHERE correo_proveedor = ?");
        pstmt->setString(1, proveedor.getCorreo().c_str());
        res = pstmt->executeQuery();

        while (res->next())
            lista.push_back(res->getString("descripcion"));
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete res;
    delete pstmt;
    return lista;
}

/***************************************************** FUNCIONES "PROTEGIDAS" *****************************************************/
int MySQLConnection::registrarProducto(const char *correo_proveedor, producto_cantidad pxq)
{
    sql::PreparedStatement *pstmt;
    try
    {
        pstmt = con->prepareStatement("INSERT INTO productos(correo_proveedor,nombre,descripcion,precio,cantidad) VALUES (?, ?, ?, ?, ?)");

        pstmt->setString(1, correo_proveedor);
        pstmt->setString(2, pxq.producto.getNombre());
        pstmt->setString(3, pxq.producto.getDescripcion());
        pstmt->setDouble(4, pxq.producto.getPrecio());
        pstmt->setInt(5, pxq.cantidad);
        pstmt->execute();
        qDebug() << "El producto se registró con éxito uwu";
        delete pstmt;
        return 1;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete pstmt;
    return 0;
}

int MySQLConnection::registrarTipoDePago(const char *correo_proveedor, const char *descripcion)
{
    sql::PreparedStatement *pstmt;
    try
    {
        pstmt = con->prepareStatement("INSERT INTO tipos_de_pago(correo_proveedor,descripcion) VALUES (?, ?)");

        pstmt->setString(1, correo_proveedor);
        pstmt->setString(2, descripcion);
        pstmt->execute();
        qDebug() << "Se registró el tipo de pago";
        delete pstmt;
        return 1;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete pstmt;
    return 0;
}


int MySQLConnection::modificarEstatusSolicitud(const int id_solicitud, const char *estatus)
{
    sql::PreparedStatement *pstmt;

    try
    {
        pstmt = con->prepareStatement("UPDATE solicitudes SET estatus = ? WHERE id_solicitud = ?");
        pstmt->setString(1, estatus);
        pstmt->setInt(2, id_solicitud);
        pstmt->execute();

        delete pstmt;
        return 1;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete pstmt;
    return 0;
}

int MySQLConnection::actualizarAlmacen(const int id_proveedor, const int id_producto, const int cantidad)
{
    sql::PreparedStatement *pstmt;

    try
    {
        pstmt = con->prepareStatement("UPDATE productos SET cantidad = ? WHERE id_proveedor = ? AND id_producto = ?");
        pstmt->setInt(1, cantidad);
        pstmt->setInt(2, id_proveedor);
        pstmt->setInt(3, id_producto);
        pstmt->execute();

        delete pstmt;
        return 1;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    delete pstmt;
    return 0;
}
