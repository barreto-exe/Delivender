#include "pantalla_registro.h"
#include "ui_pantalla_registro.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDateTime>
#include <ctime>
#include "persona.h"
#include "global.h"

bool cliente;
Persona *datosPersona;
pantalla_registro::pantalla_registro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantalla_registro)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); //Hace que la pantalla de seleccion sea la predeterminada
}

pantalla_registro::~pantalla_registro()
{
    delete ui;
}

void pantalla_registro::on_btnAceptarPersona_clicked() //Boton aceptar al introducir los datos del registro
{
    QMessageBox msgBox;
    time_t fechaNac = ui->fechaNac->dateTime().toTime_t();
    datosPersona = new Persona(ui->nombre->text().toStdString(),
                                        ui->apellido->text().toStdString(),
                                        ui->cedula->text().toStdString(),
                                        ui->telefono->text().toStdString(),
                                        ui->correo->text().toStdString().c_str(),
                                        ui->direccion->text().toStdString(),fechaNac);
    //Si las contraseñas son iguales
    if(ui->password->text() == ui->repPassword->text())  {
        if(cliente){
            //Lo registra si es un cliente
            int reg = Global::db.registrarCliente(*datosPersona, ui->correo->text().toStdString().c_str(), ui->password->text().toStdString().c_str());
            if (reg==1){
                msgBox.setText("Se ha registrado con éxito!");
                msgBox.exec();
                emit inicioSignal();
            }
        } else {
            //Si es un transportista, pasa a la ventana con los dados adicionales
            ui->stackedWidget->setCurrentIndex(3);
        }
     } else {

        msgBox.setText("Las contraseñas no coinciden, intentelo nuevamente");
        msgBox.exec();
    }
}


/* botones para cambiar de pantallas */
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
    cliente = true;
}

void pantalla_registro::on_btnProveedor_clicked()//va al registro de proveedor
{
    ui->stackedWidget->setCurrentIndex(2);

}

void pantalla_registro::on_btnTransp_clicked()//va al registro de persona
{
    ui->stackedWidget->setCurrentIndex(1);
    cliente = false;
}

void pantalla_registro::on_btnAceptarTransp_clicked()
{
    QMessageBox msgBox;
    if (ui->comboBoxTipo->currentIndex() != 0){ //si el combobox no esta en la primera opcion (seleccione un vehiculo)
        //registra al transportista
        Vehiculo *vehiculo = new Vehiculo(ui->modelo->text().toStdString(), ui->placa->text().toStdString(), ui->comboBoxTipo->currentText().toStdString());

        int reg = Global::db.registrarTransportista(*datosPersona, *vehiculo, ui->correo->text().toStdString().c_str(), ui->password->text().toStdString().c_str());
        if (reg==1){
            msgBox.setText("Se ha registrado con éxito!");
            msgBox.exec();
            emit inicioSignal();
        }
    } else {
        msgBox.setText("Elija un tipo de veíhculo, por favor");
        msgBox.exec();
    }
}

void pantalla_registro::on_atrasSeleccion_clicked()
{
    emit inicioSignal();
}
