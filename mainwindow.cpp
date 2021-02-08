#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <ctime>
#include "persona.h"
#include "global.h"
#include <QScreen>


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
    connect(this, SIGNAL(usuarioInicio()),&menuProveedor,SLOT(cargarInfoProveedor()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete Global::db.getConnection();
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
    int inicioSesion = Global::db.iniciarSesion(correo.c_str(), password.c_str());

    if (inicioSesion == 1) // Si lo logró
    {
        msgBox.setText("Inicio de sesión exitoso");
        msgBox.exec();
        if(!strcmp(Global::tipoDeUsuario.c_str(),"cliente")){
            stackedWidget->setCurrentIndex(2);
        } else if(!strcmp(Global::tipoDeUsuario.c_str(),"proveedor")){
            emit usuarioInicio();
            stackedWidget->setCurrentIndex(3);
        } else if(!strcmp(Global::tipoDeUsuario.c_str(),"transportista")){
            /*TODO: pantalla de transportista*/
        }

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
