#include "pantalla_proveedor.h"
#include "ui_pantalla_proveedor.h"
#include <QPushButton>
#include <QSize>
#include <solicitudwidget.h>
#include <QMessageBox>
#include "global.h"
#include "persona.h"

pantalla_proveedor::pantalla_proveedor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantalla_proveedor)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    /*Muestra los productos del almacen del proveedor*/
    /*int j=0, k=0; //fila y columna del layout
    const QSize btnSize = QSize(125,75);
    for (auto prod : FALTA){ //mientras haya un producto en la lista

        //crea el boton, lo personaliza y lo muestra en el layout
        QPushButton *boton = new QPushButton(this);
        boton->setFixedSize(btnSize);
        boton->setText(QString::fromStdString(prod.producto.getNombre()));
        boton->setStyleSheet("border: none; background-color: rgb(226, 226, 226); color: rgb(200, 162, 200); text-align: center; text-decoration: none; font-size:14px; font: 75 13pt \"Quicksand Bold\";");
        connect(boton, SIGNAL(clicked(bool)), this, SLOT(FALTA)); //conecta la señal cuando se presiona el boton a popupCantidad
        ui->productLayout->addWidget(boton,j,k,1,1);
        k++;
        if (k==3){
            j++;
            k=0;
        }
    }*/
    /*Muestra las solicitudes del proveeedor*/
    vector <Solicitud> lista = Global::db.listarSolicitudes();
    for (auto s : lista){
        ui->solicLayout->addWidget(new solicitudWidget(this, &s));
    }
}

pantalla_proveedor::~pantalla_proveedor()
{
    delete ui;
}

void pantalla_proveedor::on_btnAddProducto_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void pantalla_proveedor::on_btnAddMetPago_clicked()
{
    QMessageBox msgBox;
    if (Global::db.agregarTipoDePago(ui->descripcionMetodo->text().toStdString().c_str())==1){
        msgBox.setText("Metodo de pago agregado con éxito");
        ui->descripcionMetodo->setText("");
    } else {
        msgBox.setText("Intentelo nuevamente");
    }
    msgBox.exec();
}

void pantalla_proveedor::on_btnRegistrarProd_clicked()
{
    QMessageBox msgBox;
    if(!ui->nombreProd->text().isEmpty() && !ui->descripcionProd->text().isEmpty() && !ui->precioProd->text().isEmpty()){
        /*TODO: registrar producto, tengo sueño*/
    } else {

    }
    msgBox.exec();
}

void pantalla_proveedor::on_btnAtrasAddProd_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
