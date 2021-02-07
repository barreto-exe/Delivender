#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <ctime>
#include "persona.h"
#include "global.h"
#include <QScreen>
#include <pthread.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    //añade las pantallas de manera dinamica al stackWidget
    stackedWidget = ui->centralwidget->findChild<QStackedWidget *>();
    stackedWidget->insertWidget(1,&registro);
    stackedWidget->insertWidget(2,&menu);
    stackedWidget->insertWidget(3,&menuProveedor);

    //Centra la ventana en la pantalla
    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());

    //Signal para volver al inicio de sesion desde el registro
    connect(&registro, SIGNAL(inicioSignal()),this,SLOT(IrAInicio()));
    
    /*char correo[30] = "karenale@gmail.com", password[16] = "test";
    char nombre[20] = "karen", apellido[20] = "moran", cedula[10] = "28161658", telefono[15] = "04121924525", direccion[20] = "Curagua";
    time_t *fecha = new time_t();

    Persona *transportista = new Persona(nombre, apellido, cedula, telefono, direccion, fecha);

    char placa[10] = "karen19", modelo[15] = "Corolla", tipo[10] = "carro";

    Vehiculo *vehiculo = new Vehiculo(modelo,placa,tipo);

    Global::db.registrarTransportista(*transportista, *vehiculo, correo, password);*/

    //vector <Proveedor> lista = Global::db.listarProveedores();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete Global::db.getConnection();
}

// Estructura con argumentos de la función para iniciar sesión
struct argInicioSesion
{
    const char *correo;
    const char *password;
    int resul;
};

// Función del hilo para iniciar sesión
void *hiloIniciar(void *args)
{
    argInicioSesion *argumentos = (argInicioSesion *) args;
    const char *correo = argumentos->correo;
    const char *password = argumentos->password;

    argumentos->resul = Global::db.iniciarSesion(correo, password);

    pthread_exit(NULL);
}

void MainWindow::on_btnInicioSesion_clicked() //cambia a pantalla del menu principal e inicia sesión
{
    // Convierte a string los input y borra los espacios
    string correo = ui->correo->text().trimmed().toStdString();
    string password = ui->contrasenia->text().trimmed().toStdString();

    QMessageBox msgBox;

    // Si no están llenos los campos
    if (correo.empty() || password.empty())
    {
        msgBox.setText("Llena todos los campos, por favor");
        msgBox.exec();
        return;
    }

    // Intenta iniciar sesión

    // Prepara los argumentos
    argInicioSesion *args = new argInicioSesion;
    args->correo = correo.c_str();
    args->password = password.c_str();

    // Crea un nuevo hilo para el manejo del inicio de sesión
    pthread_t hilo;
    pthread_create(&hilo, NULL, hiloIniciar, args);
    pthread_join(hilo, NULL);

    // Resultado del inicio de sesión
    int inicioSesion = args->resul;
    delete args;

    if (inicioSesion == 1) // Si lo logró
    {
        msgBox.setText("Inicio de sesión exitoso");
        msgBox.exec();
        stackedWidget->setCurrentIndex(2);
    }
    else if (!inicioSesion) // Siel correo es inválido
    {
        msgBox.setText("No hay ningún usuario registrado con este correo");
        msgBox.exec();
    }
    else if (inicioSesion == -1) // Si la contraseña es inválida
    {
        msgBox.setText("Contraseña inválida, vuelve a intentarlo");
        msgBox.exec();
    }
    else if (inicioSesion == -2) // Si hubo otro error (desconexión)
    {
        msgBox.setText("Error desconocido, revisa tu conexión");
        msgBox.exec();
    }

}

void MainWindow::on_btnRegistrarse_clicked() //cambia a pantalla del registro
{
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::IrAInicio() //slot para volver al inicio (conectado a inicioSignal())
{
    stackedWidget->setCurrentIndex(0);
}
