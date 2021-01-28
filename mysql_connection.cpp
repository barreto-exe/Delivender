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

char *MySQLConnection::timeToString(time_t *fecha)
{
    struct tm * timeinfo;
    char *str = new char[11] ();

    time(fecha);
    timeinfo = localtime(fecha);

    strftime(str, 11, "%d/%m/%Y", timeinfo);
    return str;
}

int MySQLConnection::obtenerIdProducto(Producto *producto)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    try
    {
        pstmt = con->prepareStatement("SELECT * FROM productos WHERE nombre = ? AND precio = ?");
        pstmt->setString(1, producto->getNombre());
        pstmt->setDouble(2, producto->getPrecio());
        res = pstmt->executeQuery();

        if (res->next())
        {
            int id = res->getInt("id_producto");
            delete pstmt;
            delete res;
            return id;
        }

        delete pstmt;
        delete res;
        return 0;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    delete pstmt;
    delete res;
    return -1;
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
        pstmt->executeQuery();
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

        pstmt = con->prepareStatement("SELECT * FROM almacenes WHERE correo_proveedor = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        proveedor->getAlmacen().clear();

        while (res->next())
        {
            Producto *producto = instanciarProducto(res->getInt("id_producto"));
            int cantidad = res->getInt("cantidad");
            producto_cantidad *pxq = new producto_cantidad;
            pxq->cantidad = cantidad;
            pxq->producto = producto;
            proveedor->getAlmacen().push_back(*pxq);
        }

        delete res;
        delete pstmt;
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

Producto *MySQLConnection::instanciarProducto(const int id_producto)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM productos WHERE id_producto = ?");
        pstmt->setInt(1, id_producto);
        res = pstmt->executeQuery();

        if (res->next())
        {
            Producto *producto = new Producto();
            producto->setNombre(res->getString("nombre"));
            producto->setDescripcion(res->getString("descripcion"));
            producto->setPrecio(res->getDouble("precio"));

            delete res;
            delete pstmt;
            return producto;
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
            persona->setFechaNacimiento(new time_t());
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

/*********************************************************** FUNCIONES PÚBLICAS ****************************************************************/
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
        {
            Proveedor *proveedor = instanciarProveedor(res->getString("correo").c_str());

            delete res;
            delete stmt;

            lista.push_back(*proveedor);
        }

        delete res;
        delete stmt;

    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    return lista;
}

/***************************************************** FUNCIONES "PROTEGIDAS" *****************************************************/

int MySQLConnection::registrarProducto(Producto *producto)
{
    sql::PreparedStatement *pstmt;
    try
    {
        pstmt = con->prepareStatement("INSERT INTO productos(nombre,descripcion,precio) VALUES (?, ?, ?)");

        pstmt->setString(1, producto->getNombre());
        pstmt->setString(2, producto->getDescripcion());
        pstmt->setDouble(3, producto->getPrecio());
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

int MySQLConnection::agregarProductoAlmacen(const char *correo_proveedor, producto_cantidad *pxq)
{
    sql::PreparedStatement *pstmt;
    try
    {
        pstmt = con->prepareStatement("INSERT INTO almacenes(correo_proveedor,id_producto,cantidad) VALUES (?, ?, ?)");

        pstmt->setString(1, correo_proveedor);
        pstmt->setInt(2, obtenerIdProducto(pxq->producto));
        pstmt->setInt(3, pxq->cantidad);
        pstmt->execute();
        qDebug() << "El producto se registró con éxito en el almacén uwu";
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
