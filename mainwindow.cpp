#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    //añade las pantallas de manera dinamica al stackWidget
    stackedWidget = ui->centralwidget->findChild<QStackedWidget *>();
    stackedWidget->insertWidget(1,&registro);
    stackedWidget->insertWidget(2,&menu);

    connect(&registro, SIGNAL(AtrasCLick()),this,SLOT(IrAInicio())); //Signal para volver al inicio de sesion desde el registro
    
    char correo[20] = "karenamg@gmail.com";
    char password[5] = "1603";
    conector = MySQLConnection();
    conector.iniciarSesion(correo, password);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete conector.getConnection();
}

void MainWindow::on_btnInicioSesion_clicked() //cambia a pantalla del menu principal
{
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_btnRegistrarse_clicked() //cambia a pantalla del registro
{
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::IrAInicio() //slot para volver al inicio (conectado a AtrasClick())
{
    stackedWidget->setCurrentIndex(0);
}
