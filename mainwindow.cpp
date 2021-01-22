#include "mainwindow.h"
#include "ui_mainwindow.h"


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
}

MainWindow::~MainWindow()
{
    delete ui;
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
