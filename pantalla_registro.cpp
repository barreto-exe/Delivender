#include "pantalla_registro.h"
#include "ui_pantalla_registro.h"
#include <QMessageBox>

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

void pantalla_registro::on_btnAceptar_clicked() //Boton aceptar al introducir los datos del registro
{
    QMessageBox mensaje;
    mensaje.setIcon(QMessageBox::Critical);

    //Si la opcion de cliente esta seleccionada
    if (ui->checkCliente->checkState()==2 && ui->checkAdmin->checkState()==0 && ui->checkTransp->checkState()==0){

    } else if (ui->checkCliente->checkState()==0 && ui->checkAdmin->checkState()==2 && ui->checkTransp->checkState()==0) {
        //Si la opcion de admin esta seleccionada
        ui->stackedWidget->setCurrentIndex(1); //va a la pantalla para completar la info adicional de administrador
    } else if (ui->checkCliente->checkState()==0 && ui->checkAdmin->checkState()==0 && ui->checkTransp->checkState()==2) {
        //Si la opcion de transportista esta seleccionada
        ui->stackedWidget->setCurrentIndex(2); //va a la pantalla para completar la info adicional de transportista
    } else if(ui->checkCliente->checkState()==0 && ui->checkAdmin->checkState()==0 && ui->checkTransp->checkState()==0){
        //Si ninguna esta seleccionada
        mensaje.setText("Debe escojer el tipo de usuario para continuar.");
        mensaje.exec(); //muestra mensaje
    } else {
        //Si 2 o mas estan seleccionadas
        mensaje.setText("Solo puede elegir una opción.");
        mensaje.exec(); //muestra mensaje
    }
}

void pantalla_registro::on_atrasAdmin_clicked() //vuelve a pantalla de registro
{
    ui->stackedWidget->setCurrentIndex(0);
}

void pantalla_registro::on_atrasTransp_clicked() //vuelve a pantalla de registro
{
    ui->stackedWidget->setCurrentIndex(0);
}

void pantalla_registro::on_atrasRegistro_clicked() //vuelve al inicio de sesion
{
    emit AtrasCLick();
}
