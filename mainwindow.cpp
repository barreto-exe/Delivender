#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stackedwidget = ui->centralwidget->findChild<QStackedWidget *>();
    stackedwidget->insertWidget(1,&registro);
    stackedwidget->insertWidget(2, &menu);

    connect(&registro, SIGNAL(AtrasCLick()),this,SLOT(IrAInicio()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnInicioSesion_clicked()
{
    stackedwidget->setCurrentIndex(2);
}

void MainWindow::on_btnRegistrarse_clicked()
{
    stackedwidget->setCurrentIndex(1);
}

void MainWindow::IrAInicio()
{
    stackedwidget->setCurrentIndex(0);
}
