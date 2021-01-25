#include "mysql_connection.h"
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
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
}


// Devuelve connection SQL
sql::Connection *MySQLConnection::getConnection() const { return con; }


/*********************************************************** FUNCIONES PRIVADAS *****************************************************************/
// Retorna el parámetro encriptado
char *MySQLConnection::encriptar(char *password)
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

int MySQLConnection::obtenerIdUsuario(char *correo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    try
    {
        pstmt = con->prepareStatement("SELECT * FROM usuarios WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        while (res->next())
        {
            int id = res->getInt("id_usuario");
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
        return -1;
    }
}

int MySQLConnection::registrarUsuario(char *correo, char *password, char *tipo)
{
    sql::PreparedStatement *pstmt;
    try
    {
        int id = obtenerIdUsuario(correo);
        if (id)
        {
            qDebug() << "Este correo ya fue registrado";
            return 0;
        }

        pstmt = con->prepareStatement("INSERT INTO usuarios(correo,password,tipo_de_usuario) VALUES (?, ?, ?)");

        pstmt->setString(1, correo);
        pstmt->setString(2, encriptar(password));
        pstmt->setString(3, tipo);
        pstmt->execute();
        delete pstmt;
        qDebug() << "El usuario se registró con éxito uwu";
        return 1;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
        return 0;
    }
}

int MySQLConnection::registrarPersona(Persona persona, int id_usuario)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    // Verifico si la cédula corresponde a un usuario registrado
    try
    {
        pstmt = con->prepareStatement("SELECT * FROM personas WHERE cedula = ?");
        pstmt->setString(1, persona.getCedula().c_str());
        res = pstmt->executeQuery();

        while (res->next())
        {
            delete pstmt;
            delete res;
            return 0;
        }
        delete pstmt;
        delete res;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
        return 0;
    }

    // Registro los datos de la persona en la tabla personas
    try
    {
        pstmt = con->prepareStatement("INSERT INTO personas(cedula,id_usuario,nombre,apellido,telefono,direccion,fecha_nacimiento) VALUES (?, ?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, persona.getCedula().c_str());
        pstmt->setInt(2, id_usuario);
        pstmt->setString(3, persona.getNombre().c_str());
        pstmt->setString(4, persona.getApellido().c_str());
        pstmt->setString(5, persona.getTelefono().c_str());
        pstmt->setString(6, persona.getDireccion().c_str());
        pstmt->setString(7, timeToString(persona.getFechaNacimiento()));
        pstmt->executeQuery();
        delete pstmt;
        qDebug() << "La persona se registró con éxito uwu";
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


/*********************************************************** FUNCIONES PÚBLICAS ****************************************************************/
/* Entra a la BDD y comprueba el inicio de sesión
*  Retorna 1: cuando los datos son válidos y se inicia sesión
*  Retorna -1: cuando el correo está registrado, pero la contraseña no coincide
*  Retorna 0: cuando el correo no está registrado en la BDD
*  Retorna -2: cuando no se pudo conectar a la BDD
*/
int MySQLConnection::iniciarSesion(char *correo, char *password)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM usuarios WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        while (res->next())
        {
            if (!strcmp(encriptar(password), res->getString("password").c_str()))
            {
                // Entonces el correo está registrado y la contraseña coincide
                // Se debería instanciar una persona o un proveedor, de acuerdo al tipo de usuario
                delete res;
                delete pstmt;
                qDebug() << "Ha iniciado sesión";
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
        return -2;
    }
}

int MySQLConnection::registrarCliente(Persona cliente, char *correo, char *password)
{
    char tipo[8] = "cliente";
    if (!registrarUsuario(correo, password, tipo))
    {
        qDebug() << "Ya existe un usuario registrado con este correo";
        return 0;
    }

    return registrarPersona(cliente, obtenerIdUsuario(correo));
}

int MySQLConnection::registrarProveedor(Proveedor proveedor, char *correo, char *password)
{
    char tipo[10] = "proveedor";
    if (!registrarUsuario(correo, password, tipo))
    {
        qDebug() << "Ya existe un usuario registrado con este correo";
        return 0;
    }

    sql::PreparedStatement *pstmt;

    // Registro los datos de la empresa en la tabla proovedores
    try
    {
        pstmt = con->prepareStatement("INSERT INTO proveedores(id_usuario,nombre,descripcion,tipo_de_proveedor,telefono,direccion) VALUES (?, ?, ?, ?, ?, ?)");
        pstmt->setInt(1, obtenerIdUsuario(correo));
        pstmt->setString(2, proveedor.getNombre().c_str());
        pstmt->setString(3, proveedor.getDescripcion().c_str());
        pstmt->setString(4, proveedor.getTipoProveedor().c_str());
        pstmt->setString(5, proveedor.getTelefono().c_str());
        pstmt->setString(6, proveedor.getDireccion().c_str());
        pstmt->executeQuery();
        delete pstmt;
        qDebug() << "El proveedor se registró con éxito uwu";
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

int MySQLConnection::registrarTransportista(Persona transportista, Vehiculo vehiculo, char *correo, char *password)
{
    char tipo[15] = "transportista";
    if (!registrarUsuario(correo, password, tipo))
    {
        qDebug() << "Ya existe un usuario registrado con este correo. Inicie sesión para registrar un vehículo";
        return 0;
    }

    if (!registrarPersona(transportista, obtenerIdUsuario(correo)))
    {
        qDebug() << "Ya existe una persona registrada con esta cédula";
        return 0;
    }

    return registrarVehiculo(vehiculo, transportista.getCedula().c_str());
}

int MySQLConnection::registrarVehiculo(Vehiculo vehiculo, char const *cedula_transportista)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    // Verifico si la placa corresponde a un vehiculo registrado
    try
    {
        pstmt = con->prepareStatement("SELECT * FROM vehiculos WHERE placa = ?");
        pstmt->setString(1, vehiculo.getPLaca().c_str());
        res = pstmt->executeQuery();

        while (res->next())
        {
            delete pstmt;
            delete res;
            return 0;
        }
        delete pstmt;
        delete res;
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
        return 0;
    }

    // Registro los datos del vehiculo en la tabla vehiculos
    try
    {
        pstmt = con->prepareStatement("INSERT INTO vehiculos(placa,cedula_transportista,modelo,tipo_de_vehiculo) VALUES (?, ?, ?, ?)");
        pstmt->setString(1, vehiculo.getPLaca().c_str());
        pstmt->setString(2, cedula_transportista);
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
