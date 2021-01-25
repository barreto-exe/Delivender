#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <ctime>
#include "persona.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    //añade las pantallas de manera dinamica al stackWidget
    stackedwidget = ui->centralwidget->findChild<QStackedWidget *>();
    stackedwidget->insertWidget(1,&registro);
    stackedwidget->insertWidget(2,&menu);

    connect(&registro, SIGNAL(AtrasCLick()),this,SLOT(IrAInicio())); //Signal para volver al inicio de sesion desde el registro
    
//    char correo[30] = "karen@gmail.com", password[16] = "test";
//    char nombre[20] = "karen", apellido[20] = "moran", cedula[10] = "28161659", telefono[15] = "04121924525", direccion[20] = "Curagua";
//    time_t *fecha = new time_t();

//    Persona *cliente = new Persona(nombre, apellido, cedula, telefono, direccion, fecha);

    conector = MySQLConnection();
//    conector.registrarCliente(*cliente, correo, password);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete conector.getConnection();
}

void MainWindow::on_btnInicioSesion_clicked() //cambia a pantalla del menu principal
{
    // Convierte a string los input y borra los espacios
    string correo = ui->correo->text().trimmed().toStdString();
    string password = ui->contrasenia->text().trimmed().toStdString();

    QMessageBox msgBox;

    if (correo.empty() || password.empty())
    {
        msgBox.setText("Llena todos los campos, por favor");
        msgBox.exec();
        return;
    }

    int inicioSesion = conector.iniciarSesion(correo.c_str(), password.c_str());

    if (inicioSesion == 1)
    {
        msgBox.setText("Inicio de sesión exitoso");
        msgBox.exec();
        stackedwidget->setCurrentIndex(2);
    }
    else if (!inicioSesion)
    {
        msgBox.setText("No hay ningún usuario registrado con este correo");
        msgBox.exec();
    }
    else if (inicioSesion == -1)
    {
        msgBox.setText("Contraseña inválida, vuelve a intentarlo");
        msgBox.exec();
    }
    else if (inicioSesion == -2)
    {
        msgBox.setText("Error desconocido, revisa tu conexión");
        msgBox.exec();
    }

}

void MainWindow::on_btnRegistrarse_clicked() //cambia a pantalla del registro
{
    stackedwidget->setCurrentIndex(1);
}

void MainWindow::IrAInicio() //slot para volver al inicio (conectado a AtrasClick())
{
    stackedwidget->setCurrentIndex(0);
}
