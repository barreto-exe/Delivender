#include "pantalla_registro.h"
#include "ui_pantalla_registro.h"
#include <QMessageBox>
#include <QPixmap>

pantalla_registro::pantalla_registro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantalla_registro)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); //Hace que la pantalla de inicio sea la predeterminada

}

pantalla_registro::~pantalla_registro()
{
    delete ui;
}

void pantalla_registro::on_btnAceptarPersona_clicked() //Boton aceptar al introducir los datos del registro
{

}

void pantalla_registro::on_atrasProv_clicked() //vuelve a pantalla de registro
{
    ui->stackedWidget->setCurrentIndex(0);
}

void pantalla_registro::on_atrasTransp_clicked() //vuelve al registro de persona
{
    ui->stackedWidget->setCurrentIndex(1);
}

void pantalla_registro::on_atrasRegistroPersona_clicked() //vuelve a la seleccion de usuario
{
    ui->stackedWidget->setCurrentIndex(0);
}

void pantalla_registro::on_btnCliente_clicked()//va al registro de persona
{
    ui->stackedWidget->setCurrentIndex(1);
}

void pantalla_registro::on_btnProveedor_clicked()//va al registro de proveedor
{
    ui->stackedWidget->setCurrentIndex(2);
}

void pantalla_registro::on_btnTransp_clicked()//va al registro de persona
{
    ui->stackedWidget->setCurrentIndex(1);
}
