#include "mysql_connection.h"
#include <QDebug>
#include <QMessageBox>

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

int MySQLConnection::iniciarSesion(char *correo, char *password)
{
    // Esto es simplemente una prueba del funcionamiento del conector
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    const char *msj;

    try
    {
        pstmt = con->prepareStatement("SELECT * FROM usuarios WHERE correo = ? AND password = ?");

        pstmt->setString(1, correo);
        pstmt->setString(2, password);

        res = pstmt->executeQuery();


        // En este caso como solo se recibe un registro no es necesario el while pero igual lo coloqué para ilustrarlo
        while (res->next())
        {
            msj = res->getString("tipo_de_usuario").c_str(); // Se debe convertir a const char *
        }

        delete res; // Siempre es necesario liberar la memoria de res y stmt luego de una consulta
        delete pstmt;

        QMessageBox msgBox;
        msgBox.setText(msj);
        msgBox.exec();

        qDebug() << "YAIIIIIIIIIIIIII"; // Nótese que hasta que no se cierra el MessageBox, no se ejecuta esta línea
    }
    catch (sql::SQLException &e)
    {
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
    return 1;
}
