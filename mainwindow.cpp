#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <pthread.h>
#include <stdio.h>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    // Esto es simplemente una prueba del funcionamiento del conector
    sql::Statement *stmt;
    sql::ResultSet *res;
    const char *correo;

    try
    {
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM usuarios WHERE id_usuario=1");

        // En este caso como solo se recibe un registro no es necesario el while pero igual lo coloqué para ilustrarlo
        while (res->next())
        {
            correo = res->getString("correo").c_str(); // Se debe convertir a const char *
        }

        delete res; // Siempre es necesario liberar la memoria de res y stmt luego de una consulta
        delete stmt;

        QMessageBox msgBox;
        msgBox.setText(correo);
        msgBox.exec();

        qDebug() << "Hola"; // Nótese que hasta que no se cierra el MessageBox, no se ejecuta esta línea
    }
    catch (sql::SQLException &e)
    {
        qDebug() << "# ERR: SQLException in " << __FILE__ << "(" << __FUNCTION__ << ") on line " << __LINE__;
        qDebug() << "# ERR: " << e.what() << " ( MySQL error code: " << e.getErrorCode() << ")";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete con;
}


void MainWindow::on_pushButton_clicked()
{


}
