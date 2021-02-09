#include"global.h"
#include <QDebug>
#include <QMessageBox>

using namespace std;

// Constructor
MySQLConnection::MySQLConnection()
{
    POR_ENTREGAR = "Pendiente por entregar";
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
    }
}


// Devuelve connection SQL
sql::Connection *MySQLConnection::getConnection() const { return con; }

/****************************************************************************************************************************************/
/********************************************************** FUNCIONES PRIVADAS **********************************************************/
/****************************************************************************************************************************************/

// Retorna el parámetro encriptado
char *MySQLConnection::encriptar(const char *password)
{
    if (!password)
        return nullptr;

    int size = strlen(password);
    int i = 0;
    char *str = new char[size + 1]();

    // Cambia los caracteres, modificando su código ascii
    for (; password[i] != '\0'; i++)
        str[i] = password[i] + i + 3;
    str[i] = '\0';

    return str;
}

/*********************************************************** VERIFICACIONES *************************************************************/

// Verifica si un correo corresponde  a un usuario registrado
int MySQLConnection::verificarCorreo(const char *correo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Consulta en la tabla de usuarios si hay un registro con el correo recibido por parámetro
        pstmt = con->prepareStatement("SELECT * FROM usuarios WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        if (res->next())
        {
            delete pstmt;
            delete res;
            // Retorna 1 si encuentra el correo
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
    // Retorna 0 si no encuentra el correo
    return 0;
}

// Verifica si la cédula corresponde a una persona registrada
int MySQLConnection::verificarCedula(const char *cedula)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Consulta en la tabla de personas si hay un registro con la cédula recibida por parámetro
        pstmt = con->prepareStatement("SELECT * FROM personas WHERE cedula = ?");
        pstmt->setString(1, cedula);
        res = pstmt->executeQuery();

        if (res->next())
        {
            delete pstmt;
            delete res;
            // Retorna 1 si encuentra la cédula
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
    // Retorna 0 si no encuentra la cédula
    return 0;
}

// Verifica si la placa corresponde a un vehiculo registrado
int MySQLConnection::verificarPlaca(const char *placa)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Consulta en la tabla de vehiculos si hay un registro con la placa recibida por parámetro
        pstmt = con->prepareStatement("SELECT * FROM vehiculos WHERE placa = ?");
        pstmt->setString(1, placa);
        res = pstmt->executeQuery();

        if (res->next())
        {
            delete pstmt;
            delete res;
            // Retorna 1 si encuentra la placa
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
    // Retorna 0 si no encuentra la placa
    return 0;
}

// Verifica si la placa de una entrega corresponde a algun vehiculo del transportista global
int MySQLConnection::verificarEntrega(const char *placa)
{
    Transportista *transportista = reinterpret_cast<Transportista*>(Global::usuario);

    // Comprueba todas las placas de los vehículos instanciados del transportista global, coincide con la recibida por parámetro
    for (std::size_t i = 0; i < transportista->getVehiculos().size(); i++)
        if (!strcmp(placa, transportista->getVehiculos()[i].getPLaca().c_str()))
            return 1;
    return 0;
}

/************************************************************* REGISTROS ****************************************************************/

// Registro de nuevo usuario
int MySQLConnection::registrarUsuario(const char *correo, const char *password, const char *tipo)
{
    sql::PreparedStatement *pstmt;
    try
    {
        // Inserta un registro en la tabla de usuarios
        pstmt = con->prepareStatement("INSERT INTO usuarios(correo,password,tipo_de_usuario) VALUES (?, ?, ?)");

        pstmt->setString(1, correo);
        pstmt->setString(2, encriptar(password));
        pstmt->setString(3, tipo);
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

// Registro de nueva persona
int MySQLConnection::registrarPersona(Persona persona)
{
    sql::PreparedStatement *pstmt;
    try
    {
        // Inserta un registro en la tabla de personas
        pstmt = con->prepareStatement("INSERT INTO personas(correo,nombre,apellido,cedula,telefono,direccion,fecha_nacimiento) VALUES (?, ?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, persona.getCorreo().c_str());
        pstmt->setString(2, persona.getNombre().c_str());
        pstmt->setString(3, persona.getApellido().c_str());
        pstmt->setString(4, persona.getCedula().c_str());
        pstmt->setString(5, persona.getTelefono().c_str());
        pstmt->setString(6, persona.getDireccion().c_str());
        pstmt->setString(7, persona.getFechaNacimiento().toString("dd/MM/yyyy").toStdString().c_str());
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

// Registro detalles de una solicitud de compra
int MySQLConnection::registrarPedido(const char *correo_proveedor, vector<producto_cantidad> pedido, const int id_solicitud)
{
    sql::PreparedStatement *pstmt;

    // Recorre todo el pedido e inserta los productos uno a uno en la tabla solicitudes_detalles
    for (std::size_t i = 0; i < pedido.size(); i++)
    {
        try
        {
            // Inserta un registro en la tabla
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
    return actualizarAlmacen(pedido, -1);
}

// Registro de un nuevo producto
int MySQLConnection::registrarProducto(const char *correo_proveedor, producto_cantidad pxq)
{
    sql::PreparedStatement *pstmt;
    try
    {
        // Inserta un registro en la tabla productos
        pstmt = con->prepareStatement("INSERT INTO productos(correo_proveedor,nombre,descripcion,precio,cantidad) VALUES (?, ?, ?, ?, ?)");

        pstmt->setString(1, correo_proveedor);
        pstmt->setString(2, pxq.producto.getNombre());
        pstmt->setString(3, pxq.producto.getDescripcion());
        pstmt->setDouble(4, pxq.producto.getPrecio());
        pstmt->setInt(5, pxq.cantidad);
        pstmt->execute();
        delete pstmt;
        (&pxq.producto)->setId(obtenerIdProducto(correo_proveedor, pxq.producto));
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

// Registro de nuevo tipo de pago
int MySQLConnection::registrarTipoDePago(const char *correo_proveedor, const char *descripcion)
{
    sql::PreparedStatement *pstmt;
    try
    {
        // Inserta un registro en la tabla tipos_de_pago
        pstmt = con->prepareStatement("INSERT INTO tipos_de_pago(correo_proveedor,descripcion) VALUES (?, ?)");

        pstmt->setString(1, correo_proveedor);
        pstmt->setString(2, descripcion);
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

// Registro de nueva entrega
int MySQLConnection::registrarEntrega(const int id_solicitud, const char *placa_vehiculo)
{
    sql::PreparedStatement *pstmt;
    try
    {
        // Inserta un registro en la tabla entregas
        pstmt = con->prepareStatement("INSERT INTO entregas(placa_vehiculo,id_solicitud,fecha_de_entrega,estatus) VALUES (?, ?, ?, ?)");
        pstmt->setString(1, placa_vehiculo);
        pstmt->setInt(2, id_solicitud);
        pstmt->setString(3, "-");
        pstmt->setString(4, POR_ENTREGAR);
        pstmt->execute();
        delete pstmt;
        return modificarEstatusSolicitud(id_solicitud, POR_ENTREGAR);
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

/************************************************************* INSTANCIAS ***************************************************************/

// Instanciar un proveedor de la BDD
Proveedor *MySQLConnection::instanciarProveedor(const char *correo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    Proveedor *proveedor = 0;

    try
    {
        // Busca un registro en la tabla proveedores que contenga el correo recibido por parámetro
        pstmt = con->prepareStatement("SELECT * FROM proveedores WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se crea una instancia del proveedor con los datos de la BDD
            proveedor = new Proveedor();
            proveedor->setNombre(res->getString("nombre"));
            proveedor->setDescripcion(res->getString("descripcion"));
            proveedor->setTelefono(res->getString("telefono"));
            proveedor->setDireccion(res->getString("direccion"));
            proveedor->setTipoProveedor(res->getString("tipo_de_proveedor"));
            proveedor->setCorreo(correo);
            proveedor->setAlmacen(instanciarAlmacen(proveedor));
            delete res;
            delete pstmt;
            // Retorna la instancia creada
            return proveedor;
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
    // Si no se encuentra el registro, que retorna un puntero NULL
    return 0;
}

// Instanciar el almacén de un proveedor desde la BDD
vector<producto_cantidad> MySQLConnection::instanciarAlmacen(Proveedor *proveedor)
{
    vector<producto_cantidad> almacen = vector<producto_cantidad>();
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca todos los registros que existen en la tabla productos que contengan el correo recibido por parámetro
        pstmt = con->prepareStatement("SELECT * FROM productos WHERE correo_proveedor = ?");
        pstmt->setString(1, proveedor->getCorreo());
        res = pstmt->executeQuery();

        while (res->next())
        {
            // Si encuentra un registro, se crea una instancia del producto con los datos de la BDD
            Producto producto = Producto();
            producto.setNombre(res->getString("nombre"));
            producto.setDescripcion(res->getString("descripcion"));
            producto.setPrecio(res->getDouble("precio"));
            producto.setId(res->getInt("id_producto"));
            int cantidad = res->getInt("cantidad");
            // Se agrega el producto a la lista del almacén
            almacen.push_back(structProductoCantidad(producto, cantidad));
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
    // Retorna la lista del almacén
    return almacen;
}

// Instanciar una persona - cliente de la BDD
Cliente *MySQLConnection::instanciarCliente(const char *correo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca un registro en la tabla personas que contenga el correo recibido por parámetro
        pstmt = con->prepareStatement("SELECT * FROM personas WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se crea una instancia del cliente con los datos de la BDD
            Cliente *persona = new Cliente();
            persona->setNombre(res->getString("nombre"));
            persona->setApellido(res->getString("apellido"));
            persona->setTelefono(res->getString("telefono"));
            persona->setDireccion(res->getString("direccion"));
            QString fecha = QString().fromStdString(res->getString("fecha_nacimiento"));
            persona->setFechaNacimiento(QDate().fromString(fecha, "dd/MM/yyyy"));
            persona->setCorreo(string(correo));

            delete res;
            delete pstmt;
            // Retorna la instancia creada
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
    // Si no se encuentra el registro, que retorna un puntero NULL
    return 0;
}

// Instanciar una persona - transportista de la BDD
Transportista *MySQLConnection::instanciarTransportista(const char *correo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca un registro en la tabla personas que contenga el correo recibido por parámetro
        pstmt = con->prepareStatement("SELECT * FROM personas WHERE correo = ?");
        pstmt->setString(1, correo);
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se crea una instancia del transportista con los datos de la BDD
            Transportista *persona = new Transportista();
            persona->setNombre(res->getString("nombre"));
            persona->setApellido(res->getString("apellido"));
            persona->setTelefono(res->getString("telefono"));
            persona->setDireccion(res->getString("direccion"));
            QString fecha = QString().fromStdString(res->getString("fecha_nacimiento"));
            persona->setFechaNacimiento(QDate().fromString(fecha, "dd/MM/yyyy"));
            persona->setCorreo(string(correo));
            persona->setVehiculos(instanciarVehiculos(correo));

            delete res;
            delete pstmt;
            // Retorna la instancia creada
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
    // Si no se encuentra el registro, que retorna un puntero NULL
    return 0;
}

// Instanciar detalles de una solicitud de compra desde la BDD
vector<producto_cantidad> MySQLConnection::instanciarPedido(Solicitud *solicitud)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    vector <producto_cantidad> pedido = vector <producto_cantidad>();

    try
    {
        // Busca todos los registros que existen en la tabla solicitudes_detalles que contenga el id de la solicitud recibida por parámetro
        pstmt = con->prepareStatement("SELECT * FROM solicitudes_detalles WHERE id_solicitud = ?");
        pstmt->setInt(1, solicitud->getId());
        res = pstmt->executeQuery();

        while (res->next())
        {
            // A cada registro que se encuentre, se agregará a la lista de pedidos, la instancia obtenida de cada producto_cantidad
            pedido.push_back(instanciarProductoCantidad(res->getInt("id_producto")));
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
    // Retorna la lista del pedido
    return pedido;
}

// Instanciar un producto con su cantidad desed la BDD
producto_cantidad MySQLConnection::instanciarProductoCantidad(const int id)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca un registro en la tabla productos que contenga el id del producto recibido por parámetro
        pstmt = con->prepareStatement("SELECT * FROM productos WHERE id_producto = ?");
        pstmt->setInt(1, id);
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se crea una instancia del producto con los datos de la BDD
            Producto producto = Producto();
            producto.setNombre(res->getString("nombre"));
            producto.setDescripcion(res->getString("descripcion"));
            producto.setPrecio(res->getDouble("precio"));
            int cantidad = res->getInt("cantidad");

            delete res;
            delete pstmt;
            // Retorna una estructura con el producto creado + la candidad disponible en el almacén
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
    // Si no lo encuentra, retorna una estructura producto_cantidad vacía
    return producto_cantidad();
}

// Instanciar una solicitud de un cliente desde la BDD
Solicitud *MySQLConnection::instanciarSolicitud(Persona cliente, const int id)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca un registro en la tabla solicitudes que contenga el id de la solicitud recibida por parámetro
        pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE id_solicitud = ?");
        pstmt->setInt(1, id);
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se crea una instancia de la solicitud con los datos de la BDD y el cliente recibido por parámetro
            Solicitud *solicitud = new Solicitud();
            solicitud->setCliente(cliente);
            solicitud->setProveedor(*instanciarProveedor(res->getString("correo_proveedor").c_str()));
            solicitud->setMonto(res->getDouble("monto"));
            solicitud->setTipoPago(obtenerTipoDePago(res->getInt("id_tipo_de_pago")));
            solicitud->setDireccion(res->getString("direccion"));
            QString fechaP = QString().fromStdString(res->getString("fecha_de_creacion"));
            QString fechaE = QString().fromStdString(res->getString("fecha_de_entrega"));
            solicitud->setFechaPedido(QDate().fromString(fechaP, "dd/MM/yyyy"));
            solicitud->setFechaEntrega(QDate().fromString(fechaE, "dd/MM/yyyy"));
            solicitud->setEstatus(res->getString("estatus"));
            solicitud->setId(id);
            instanciarPedido(solicitud);

            delete res;
            delete pstmt;
            // Retorna la instancia creada
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
    // Si no se encuentra el registro, que retorna un puntero NULL
    return 0;
}

// Instanciar una solicitud de un proveedor desde la BDD
Solicitud *MySQLConnection::instanciarSolicitud(Proveedor proveedor, const int id)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca un registro en la tabla solicitudes que contenga el id de la solicitud recibida por parámetro
        pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE id_solicitud = ?");
        pstmt->setInt(1, id);
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se crea una instancia de la solicitud con los datos de la BDD y el proveedor recibido por parámetro
            Solicitud *solicitud = new Solicitud();
            solicitud->setCliente(*instanciarCliente(res->getString("correo_cliente").c_str()));
            solicitud->setProveedor(proveedor);
            solicitud->setMonto(res->getDouble("monto"));
            solicitud->setTipoPago(obtenerTipoDePago(res->getInt("id_tipo_de_pago")));
            solicitud->setDireccion(res->getString("direccion"));
            QString fechaP = QString().fromStdString(res->getString("fecha_de_creacion"));
            QString fechaE = QString().fromStdString(res->getString("fecha_de_entrega"));
            solicitud->setFechaPedido(QDate().fromString(fechaP, "dd/MM/yyyy"));
            solicitud->setFechaEntrega(QDate().fromString(fechaE, "dd/MM/yyyy"));
            solicitud->setEstatus(res->getString("estatus"));
            solicitud->setId(id);
            instanciarPedido(solicitud);

            delete res;
            delete pstmt;
            // Retorna la instancia creada
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
    // Si no se encuentra el registro, que retorna un puntero NULL
    return 0;
}

// Instanciar una solicitud desde la BDD
Solicitud *MySQLConnection::instanciarSolicitud(const int id)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca un registro en la tabla solicitudes que contenga el id de la solicitud recibida por parámetro
        pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE id_solicitud = ?");
        pstmt->setInt(1, id);
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se crea una instancia de la solicitud con los datos de la BDD
            Solicitud *solicitud = new Solicitud();
            solicitud->setCliente(*instanciarCliente(res->getString("correo_cliente").c_str()));
            solicitud->setProveedor(*instanciarProveedor(res->getString("correo_proveedor").c_str()));
            solicitud->setMonto(res->getDouble("monto"));
            solicitud->setTipoPago(obtenerTipoDePago(res->getInt("id_tipo_de_pago")));
            solicitud->setDireccion(res->getString("direccion"));
            QString fechaP = QString().fromStdString(res->getString("fecha_de_creacion"));
            QString fechaE = QString().fromStdString(res->getString("fecha_de_entrega"));
            solicitud->setFechaPedido(QDate().fromString(fechaP, "dd/MM/yyyy"));
            solicitud->setFechaEntrega(QDate().fromString(fechaE, "dd/MM/yyyy"));
            solicitud->setEstatus(res->getString("estatus"));
            solicitud->setId(id);
            instanciarPedido(solicitud);

            delete res;
            delete pstmt;
            // Retorna la instancia creada
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
    // Si no se encuentra el registro, que retorna un puntero NULL
    return 0;
}

vector <Vehiculo> MySQLConnection::instanciarVehiculos(const char *correo_transportista)
{
    vector <Vehiculo> lista = vector <Vehiculo>();

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca todos los registros que existen en la tabla vehiculos que contengan  el correo del transportista recibido por parámetro
        pstmt = con->prepareStatement("SELECT * FROM vehiculos WHERE correo_transportista = ? ");
        pstmt->setString(1, correo_transportista);
        res = pstmt->executeQuery();

        while (res->next())
        {
            // Por cada registro, se crea una instancia del vehículo son los datos de la BDD
            Vehiculo vehiculo = Vehiculo(res->getString("modelo").c_str(), res->getString("placa").c_str(), res->getString("tipo_de_vehiculo").c_str());
            // Se añade cada instancia a la lista de vehículos
            lista.push_back(vehiculo);
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
    // Retorna la lista de vehículos
    return lista;
}

/************************************************************* OBTENER ID ***************************************************************/

// Obtener ID de un tipo de pago
int MySQLConnection::obtenerIdTipoDePago(const char *correo_proveedor, const char *tipo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    int id = 0;

    try
    {
        // Busca un registro en la tabla tipos_de_pago que contenga el correo del proveedor y la descripción recibida por parámetro
        pstmt = con->prepareStatement("SELECT * FROM tipos_de_pago WHERE correo_proveedor = ? AND descripcion = ?");
        pstmt->setString(1, correo_proveedor);
        pstmt->setString(2, tipo);
        res = pstmt->executeQuery();

        if (res->next())
            // Si encuentra el registro, se guarda el id correspondiente
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
    // Retorna 0 si no encontró un id a ese tipo de pago
    // Retorna el id si encontró un registro con el tipo de pago perteneciente a un proveedor
    return id;
}

// Obtener ID de un producto
int MySQLConnection::obtenerIdProducto(const char *correo_proveedor, Producto producto)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    int id = 0;

    try
    {
        // Busca un registro en la tabla productos que contenga el correo del proveedor y la información del producto recibido por parámetro
        pstmt = con->prepareStatement("SELECT * FROM productos WHERE correo_proveedor = ? AND nombre = ? AND descripcion = ? AND precio = ?");
        pstmt->setString(1, correo_proveedor);
        pstmt->setString(2, producto.getNombre().c_str());
        pstmt->setString(3, producto.getDescripcion().c_str());
        pstmt->setDouble(4, producto.getPrecio());
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se guarda el id correspondiente
            id = res->getInt("id_producto");
            (&producto)->setId(id);
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
    // Retorna 0 si no encontró un id de ese producto
    // Retorna el id si encontró un registro con el producto perteneciente a un proveedor
    return id;
}

// Obtener ID de una solicitud
int MySQLConnection::obtenerIdSolicitud(Solicitud solicitud)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    int id = 0;

    try
    {
        // Busca un registro en la tabla solicitudes que contenga la información de la solicitud recibida por parámetro
        pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE correo_proveedor = ? AND correo_cliente = ? AND monto = ? AND fecha_de_creacion = ? AND direccion = ? AND estatus = ?");
        pstmt->setString(1, solicitud.getProveedor().getCorreo().c_str());
        pstmt->setString(2, solicitud.getCliente().getCorreo().c_str());
        pstmt->setDouble(3, solicitud.getMonto());
        pstmt->setString(4, solicitud.getFechaPedido().toString("dd/MM/yyyy").toStdString().c_str());
        pstmt->setString(5, solicitud.getDireccion().c_str());
        pstmt->setString(6, solicitud.getEstatus().c_str());
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se guarda el id correspondiente
            id = res->getInt("id_solicitud");
            (&solicitud)->setId(id);
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
    // Retorna 0 si no encontró un id de esa solicitud
    // Retorna el id si encontró un registro con la solicitud determinada
    return id;
}

// Obtener la descripcion de un tipo de pago a partir de su ID
const char *MySQLConnection::obtenerTipoDePago(const int id)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca un registro en la tabla tipos_de_pago que contenga el id del tipo de pago recibido por parámetro
        pstmt = con->prepareStatement("SELECT * FROM tipos_de_pago WHERE id_tipo_de_pago = ?");
        pstmt->setInt(1, id);
        res = pstmt->executeQuery();

        if (res->next())
        {
            // Si encuentra el registro, se guarda la descripcion del mismo
            const char *tipo= new char(30);
            tipo = res->getString("descripcion").c_str();
            delete res;
            delete pstmt;
            // Retorna la descripción del tipo de pago
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
    // Si no se encuentra el registro, que retorna un puntero NULL
    return 0;
}

/******************************************************** ACTUALIZACIÓN DE DATOS ********************************************************/

// Modificar estatus de una solicitud
int MySQLConnection::modificarEstatusSolicitud(const int id_solicitud, const char *estatus)
{
    sql::PreparedStatement *pstmt;

    try
    {
        // Actualiza el estatus de un registro en la tabla solicitudes que corresponde al id recibido por parámetro
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


// Modificar estatus de una entrega
int MySQLConnection::modificarEstatusEntrega(const int id_entrega, const char *estatus)
{
    sql::PreparedStatement *pstmt;

    try
    {
        // Actualiza el estatus de un registro en la tabla entregas que corresponde al id recibido por parámetro
        pstmt = con->prepareStatement("UPDATE entregas SET estatus = ? WHERE id_entrega = ?");
        pstmt->setString(1, estatus);
        pstmt->setInt(2, id_entrega);
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

// Actualiza e la BDD la fecha en la que fue realizada una entrega
int MySQLConnection::actualizarFechaEntrega(const int id_entrega, QDate fecha)
{
    sql::PreparedStatement *pstmt;

    try
    {
        // Actualiza la fecha de un registro en la tabla entregas que corresponde al id recibido por parámetro
        pstmt = con->prepareStatement("UPDATE entregas SET fecha_de_entrega = ? WHERE id_entrega = ?");
        pstmt->setString(1, fecha.toString("dd/MM/yyyy").toStdString());
        pstmt->setInt(2, id_entrega);
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

// Actualizar cantidad de un producto dentro del almacen
int MySQLConnection::actualizarCantidadProducto(const int id_producto, const int cantidad)
{
    sql::PreparedStatement *pstmt;

    try
    {
        // Actualiza la cantidad de un registro en la tabla productos que corresponde al id recibido por parámetro
        pstmt = con->prepareStatement("UPDATE productos SET cantidad = ? WHERE id_producto = ?");
        pstmt->setInt(1, cantidad);
        pstmt->setInt(2, id_producto);
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

// Actualiza el almacén dado un pedido
// Retorna 1 si se logró la actualización
// Retorna -1 por almacén negativo
// Retorna -2 por error en la búsqueda
int MySQLConnection::actualizarAlmacen(vector<producto_cantidad> pedido, const int signo)
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    vector<int> cantidades = vector <int>();

    // Recorre toda la lista de productos recibida por parámetro
    for (std::size_t i = 0; i < pedido.size(); i++)
    {
        try
        {
            // Guarda la nueva cantidad de un producto de la tabla productos, en una lista para su posterior actualización
            pstmt = con->prepareStatement("SELECT * FROM productos WHERE id_producto = ?");
            pstmt->setInt(1, pedido[i].producto.getId());
            res = pstmt->executeQuery();

            if (res->next())
            {
                // Si al sumar o restar la cantidad del almacén con la cantidad del pedido no da una cantidad negativa, se guarda en la nueva lista de cantidades
                int cantidad = res->getUInt("cantidad") + (pedido[i].cantidad * signo);
                if (cantidad >= 0)
                {
                    cantidades.push_back(cantidad);
                }
                else
                {
                    delete res;
                    delete pstmt;
                    // Si da un número negativo, no se actualiza el almacén
                    return -1;
                }
            }
            else
            {
                delete res;
                delete pstmt;
                // Retorna -2 si no se encontró un producto en la BDD
                return -2;
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

    // Actualiza el almacén con las nuevas cantidades
    for (std::size_t i = 0; i < pedido.size(); i++)
        actualizarCantidadProducto(pedido[i].producto.getId(), cantidades[i]);

    return 1;
}

/*********************************************************** VISTAS GLOBALES ************************************************************/

// Valida si el puntero usuario Global existe
int MySQLConnection::validarPtrUsuario()
{
    if (Global::usuario == nullptr)
        return 0;
    return 1;
}

// Verifica si el puntero usuario Global es una instancia de Proveedor
int MySQLConnection::vistaProveedor()
{
    if (validarPtrUsuario())
        if (!strcmp("proveedor", Global::tipoDeUsuario.c_str()))
            // Retorna 1 si está en vista proveedor y el puntero Global existe
            return 1;

    // Retorna 0 si alguna de las condiciones falla
    return 0;
}

// Verifica si el puntero usuario Global es una instancia de Transportista
int MySQLConnection::vistaTransportista()
{
    if (validarPtrUsuario())
        if (!strcmp("transportista", Global::tipoDeUsuario.c_str()))
            // Retorna 1 si está en vista transportista y el puntero Global existe
            return 1;

    // Retorna 0 si alguna de las condiciones falla
    return 0;
}

// Verifica si el puntero usuario Global es una instancia de Cliente
int MySQLConnection::vistaCliente()
{
    if (validarPtrUsuario())
        if (!strcmp("cliente", Global::tipoDeUsuario.c_str()))
            // Retorna 1 si está en vista cliente y el puntero Global existe
            return 1;

    // Retorna 0 si alguna de las condiciones falla
    return 0;
}

/****************************************************************************************************************************************/
/********************************************************** FUNCIONES PÚBLICAS **********************************************************/
/****************************************************************************************************************************************/

// Cosnstructor de un struct producto_cantidad
producto_cantidad MySQLConnection::structProductoCantidad(Producto producto, int cantidad)
{
    producto_cantidad pxq = producto_cantidad();
    pxq.producto = producto;
    pxq.cantidad = cantidad;
    return pxq;
}

// Cosnstructor de un struct producto_cantidad
vehiculo_transportista MySQLConnection::structVehiculoTransportista(Vehiculo vehiculo, Transportista transportista)
{
    vehiculo_transportista v = vehiculo_transportista();
    v.vehiculo = vehiculo;
    v.transportista = transportista;
    return v;
}

/*********************************************************** INICIO DE SESIÓN ***********************************************************/
/* Entra a la BDD y comprueba el inicio de sesión
*  Retorna 1: cuando los datos son válidos y se inicia sesión
*  Retorna -1: cuando el correo está registrado, pero la contraseña no coincide
*  Retorna 0: cuando el correo no está registrado en la BDD
*  Retorna -2: cuando se produce un error en la búsqueda
*/
int MySQLConnection::iniciarSesion(const char *correo, const char *password)
{
    if (con == 0)
        return -2;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        // Busca un registro en la tabla usuarios que contenga el correo recibido por parámetro
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

                // Instanciando proveedor global con los atributos de la BDD
                if (!strcmp(tipo.c_str(), "proveedor"))
                {
                    Global::usuario = instanciarProveedor(correo);
                }
                else
                {
                    pstmt = con->prepareStatement("SELECT * FROM personas WHERE correo = ?");
                    pstmt->setString(1, correo);
                    res = pstmt->executeQuery();


                    if (res->next())
                    {
                        // Instanciando cliente global con los atributos de la BDD
                        if (!strcmp(tipo.c_str(), "cliente"))
                        {
                            Global::usuario = instanciarCliente(correo);
                        }
                        // Instanciando transportista global con los atributos de la BDD
                        else if (!strcmp(tipo.c_str(), "transportista"))
                        {
                            Global::usuario = instanciarTransportista(correo);
                        }
                        else
                        {
                            delete res;
                            delete pstmt;
                            return -2;
                        }
                    }
                    delete res;
                    delete pstmt;
                }
                // Se inicializa el tipo de usuario global con el obtenido del inicio de sesión
                Global::tipoDeUsuario = tipo;
                // Retorna 1 por un inicio de sesión exitoso
                return 1;
            }
            // Entonces se encontró el correo, pero la contraseña no coincide
            delete res;
            delete pstmt;
            return -1;
        }

        // Si llega aquí es porque el correo no está registrado
        delete res;
        delete pstmt;
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

/********************************************************* REGISTRO DE USUARIOS *********************************************************/

// Registro de nuevo cliente
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
    return 1;
}

// Registro de nuevo proveedor
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

// Registro de nuevo transportista
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
    registrarVehiculo(vehiculo, correo);
    return 1;
}

// Registro de un nuevo vehículo
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

/******************************************************** FUNCIONES PARA CLIENTES ********************************************************/

// Registro de nueva solicitud
int MySQLConnection::registrarSolicitud(Solicitud solicitud)
{
    if (!vistaCliente())
    {
        qDebug() << "El puntero global no corresponde a un cliente";
        return 0;
    }

    sql::PreparedStatement *pstmt;
    try
    {
        Cliente *cliente = reinterpret_cast<Cliente *>(Global::usuario);
        solicitud.setCliente(*cliente);
        pstmt = con->prepareStatement("INSERT INTO solicitudes(correo_cliente,correo_proveedor,monto,id_tipo_de_pago,direccion,fecha_de_creacion,fecha_de_entrega,estatus) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        pstmt->setString(1, solicitud.getCliente().getCorreo().c_str());
        pstmt->setString(2, solicitud.getProveedor().getCorreo().c_str());
        pstmt->setDouble(3, solicitud.getMonto());
        pstmt->setInt(4, obtenerIdTipoDePago(solicitud.getProveedor().getCorreo().c_str(), solicitud.getTipoPago().c_str()));
        pstmt->setString(5, solicitud.getDireccion().c_str());
        pstmt->setString(6, solicitud.getFechaPedido().toString("dd/MM/yyyy").toStdString().c_str());
        pstmt->setString(7, solicitud.getFechaEntrega().toString("dd/MM/yyyy").toStdString().c_str());
        pstmt->setString(8, "en espera");
        pstmt->execute();

        qDebug() << "La solicitud fue registrada con éxito uwu";
        delete pstmt;

        int id = obtenerIdSolicitud(solicitud);
        solicitud.setId(id);
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

// Listar tipos de pago de un proveedor
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

/****************************************************** FUNCIONES PARA PROVEEDORES ******************************************************/

// Listar mis tipos de pago
vector <string> MySQLConnection::listarTiposDePago()
{
    vector <string> lista;

    if (!vistaProveedor())
        return lista;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM tipos_de_pago WHERE correo_proveedor = ?");
        pstmt->setString(1, Global::usuario->getCorreo().c_str());
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

// Agregar producto al almacén
int MySQLConnection::agregarProductoAlmacen(Producto producto, int cantidad)
{
    if (!vistaProveedor())
        return 0;

    producto_cantidad pxq = structProductoCantidad(producto,cantidad);


    if (obtenerIdProducto(Global::usuario->getCorreo().c_str(), pxq.producto))
    {
        qDebug() << "Ya existe este producto";
        return 0;
    }

    if (registrarProducto(Global::usuario->getCorreo().c_str(), pxq))
    {
        Proveedor *proveedor = reinterpret_cast<Proveedor*>(Global::usuario);
        proveedor->getAlmacen().push_back(pxq);
        return 1;
    }

    return 0;
}

// Agregar un tipo de pago
// Retorna 1 si se hizo el registro
// Retorna -1 si el tipo de pago existe para ese proveedor
// Retorna 0 por errores de SQL o de puntero
int MySQLConnection::agregarTipoDePago(const char *descripcion)
{
    if (!vistaProveedor())
        // El puntero global no corresponde a un proveedor
        return 0;

    if (obtenerIdTipoDePago(Global::usuario->getCorreo().c_str(), descripcion))
        // Si obtiene el Id del tipo de pago recibido por parámetro, entonces ese tipo ya existe y no se ejecuta el registro
        return -1;

    return registrarTipoDePago(Global::usuario->getCorreo().c_str(), descripcion);
}

// Aprobar una solicitud de compra
int MySQLConnection::aprobarSolicitud(Solicitud solicitud, const char *placa_vehiculo)
{
    if (!vistaProveedor())
        return 0;

    return registrarEntrega(solicitud.getId(), placa_vehiculo);;
}

// Rechazar una solicitud de compra
int MySQLConnection::rechazarSolicitud(Solicitud solicitud)
{
    if (!vistaProveedor())
        return 0;

    if (!actualizarAlmacen(solicitud.getPedido(), 1))
        return 0;

    return Global::db.modificarEstatusSolicitud(solicitud.getId(), "rechazada");
}

// Lista a todos los transportistas registrados en la BDD con su respectivo vehículo
vector <vehiculo_transportista> MySQLConnection::listarTransportistas()
{
    vector <vehiculo_transportista> lista = vector <vehiculo_transportista>();

    if (!vistaProveedor())
        return lista;

    sql::Statement *stmt;
    sql::ResultSet *res;

    try
    {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM vehiculos");

        while (res->next())
        {
            Vehiculo vehiculo = Vehiculo(res->getString("modelo").c_str(), res->getString("placa").c_str(), res->getString("tipo_de_vehiculo").c_str());
            lista.push_back(structVehiculoTransportista(vehiculo, *instanciarTransportista(res->getString("correo_transportista").c_str())));
        }

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

int MySQLConnection::actualizarInfoProducto(producto_cantidad pxq)
{
    if (!vistaProveedor())
        return 0;


    sql::PreparedStatement *pstmt;

    try
    {
        pstmt = con->prepareStatement("UPDATE productos SET nombre = ? AND descripcion = ? AND precio = ? AND cantidad = ? WHERE id_producto = ? AND correo_proveedor = ?");
        pstmt->setString(1, pxq.producto.getNombre());
        pstmt->setString(2, pxq.producto.getDescripcion());
        pstmt->setDouble(3, pxq.producto.getPrecio());
        pstmt->setInt(4, pxq.cantidad);
        pstmt->setInt(5, pxq.producto.getId());
        pstmt->setString(6, Global::usuario->getCorreo());
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

/**************************************************** FUNCIONES PARA TRANSPORTISTAS ****************************************************/

// Listar entregas
vector <Solicitud> MySQLConnection::listarEntregasRealizadas()
{
    vector <Solicitud> lista = vector <Solicitud>();

    if (!vistaTransportista())
        return lista;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        Transportista *transportista = reinterpret_cast<Transportista*>(Global::usuario);
        int flag = 0;

        for (std::size_t i = 0; i < transportista->getVehiculos().size(); i++)
        {
            pstmt = con->prepareStatement("SELECT * FROM entregas WHERE placa_vehiculo = ? AND estatus = ?");
            pstmt->setString(1, transportista->getVehiculos()[i].getPLaca().c_str());
            pstmt->setString(2, "entregado");
            res = pstmt->executeQuery();
            flag = 1;

            while (res->next())
                lista.push_back(*instanciarSolicitud(res->getInt("id_solicitud")));
        }

        if (flag)
        {
            delete res;
            delete pstmt;
        }
    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    return lista;
}

// Listar entregas pendientes
vector <Solicitud> MySQLConnection::listarEntregasPendientes()
{
    vector <Solicitud> lista = vector <Solicitud>();

    if (!vistaTransportista())
        return lista;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        Transportista *transportista = reinterpret_cast<Transportista*>(Global::usuario);
        int flag = 0;

        for (std::size_t i = 0; i < transportista->getVehiculos().size(); i++)
        {
            pstmt = con->prepareStatement("SELECT * FROM entregas WHERE placa_vehiculo = ? AND estatus = ?");
            pstmt->setString(1, transportista->getVehiculos()[i].getPLaca().c_str());
            pstmt->setString(2, "por entregar");

            res = pstmt->executeQuery();
            flag = 1;

            while (res->next())
                lista.push_back(*instanciarSolicitud(res->getInt("id_solicitud")));
        }

        if (flag)
        {
            delete res;
            delete pstmt;
        }

    }
    catch (sql::SQLException &e)
    {
        // Error de conexión
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }

    return lista;
}

int MySQLConnection::realizarEntrega(Solicitud solicitud)
{
    if (!vistaTransportista())
        return 0;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {

        pstmt = con->prepareStatement("SELECT * FROM entregas WHERE id_solicitud = ? AND estatus = ?");
        pstmt->setInt(1, solicitud.getId());
        pstmt->setString(2, "por entregar");

        res = pstmt->executeQuery();

        if (res->next())
            if (verificarEntrega(res->getString("placa_vehiculo").c_str()))
                if (modificarEstatusEntrega(res->getInt("id_entrega"), "entregado"))
                {
                    actualizarFechaEntrega(res->getInt("id_entrega"), QDate::currentDate());
                    delete res;
                    delete pstmt;
                    return 1;
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

/********************************************************* FUNCIONES GENÉRICAS *********************************************************/

// Listar proveedores disponibles
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

// Listar mis solicitudes (cliente o  proveedor)
vector <Solicitud> MySQLConnection::listarSolicitudes()
{
    vector <Solicitud> lista = vector <Solicitud>();

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    try
    {
        if (vistaCliente())
        {
            Cliente *cliente = reinterpret_cast<Cliente*>(Global::usuario);
            pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE correo_cliente = ?");
            pstmt->setString(1, cliente->getCorreo().c_str());
            res = pstmt->executeQuery();

            while (res->next())
                lista.push_back(*instanciarSolicitud(*cliente,res->getInt("id_solicitud")));
        }
        else if (vistaProveedor())
        {
            Proveedor *proveedor = reinterpret_cast<Proveedor*>(Global::usuario);
            pstmt = con->prepareStatement("SELECT * FROM solicitudes WHERE correo_proveedor = ?");
            pstmt->setString(1, proveedor->getCorreo().c_str());
            res = pstmt->executeQuery();

            while (res->next())
                lista.push_back(*instanciarSolicitud(*proveedor,res->getInt("id_solicitud")));
        }
        else
        {
            return lista;
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
    return lista;
}
