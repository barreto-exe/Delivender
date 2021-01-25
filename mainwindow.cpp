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
    
    char correo[30] = "karen@gmail.com", password[16] = "test";
    char nombre[20] = "karen", apellido[20] = "moran", cedula[10] = "28161659", telefono[15] = "04121924525", direccion[20] = "Curagua";
    time_t *fecha = new time_t();

    Persona *cliente = new Persona(nombre, apellido, cedula, telefono, direccion, fecha);

    conector = MySQLConnection();
    conector.registrarCliente(*cliente, correo, password);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete conector.getConnection();
}

void MainWindow::on_btnInicioSesion_clicked() //cambia a pantalla del menu principal
{
    stackedwidget->setCurrentIndex(2);
}

void MainWindow::on_btnRegistrarse_clicked() //cambia a pantalla del registro
{
    stackedwidget->setCurrentIndex(1);
}

void MainWindow::IrAInicio() //slot para volver al inicio (conectado a AtrasClick())
{
    stackedwidget->setCurrentIndex(0);
}
