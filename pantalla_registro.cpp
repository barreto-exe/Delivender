#include "pantalla_registro.h"
#include "ui_pantalla_registro.h"
#include <QMessageBox>

pantalla_registro::pantalla_registro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantalla_registro)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

pantalla_registro::~pantalla_registro()
{
    delete ui;
}

void pantalla_registro::on_pushButton_clicked()
{
    //1:cliente 2:admin 3:transp ->1:Admin 2:transp
    QMessageBox mensaje;
    if (ui->checkCliente->checkState()==2 && ui->checkAdmin->checkState()==0 && ui->checkTransp->checkState()==0){

    } else if (ui->checkCliente->checkState()==0 && ui->checkAdmin->checkState()==2 && ui->checkTransp->checkState()==0) {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (ui->checkCliente->checkState()==0 && ui->checkAdmin->checkState()==0 && ui->checkTransp->checkState()==2) {
        ui->stackedWidget->setCurrentIndex(2);
    } else if(ui->checkCliente->checkState()==0 && ui->checkAdmin->checkState()==0 && ui->checkTransp->checkState()==0){
        mensaje.setText("Debe escojer el tipo de usuario para continuar.");
        mensaje.setIcon(QMessageBox::Critical);
        mensaje.exec();
    } else {
        mensaje.setText("Solo puede elegir una opción.");
        mensaje.setIcon(QMessageBox::Critical);
        mensaje.exec();
    }
}

void pantalla_registro::on_atrasAdmin_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void pantalla_registro::on_atrasTransp_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void pantalla_registro::on_atrasRegistro_clicked()
{
    emit AtrasCLick();
}
